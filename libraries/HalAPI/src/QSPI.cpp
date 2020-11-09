/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
//Copyright 2011-2018 Tyler Gilbert; All Rights Reserved

#if !defined __link
#include "sys/Aio.hpp"
#include "chrono/Timer.hpp"
#endif

#include "hal/QSPI.hpp"

using namespace hal;

QSPI::QSPI(port_t port) : Periph(CORE_PERIPH_QSPI, port){}
QSPI_FLASH::QSPI_FLASH(port_t port) : QSPI(port){}


u8 QSPI_FLASH::read_status_reg(){
    u8 data = 0;
    read_reg(read_status_command,&data,FLAG_IS_REGISTER_WIDTH_8);
    return data;
}

int QSPI_FLASH::set_qspi_mode(u32 command,u8 check_mask){
    int result,i;
    result = 0;
    u8 data;
    const u16 MAX_ITERATES = 10;
    i=0;
    for (i =0 ;i<MAX_ITERATES ;i++){
        write_reg(command,NULL,FLAG_IS_INSTRUCTION_1_LINE);
        data = read_status_reg();
        if(data & check_mask){
            write_reg(command,NULL,FLAG_IS_INSTRUCTION_4_LINE);
            break;
        }
    }
    if(i >= MAX_ITERATES){
        result =-1;
    }
    return result;
}
int QSPI_FLASH::write_enable(){
    int result = 0;
    u8 status;
    u16 i;
    const u16 MAX_ITERATES = 10;
    i=0;
    status = read_status_reg();
    for (i =0 ;i<MAX_ITERATES ;i++){
        /*change mode for read operations*/
        write_reg(write_enable_command,NULL,0);
        status = read_status_reg();
        if(status & write_enabled_mask){
            break;
        }
    }
    if(i >=MAX_ITERATES ){
        result =-1;
    }
    return result;
}

int QSPI_FLASH::set_to_four_bytes_address(u32 command){
    int result;
    result = 0;
    write_enable();
    /*change mode for read operations*/
    write_reg(command,NULL,0);
    return result;
}
int QSPI_FLASH::set_dummy_cycles_and_strength(u8 dummy_and_strenght,u8 dummy_and_strength_mask,
                                        u32 read_config_command,u32 write_config_command){
    int result = 0;
    u8 status_cnfg[2];
    /*read first*/
    status_cnfg[0] = read_status_reg();
    /*read second*/
    read_reg(read_config_command,&status_cnfg[1],QSPI_FLAG_IS_REGISTER_WIDTH_8);
    write_enable();
    status_cnfg[1] &= ~dummy_and_strength_mask;
    status_cnfg[1] |=  dummy_and_strenght;
    /*modify*/
    write_reg(write_config_command,&status_cnfg[0],QSPI_FLAG_IS_REGISTER_WIDTH_16);
    u16 i =10000;
    while(i--){};
    /*read for check first*/
    status_cnfg[0] = read_status_reg();
    /*read for check second*/
    read_reg(read_config_command,&status_cnfg[1],QSPI_FLAG_IS_REGISTER_WIDTH_8);
    /*check*/
    if((status_cnfg[1] & dummy_and_strength_mask) != dummy_and_strenght){
        result = -1;
    }
    return result;
}
int QSPI_FLASH::erase_block(u32 block_address,u32 command){
    int result=0;
    /* Enable write operations */
    u8 status_reg;
    status_reg = read_status_reg();
    while(status_reg & write_in_progress_mask){
        status_reg = read_status_reg();
    }
    if (write_enable() == 0){
        u8 address[4];
        address[0] =(u8)(block_address>>24);
        address[1] =(u8)(block_address>>16);
        address[2] =(u8)(block_address>>8);
        address[3] =(u8)(block_address);
        write_reg(command,address,FLAG_IS_REGISTER_WIDTH_32);
        status_reg = read_status_reg();
        while(status_reg & write_in_progress_mask){
            status_reg = read_status_reg();
        }
    }else{
        result = -1;
    }
    return result;

}
u16 QSPI_FLASH::read_flash(u32 address,u8* buff,u16 length){
    u16 result = 0;
    u16 page_count,remain;
    u16 mergin;
    u8 status_reg;
    status_reg = read_status_reg();
    while(status_reg & write_in_progress_mask){
        status_reg = read_status_reg();
    }
    mergin = (u32)m_page_size - (address % (u32)m_page_size);
    if(length > mergin){
        read((int)address,buff,mergin);
        result = mergin;
        length -= mergin;                              // re-calculate the number of elements
        buff += mergin;                                             // modify the pointer to the buffer
        address += mergin;                                             // modify the start address in the memory
        page_count = length / (u16)m_page_size;  // calculate number of pages to be written
        remain = length % m_page_size;   // calculate the remainder after filling up one or more entire pages
        while(page_count--){
            read((int)address,buff,m_page_size);
            result += m_page_size;
            buff += m_page_size;
            address += (u16)(m_page_size);
        }
        read((int)address,buff,remain);
        result += remain;
    }else{
        if(read((int)address,buff,length)<0){
            result = 0;
        }else{
            result = length;
        }

    }
    return result;
}
u16 QSPI_FLASH::write_flash(u32 address,u8* buff,u16 length){
    u16 result = 0;
    u16 page_count,remain;
    u16 mergin;
    u8 status_reg;
    //writing
    status_reg = read_status_reg();
    while(status_reg & write_in_progress_mask){
        status_reg = read_status_reg();
    }
    mergin = (u32)m_page_size - (address % (u32)m_page_size);
    if(length > mergin){
        write_enable();
        write((int)address,buff,mergin);
        result = mergin;
        length -= mergin;                              // re-calculate the number of elements
        buff += mergin;                                             // modify the pointer to the buffer
        address += mergin;                                             // modify the start address in the memory
        page_count = length / (u16)m_page_size;  // calculate number of pages to be written
        remain = length % m_page_size;   // calculate the remainder after filling up one or more entire pages
        while(page_count--){
            status_reg = read_status_reg();
            while(status_reg & write_in_progress_mask){
                status_reg = read_status_reg();
            }
            write_enable();
            write((int)address,buff,m_page_size);
            buff += m_page_size;
            address += m_page_size;
            result+=m_page_size;
        }
        status_reg = read_status_reg();
        while(status_reg & write_in_progress_mask){
            status_reg = read_status_reg();
        }
        write_enable();
        write((int)address,buff,remain);
        result+=remain;
    }else{
        write_enable();
        if(write((int)address,buff,length)<0){
            result = 0;
        }
        result = length;
    }
    return result;
}
