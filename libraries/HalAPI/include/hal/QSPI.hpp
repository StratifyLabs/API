/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
#ifndef SAPI_HAL_QSPI_HPP_
#define SAPI_HAL_QSPI_HPP_

/*! \cond */

#include <sapi/hal.hpp>
#include "sos/dev/qspi.h"
namespace hal {

/**
 * @brief The QSPIAttributes class
 */
class QSPIAttributes : public PinAssignmentPeriphAttributes<qspi_attr_t, qspi_pin_assignment_t> {
public:
	QSPIAttributes(u32 o_flags = QSPI_FLAG_SET_MASTER, u32 frequency = 1000000){
		m_attr.o_flags = o_flags;
		m_attr.freq	= frequency;
	}
	void set_data0(const mcu_pin_t & pin){ m_attr.pin_assignment.data[0] = pin; }
	void set_data1(const mcu_pin_t & pin){ m_attr.pin_assignment.data[1] = pin; }
	void set_data2(const mcu_pin_t & pin){ m_attr.pin_assignment.data[2] = pin; }
	void set_data3(const mcu_pin_t & pin){ m_attr.pin_assignment.data[3] = pin; }
	void set_sck(const mcu_pin_t & pin){ m_attr.pin_assignment.sck = pin; }
	void set_cs(const mcu_pin_t & pin){ m_attr.pin_assignment.cs = pin; }

	mcu_pin_t data0() const { return m_attr.pin_assignment.data[0]; }
	mcu_pin_t data1() const { return m_attr.pin_assignment.data[1]; }
	mcu_pin_t data2() const { return m_attr.pin_assignment.data[2]; }
	mcu_pin_t data3() const { return m_attr.pin_assignment.data[3]; }
	mcu_pin_t sck() const { return m_attr.pin_assignment.sck; }
	mcu_pin_t cs() const { return m_attr.pin_assignment.cs; }

};

typedef QSPIAttributes QSPIAttr;


class QSPIPinAssignment : public PinAssignment<qspi_pin_assignment_t>{};
/**
 * @brief The QSPI class
 */
class QSPI: public Periph<qspi_info_t, qspi_attr_t, QSPIAttributes, QSPI_IOC_IDENT_CHAR> {
public:
	QSPI(port_t port);/* : Periph(CORE_PERIPH_QSPI, port){}*/
	enum {
		flag_set_master = QSPI_FLAG_SET_MASTER /*! Configure the QSPI as master */ ,
		flag_is_read_mem_mapped_mode = QSPI_FLAG_IS_READ_MEM_MAPPED_MODE /*! Configure the QSPI as mem mapped mode(read only)*/ ,
		flag_is_clk_high_while_cs = QSPI_FLAG_IS_CLK_HIGH_WHILE_CS /*!<Clk goes high while nCS is released, else low*/ ,
		flag_is_flash_id_2 = QSPI_FLAG_IS_FLASH_ID_2 /*!<use flash 2, else 1*/,
		flag_is_instruction_1_line = QSPI_FLAG_IS_INSTRUCTION_1_LINE/*!<write command use one line instead 4*/ ,
		flag_is_instruction_4_line = QSPI_FLAG_IS_INSTRUCTION_4_LINE/*!<write command use one line instead 4*/ ,
		flag_is_address_8_bits = QSPI_FLAG_IS_ADDRESS_8_BITS    /*!<8-bit address, default 32*/,
		flag_is_address_16_bits = QSPI_FLAG_IS_ADDRESS_16_BITS   /*!<16-bit address, default 32*/,
		flag_is_address_24_bits = QSPI_FLAG_IS_ADDRESS_24_BITS   /*!<24-bit address, default 32*/ ,
		flag_is_address_32_bits = QSPI_FLAG_IS_ADDRESS_32_BITS   /*!<24-bit address, default 32*/ ,
		flag_is_address_1_line = QSPI_FLAG_IS_ADDRESS_1_LINE /*!<use addressed command*/ ,
		flag_is_address_4_lines = QSPI_FLAG_IS_ADDRESS_4_LINES /*!<use addressed command*/ ,
		flag_is_data_1_line = QSPI_FLAG_IS_DATA_1_LINE /*!<use addressed command*/,
		flag_is_data_4_lines = QSPI_FLAG_IS_DATA_4_LINES /*!<use addressed command*/ ,
		flag_read_register = QSPI_FLAG_READ_REGISTER /*!<use with QSPI_FLAG_IS_REGISTER_WIDTH_*/,
		flag_write_register = QSPI_FLAG_WRITE_REGISTER /*!<use with QSPI_FLAG_IS_REGISTER_WIDTH_*/,
		flag_is_register_width_8 = QSPI_FLAG_IS_REGISTER_WIDTH_8/*!<use with QSPI_FLAG_READ_REGISTER or QSPI_FLAG_WRITE_REGISTER*/,
		flag_is_register_width_16 = QSPI_FLAG_IS_REGISTER_WIDTH_16/*!<use with QSPI_FLAG_READ_REGISTER or QSPI_FLAG_WRITE_REGISTER*/,
		flag_is_register_width_24 = QSPI_FLAG_IS_REGISTER_WIDTH_24/*!<use with QSPI_FLAG_READ_REGISTER or QSPI_FLAG_WRITE_REGISTER*/,
		flag_is_register_width_32 = QSPI_FLAG_IS_REGISTER_WIDTH_32/*!<use with QSPI_FLAG_READ_REGISTER or QSPI_FLAG_WRITE_REGISTER*/
	};
	int set_attr(u32 o_flags, u32 freq,u8 width,u32 read_instruction,u32 read_instruction_mem_mapped,
							 u32 write_instruction,u32 dummy_cycle, const qspi_pin_assignment_t * pin_assignment = 0) const {
		qspi_attr_t attr;
		memset(&attr,0,sizeof(qspi_attr_t));
		memset(&attr.pin_assignment, 0xff, sizeof(qspi_pin_assignment_t));
		if( pin_assignment != 0 ){
			memcpy(&attr.pin_assignment, pin_assignment, sizeof(qspi_pin_assignment_t));
		}
		attr.freq = freq;
		attr.o_flags = o_flags;
		attr.width = width;    //2^26 - 64 mbytes
		attr.read_instruction = read_instruction;
		attr.mem_mapped_read_instruction = read_instruction_mem_mapped;
		attr.write_instruction = write_instruction;
		attr.dummy_cycle = dummy_cycle;
		return set_attributes(attr);
	}

