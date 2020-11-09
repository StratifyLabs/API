/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
#ifndef SAPI_HAL_EMC_HPP_
#define SAPI_HAL_EMC_HPP_

#include <sapi/hal.hpp>
#include "sos/dev/emc.h"

/*! \cond */

namespace hal {


class EmcAttributes : public PinAssignmentPeriphAttributes<emc_attr_t, emc_pin_assignment_t> {
public:
    EmcAttributes(u32 o_flags = EMC_FLAG_ENABLE,
                  u8 data_bus_size = 16,u8 address_bus_size = 18,u8 bl_bus_size = 2,
                  u8 ncs_bus_size = 1){
        m_attr.o_flags = o_flags;
        m_attr.data_bus_width = data_bus_size;
        data_bus_size_m = data_bus_size;
        address_bus_size_m = address_bus_size;
        bl_bus_size_m = bl_bus_size;
        ncs_bus_size_m = ncs_bus_size;
    }
    void set_data(const mcu_pin_t * pin){
        int i=0;
        for (i =0; i<data_bus_size_m ;i++) {
            m_attr.pin_assignment.data[i] = pin[i];
		  }
        for (i =0; i<MAX_DATA_BUS_SIZE ;i++) {
            m_attr.pin_assignment.data[i] = {0xff,0xff};
		  }
    }
    void set_address(const mcu_pin_t * pin){
        int i=0;
        for (i =0; i<address_bus_size_m ;i++) {
            m_attr.pin_assignment.address[i] = pin[i];
		  }
        for (; i<MAX_ADDRESS_BUS_SIZE ;i++) {
            m_attr.pin_assignment.address[i] = {0xff,0xff};
		  }
    }
    void set_bl(const mcu_pin_t * pin){
        int i=0;
        for (i =0; i< bl_bus_size_m;i++) {
            m_attr.pin_assignment.bl[i] = pin[i];
        }
        for (; i< MAX_BL_NUM;i++) {
            m_attr.pin_assignment.bl[i] = {0xff,0xff};
        }
    }
    void set_ncs(const mcu_pin_t * pin){
        int i=0;
        for ( i =0; i< ncs_bus_size_m;i++) {
            m_attr.pin_assignment.ncs[i] = pin[i];
        }
        for ( ; i< MAX_NCS_NUM;i++) {
            m_attr.pin_assignment.ncs[i] = {0xff,0xff};
        }
    }
    void set_oe(const mcu_pin_t & pin){ m_attr.pin_assignment.oe = pin; }
    void set_we(const mcu_pin_t & pin){ m_attr.pin_assignment.we = pin; }
    void set_nadv(const mcu_pin_t & pin){ m_attr.pin_assignment.nadv = pin; }
    void set_nwait(const mcu_pin_t & pin){ m_attr.pin_assignment.nwait = pin; }