	int init(u32 o_flags, u32 freq,u8 width,u32 read_command,u32 read_command_mem_mapped,
					 u32 write_command,u32 dummy_cycle, const qspi_pin_assignment_t * pin_assignment = 0){
		if( open(READWRITE) < 0 ){
			return -1;
		}
		return set_attr(o_flags, freq, width, read_command,read_command_mem_mapped,write_command,
										dummy_cycle, pin_assignment);
	}
	/**
		 * @brief write_reg sending command and data withouth address,
		 * use in command mode
		 *
		 * @param command - command
		 * @param data - pointer to data(max 4 byte used)
		 * @param flag_width - FLAG_IS_REGISTER_WIDTH_8 ,FLAG_IS_REGISTER_WIDTH_16,
		 * FLAG_IS_REGISTER_WIDTH_24,FLAG_IS_REGISTER_WIDTH_32
		 * @return zero
		 */
	int write_reg(u32 command,void * data,u32 flag_width){
		qspi_attr_t qspi_attr;
		u8 len;
		/*change mode for read operations*/
		memset(&qspi_attr,0,sizeof(qspi_attr_t));
		qspi_attr.o_flags = FLAG_WRITE_REGISTER;
		qspi_attr.o_flags |= flag_width;
		qspi_attr.command.opcode = command;
		switch (flag_width){
			case(QSPI_FLAG_IS_REGISTER_WIDTH_8):
				len =1;
				break;
			case(QSPI_FLAG_IS_REGISTER_WIDTH_16):
				len =2;
				break;
			case(QSPI_FLAG_IS_REGISTER_WIDTH_24):
				len =3;
				break;
			case(QSPI_FLAG_IS_REGISTER_WIDTH_32):
				len =4;
				break;
			default:
				len = 1;
		}
		memcpy(qspi_attr.command.data , data, len);

		ioctl(I_QSPI_SETATTR, &qspi_attr);
		return 0;
	}
	/**
		 * @brief read_reg read registers by command intead address use
		 * @param command - command
		 * @param data - pointer for reads data
		 * @param flag_width - FLAG_IS_REGISTER_WIDTH_8 ,FLAG_IS_REGISTER_WIDTH_16,
		 * FLAG_IS_REGISTER_WIDTH_24,FLAG_IS_REGISTER_WIDTH_32,FLAG_IS_INSTRUCTION_1_LINE,
		 * FLAG_IS_INSTRUCTION_4_LINE,FLAG_IS_DATA_1_LINE,FLAG_IS_DATA_4_LINE
		 * @return zero value
		 */
	int read_reg(u32 command,void * data,u32 flag_width){
		qspi_attr_t qspi_attr;
		u8 len;
		memset(&qspi_attr,0,sizeof(qspi_attr_t));
		qspi_attr.o_flags = QSPI_FLAG_READ_REGISTER ;
		qspi_attr.o_flags |= flag_width;
		qspi_attr.command.opcode = command;
		ioctl(I_QSPI_SETATTR, &qspi_attr);
		switch (flag_width){
			case(QSPI_FLAG_IS_REGISTER_WIDTH_8):
				len =1;
				break;
			case(QSPI_FLAG_IS_REGISTER_WIDTH_16):
				len =2;
				break;
			case(QSPI_FLAG_IS_REGISTER_WIDTH_24):
				len =3;
				break;
			case(QSPI_FLAG_IS_REGISTER_WIDTH_32):
				len =4;
				break;
			default:
				len = 1;
		}

		memcpy( data, qspi_attr.command.data, len);

		return 0;
	}
private:

};
/**
 * @brief The QSPI_FLASH class
 */
class QSPI_FLASH : public QSPI {
public:

	QSPI_FLASH(port_t port);/* : QSPI( port){}*/

	void set_commands(u32 read_status,u32 write_enable,u32 write_enabled,u32 write_in_progress){
		read_status_command = read_status;
		write_enable_command = write_enable;
		write_enabled_mask = write_enabled;
		write_in_progress_mask = write_in_progress;
	}
	void set_page_size(int page_size = 256){
		m_page_size = page_size;
	}
	/**
			* @brief  This function read the SR
			* @param  fd qspi file
			* @retval status reg
			*/
	u8 read_status_reg();
	/**
			* @brief  This function enter qspi mode and check state.
			*         need to set read_status_command before
			* @param  command - command to enter qspi
			* @param  check_mask - mask control , reads from status register
			* @retval less then zero if mode did't check
			*/
	int set_qspi_mode(u32 command,u8 check_mask);
	/**
			* @brief  This function set the QSPI memory in 4-byte address mode
			* @param  command - sended to
			* @retval None
			*/
	int set_to_four_bytes_address(u32 command);
	/**
			* @brief  This function send a Write Enable and wait it is effective.
			* @retval less then zero if mode did't check
			*/
	int write_enable();
	/**
			* @brief  This function configure the dummy cycles on memory chip side.
			* @param  dummy_and_strenght - masked value
			* @param  dummy_and_strenght_mask - mask for strenght and dummy
			* @param  read_config_command - command for read config register
			* @param  write_config_command - command for write config register
			* @retval None
			*/
	int set_dummy_cycles_and_strength(u8 dummy_and_strenght,u8 dummy_and_strenght_mask,
																		u32 read_config_command,u32 write_config_command);
	/**
			* @brief  Erases the specified block of the QSPI memory.
			* @param  block_address - block address to erase
			* @param  command - erase command
			* @retval QSPI memory status
			*/
	int erase_block(u32 block_address,u32 command);
	/**
		 * @brief write data
		 * @param address - address start
		 * @param buff pointer data to
		 * @param length - data length
		 * @retval value writed data
		 * */
	u16 read_flash(u32 address,u8* buff,u16 length);
	/**
		 * @brief write data
		 * @param address - address start
		 * @param buff pointer data from
		 * @param length - data length
		 * return length writed data
		 * */
	u16 write_flash(u32 address,u8* buff,u16 length);


	using Periph::get_channel;
#ifdef __MCU_ONLY__
	//using Pblock::write;
	//int write(const void * buf, int nbyte);
	int close();
#endif
private:
	u32 read_status_command;
	u32 write_enable_command;
	u32 write_enabled_mask;
	u32 write_in_progress_mask;
	int m_page_size;
};

}

/*! \endcond */


#endif //SAPI_HAL_QSPI_HPP_