    const mcu_pin_t * pins_data() const { return (const mcu_pin_t *)m_attr.pin_assignment.data; }
    const mcu_pin_t * pins_address() const { return (const mcu_pin_t *)m_attr.pin_assignment.address; }
    const mcu_pin_t * pins_bl() const { return (const mcu_pin_t *)m_attr.pin_assignment.bl; }
    const mcu_pin_t * pins_ncs() const { return (const mcu_pin_t *)m_attr.pin_assignment.ncs;; }
    mcu_pin_t oe() const { return m_attr.pin_assignment.oe; }
    mcu_pin_t we() const { return m_attr.pin_assignment.we; }
    mcu_pin_t nadv() const { return m_attr.pin_assignment.nadv; }
    mcu_pin_t nwait() const { return m_attr.pin_assignment.nwait; }
private:
    u8 data_bus_size_m = 16;
    u8 address_bus_size_m = 18;
    u8 bl_bus_size_m = 2;
    u8 ncs_bus_size_m = 1;
};

typedef EmcAttributes EmcAttr;


class EmcPinAssignment : public PinAssignment<emc_pin_assignment_t>{};

class Emc: public Periph<emc_info_t, emc_attr_t, EmcAttributes, EMC_IOC_IDENT_CHAR> {
public:
    Emc(port_t port);
    enum {
				flag_disable = EMC_FLAG_DISABLE,
				flag_enable = EMC_FLAG_ENABLE,
				flag_is_sdram  = EMC_FLAG_IS_SDRAM,
				flag_is_psram = EMC_FLAG_IS_PSRAM,
				flag_is_sram = EMC_FLAG_IS_SRAM,
				flag_is_nor = EMC_FLAG_IS_NOR,
				flag_is_nand = EMC_FLAG_IS_NAND,
				flag_is_8b_access = EMC_FLAG_IS_8B_ACCESS,
				flag_is_16b_access = EMC_FLAG_IS_16B_ACCESS,
				flag_is_32b_access = EMC_FLAG_IS_32B_ACCESS ,
				flag_is_ahb = EMC_FLAG_IS_AHB ,	/*!< use only data bus without address*/
				flag_is_psram_bank1 = EMC_FLAG_IS_PSRAM_BANK1 ,	/*!< use subbank BANK1 - cs0*/
				flag_is_psram_bank2 = EMC_FLAG_IS_PSRAM_BANK2 ,	/*!< use subbank BANK2 - cs1*/
				flag_is_psram_bank3 = EMC_FLAG_IS_PSRAM_BANK3 ,	/*!< use subbank BANK3 - cs2*/
				flag_is_psram_bank4 = EMC_FLAG_IS_PSRAM_BANK4,	/*!< use subbank BANK4 - cs3*/
				flag_ahb_write_data = EMC_FLAG_AHB_WRITE_DATA,	/*!< write data throuth ahb */
				flag_ahb_write_reg = EMC_FLAG_AHB_WRITE_REG,	/*!< write reg  throuth ahb*/
    };
    /**
     * @brief set_attr
     * @param o_flags
     * @param size psram in mbyte Ex. 0x80000 -> 524288 mbyte
     * @param base_address - Bank address Ex. 0x60000000
     * @param bus_width - data bus width
     * @param pin_assignment
     * @return
     */
    int set_attr(u32 o_flags,u32 size,u32 base_address,u8 bus_width, const emc_pin_assignment_t * pin_assignment = 0) const {
        emc_attr_t attr;
        memset(&attr,0,sizeof(emc_attr_t));
        memset(&attr.pin_assignment, 0xff, sizeof(emc_pin_assignment_t));
        if( pin_assignment != 0 ){
            memcpy(&attr.pin_assignment, pin_assignment, sizeof(emc_pin_assignment_t));
        }
        attr.size = size;
        attr.base_address = base_address;
        attr.o_flags = o_flags ;
        attr.data_bus_width = bus_width;
        return set_attributes(attr);
    }
    /**
     * @brief init
     * @param o_flags
     * @param size psram in mbyte Ex. 0x80000 -> 524288 mbyte
     * @param base_address - Bank address Ex. 0x60000000
     * @param bus_width - data bus width
     * @param pin_assignment
     * @return
     */
    int init(u32 o_flags,u32 size,u32 base_address,u8 bus_width, const emc_pin_assignment_t * pin_assignment = 0){
        o_flags |= FLAG_ENABLE;
        if( open(READWRITE) < 0 ){
            return -1;
        }
        return set_attr(o_flags,size,base_address,bus_width,pin_assignment);
    }
private:

};

class Emc_psram : public Emc {
public:
    Emc_psram(port_t port);/* : Emc( port){}*/
    /**
     * @brief Open and setattr for psram
     * @param o_flags Flags
     * @param size psram in mbyte Ex. 0x80000 -> 524288 mbyte
     * @param base_address - Bank address Ex. 0x60000000
     * @param bus_width - data bus width
     * @param pin_assignment
     * @return result of setattr
     */
    int init(u32 o_flags,u32 size,u32 base_address,u8 bus_width, const emc_pin_assignment_t * pin_assignment = 0){
        o_flags |= FLAG_IS_PSRAM | FLAG_ENABLE;
        if( open(READWRITE) < 0 ){
            return -1;
        }
        return set_attr(o_flags,size,base_address,bus_width,pin_assignment);
    }
    using Periph::get_channel;
#ifdef __MCU_ONLY__
    //using Pblock::write;
    //int write(const void * buf, int nbyte);
    int close();
#endif
private:
    int m_page_size;
};
class Emc_ahb : public Emc {
public:
    Emc_ahb(port_t port);/* : Emc( port){}*/
    /**
     * @brief init - open and setattr for with FLAG_IS_AHB flags
     * @param o_flags - flags
     * @param bus_width - data bus width
     * @param size - for ahb may be 0
     * @param base_address may be 0
     * @param pin_assignment
     * @return
     */
    int init(u32 o_flags, u32 size = 0,u32 base_address = 0,u8 bus_width = 16,const emc_pin_assignment_t * pin_assignment = 0){
        o_flags |= FLAG_IS_AHB | FLAG_ENABLE;
        if( open(READWRITE) < 0 ){
            return -1;
        }
        return set_attr(o_flags,size,base_address,bus_width,pin_assignment);
    }
    /**
     * @brief write_reg write reg throuth ahb interface
     * @param reg - reg value
     * @return les then zero value if error occured
     */
    int write_reg(u32 reg){
        emc_attr_t emc_attr;
        /* Send command */
        emc_attr.o_flags =EMC_FLAG_IS_AHB|EMC_FLAG_AHB_WRITE_REG;
        emc_attr.data_or_reg = reg;
        return ioctl(I_EMC_SETATTR, &emc_attr);
    }
    using Periph::get_channel;

#ifdef __MCU_ONLY__
    //using Pblock::write;
    //int write(const void * buf, int nbyte);
    int close();
#endif
private:
    int m_page_size;
};

}

/*! \endcond */


#endif // SAPI_HAL_EMC_HPP_
