/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
#ifndef SAPI_HAL_SWITCHBOARD_HPP_
#define SAPI_HAL_SWITCHBOARD_HPP_

#include <sos/dev/switchboard.h>
#if !defined __link
#include <sos/fs/sysfs.h>
#endif
#include "Device.hpp"
#include "../var/ConstString.hpp"

namespace hal {

class Switchboard;

class SwitchboardFlags {
public:
	enum flags {
		flag_connect /*! Connect Flag */ = SWITCHBOARD_FLAG_CONNECT,
		flag_disconnect /*! Disconnect Flag */ = SWITCHBOARD_FLAG_DISCONNECT,
		flag_is_persistent /*! Is Persistent Flag */ = SWITCHBOARD_FLAG_IS_PERSISTENT,
		flag_is_fixed_size /*! Is Fixed Size Flag */ = 0,
		flag_is_connected /*! Connection is connected and running (otherwise IS_ERROR, IS_CANCELED, or IS_DESTROYED) */ = SWITCHBOARD_FLAG_IS_CONNECTED,
		flag_is_error /*! Stopped because of an error */ = SWITCHBOARD_FLAG_IS_ERROR,
		flag_is_canceled /*! Stopped because an operation was canceled */ = SWITCHBOARD_FLAG_IS_CANCELED,
		flag_is_destroyed /*! Stopped because the connection was destroyed */ = SWITCHBOARD_FLAG_IS_DESTROYED,
		flag_is_fill_zero /*! Fill output with zeros if no input data is available */ = SWITCHBOARD_FLAG_IS_FILL_ZERO,
		flag_is_input_non_blocking /*! Execute input transactions as non-blocking */ = SWITCHBOARD_FLAG_IS_INPUT_NON_BLOCKING,
		flag_is_output_non_blocking /*! Execute input transactions as non-blocking */ = SWITCHBOARD_FLAG_IS_OUTPUT_NON_BLOCKING,
		flag_is_fill_last_8 /*! Fill output with last byte of most recent packet */ = SWITCHBOARD_FLAG_IS_FILL_LAST_8,
		flag_is_fill_last_16 /*! Fill output with last 16-bit word of most recent packet */ = SWITCHBOARD_FLAG_IS_FILL_LAST_16,
		flag_is_fill_last_32 /*! Fill output with last 32-bit word of most recent packet */ = SWITCHBOARD_FLAG_IS_FILL_LAST_32,
		flag_is_fill_last_64 /*! Fill output with last 64-bit word of most recent packet */ = SWITCHBOARD_FLAG_IS_FILL_LAST_64
	};
};

/*! \brief Switchboard Terminal Class
 *
 * \details A Switchboard terminal defines
 * the data structure for either an input or an output.
 *
 * Inputs and outputs are defined identically. When
 * a terminal is passed to the Switchboard as an input
 * it will be read. And when passed as an output, it will
 * be written.
 *
 */
class SwitchboardTerminal : public api::InfoObject, public SwitchboardFlags {
public:

	/*!
	 * \details Constructs a new Switchboard terminal.
	 *
	 * \param name The name of the terminal (e.g. uart0 -- not /dev/uart0)
	 * \param loc The channel/location to read or write
	 * \param priority Zero for default priority
	 */
	SwitchboardTerminal(const var::String & name, int loc = 0, s8 priority = 0){
		set_name(name);
		set_loc(loc);
		set_priority(priority);
		m_terminal.bytes_transferred = 0;
	}

	/*! \details Constructs a terminal from a switchboard_terminal_t. */
	SwitchboardTerminal(const switchboard_terminal_t & terminal){
		m_terminal = terminal;
	}

	/*!
	 * \details Sets the name of the terminal.
	 * \param name A pointer to the terminal name
	 */
	void set_name(const var::String & name){
		m_terminal.name[LINK_NAME_MAX-1]=0; //guarantee zero termination
		strncpy(m_terminal.name, name.cstring(), LINK_NAME_MAX-1);
	}

	/*!
	 * \details Sets the location/channel of the terminal.
	 */
	void set_loc(int loc){ m_terminal.loc = loc; }

	/*! \details Sets the priority of the terminal. */
	void set_priority(s8 priority){ m_terminal.priority = priority; }

	/*! \details Returns the terminal's name. */
	var::String name() const { return m_terminal.name; }
	/*! \details Returns the terminal interrupt priority. */
	s8 priority() const { return m_terminal.priority; }
	/*! \details Returns the location/channel value for the terminal. */
	u32 loc() const { return m_terminal.loc; }
	/*! \details Returns the number of bytes transferred on the terminal. */
	u32 bytes_transferred() const { return m_terminal.bytes_transferred; }

private:
	friend class SwitchboardConnection;
	friend class Switchboard;
	switchboard_terminal_t m_terminal;
};

/*! \brief Switchboard Connection Class
 *
 */
class SwitchboardConnection : public api::InfoObject, public SwitchboardFlags {
public:

	/*! \details Constructs a new empty connection. */
	SwitchboardConnection(){
		memset(&m_connection, 0, sizeof(switchboard_connection_t));
		m_connection.id = invalid_id();
	}

	/*! \details Returns the value assigned to invalid index values. */
	static u16 invalid_id() { return (u16)-1; }

	/*! \details Returns true if the object holds valid information. */
	bool is_valid() const { return id() != invalid_id(); }

	/*! \details Constructs a connection with the specified terminals.
	 *
	 */
	SwitchboardConnection(const SwitchboardTerminal & input, const SwitchboardTerminal & output, s32 nbyte){
		MCU_UNUSED_ARGUMENT(nbyte);
		set_input(input);
		set_output(output);
	}

	/*! \details Sets the connection's input terminal. */
	void set_input(const SwitchboardTerminal & value){
		m_connection.input = value.m_terminal;
	}

	/*! \details Sets the connections's output terminal. */
	void set_output(const SwitchboardTerminal & value){
		m_connection.output = value.m_terminal;
	}

	/*! \details Returns the connection ID value.
	 *
	 * If this value is equal to invalid_id(), the connection
	 * is not valid.
	 *
	 */
	u16 id() const { return m_connection.id; }

	/*! \details Returns the number of bytes transferred on the last transaction.
	 *
	 * If this value is negative, then an error has occurred.
	 *
	 */
	s32 nbyte() const {
#if !defined __link
		if( m_connection.nbyte < 0 ){
			return SYSFS_GET_RETURN(m_connection.nbyte);
		}
#endif
		return m_connection.nbyte;
	}

	/*! \details Returns the status flags of the connection. */
	u32 o_flags() const { return m_connection.o_flags; }

	/*! \details Returns a copy of the input terminal. */
	SwitchboardTerminal input() const { return m_connection.input; }

	/*! \details Returns a copy of the output terminal. */
	SwitchboardTerminal output() const { return m_connection.output; }

	/*! \details Returns true if the connection has stopped on an error. */
	bool is_error() const {
		return (o_flags() & flag_is_error) != 0;
	}

	/*! \details Returns true if the connection stopped because an operation was canceled. */
	bool is_canceled() const {
		return (o_flags() & flag_is_canceled) != 0;
	}

	/*! \details Returns true if the connection has been destroyed. */
	bool is_destroyed() const {
		return (o_flags() & flag_is_destroyed) != 0;
	}

	/*! \details Returns true if the connection is currently running. */
	bool is_connected() const {
		return (o_flags() & flag_is_connected) != 0;
	}

	/*! \details Returns the error number associated with the is_stopped_on_error() condition. */
	int error_number() const {
#if !defined __link
		if( m_connection.nbyte < 0 ){
			return SYSFS_GET_RETURN_ERRNO(m_connection.nbyte);
		}
#endif
		return 0;
	}

	/*! \details Prints details about the connection on the standard output. */
	void print() const;

private:
	friend class Switchboard;
	switchboard_connection_t m_connection;
};

/*! \brief Switchboard Connection Class
 *
 */
class SwitchboardInfo : public api::InfoObject, public SwitchboardFlags {
public:
	SwitchboardInfo(){ memset(&m_info, 0, sizeof(m_info)); }

	/*! \details Returns the number of connections available. */
	u16 connection_count() const { return m_info.connection_count; }

	/*! \details Returns the switchboard's internal connection buffer size. */
	u16 connection_buffer_size() const { return m_info.connection_buffer_size; }

	/*! \details Returns the transaction limit of the switchboard. */
	u16 transaction_limit() const { return m_info.transaction_limit; }

	operator const switchboard_info_t & () const { return m_info; }
private:
	friend class Switchboard;
	switchboard_info_t m_info;
};

/*! \brief Switch board class
 * \details The Switchboard class is used to interface
 * with /dev/switchboard0 and similar devices.
 *
 * The switchboard can connect two devices together
 * such that when data is received on one device,
 * it will be written to another device.
 *
 * A good application for using the switchboard is connecting streaming audio devices together.
 *
 * \code
 * #include <sapi/hal.hpp>
 * Switchboard switchboard;
 * SwitchboardTerminal input("mic"); //will refer to /dev/mic
 * SwitchboardTerminal output("speaker"); //refers to /dev/speaker
 * SwitchboardConnection connection = switchboard.create_persistent_connnection(input, output);
 *
 * \endcode
 *
 *
 */
class Switchboard : public Device, public SwitchboardFlags {
public:

	/*! \details Constructs a new object. */
	Switchboard();

	/*!
	 * \details Opens a switch board
	 * \param name The path to the switchboard (default is /dev/swithboard0)
	 * \return Zero on success
	 *
	 * To open a different switchboard, use
	 * \code
	 * Switchboard sb1;
	 * sb1.open("/dev/switchboard1");
	 * \endcode
	 *
	 */
	int open(
			const var::String & name = "/dev/switchboard0",
			const fs::OpenMode & flags = fs::OpenMode::read_write()
			);

	/*! \details Gets the connection specified by id. */
	SwitchboardConnection get_connection(u16 id) const;

	/*! \details Reloads the latest status on the connection.
	 *
	 * @param connection A reference to the connection to reload
	 * @return Zero on success
	 *
	 * The \a connection parameter must have a valid id() value.
	 *
	 * \code
	 * Switchboard sb;
	 * sb.open();
	 * SwitchboardConnection connection = sb.get_connection(0); //assumes 0 is a valid connection
	 * printf("connection input bytes transferred %d\n", connection.input().bytes_transferred());
	 * sleep(1);
	 * sb.get_connection(connection); //grab the latest status
	 * printf("connection input bytes transferred %d\n", connection.input().bytes_transferred());
	 * \endcode
	 *
	 */
	int get_connection(SwitchboardConnection & connection) const;

	/*! \details Gets a free connection that can be used
	 * for a new connection.
	 *
	 * \return Less than zero if no connection is available
	 *
	 */
	int get_available_connection() const;

	/*! \details Returns the number of active connections. */
	int get_active_connection_count() const;



	/*!
	 * \details Creates a new persistent connection on the switchboard.
	 *
	 * \param input The input terminal
	 * \param output The output terminal
	 * \param nbyte The number of bytes to transfer per transaction (default is maximum)
	 * \param o_flags Additional flags to apply while creating the connection
	 * \return The id number of the new connection or less than zero for an error
	 *
	 * The connection will persist until it is disconnected using destroy_connection()
	 * or it encounters a read or write error.
	 *
	 */
	int create_persistent_connection(
			const SwitchboardTerminal & input,
			const SwitchboardTerminal & output,
			s32 nbyte = 65535,
			u32 o_flags = 0) const;

	/*!
	 * \details create_fixed_size_connection
	 * \param input The input terminal
	 * \param output The output terminal
	 * \param nbyte The number of bytes to transfer
	 * \return Zero on success or less than zero for an error
	 */
	int create_fixed_size_connection(
			const SwitchboardTerminal & input,
			const SwitchboardTerminal & output,
			s32 nbyte) const;

	/*!
	 * \details Destroys the specified connection.
	 *
	 * \param id The connection to disconnect
	 * \return Zero on success
	 *
	 * After a connection is destroyed, it can be used again.
	 * The connection may take some time to stop.
	 *
	 */
	int destroy_connection(u16 id) const;

	/*! \details Disconnects the specified connection.
	 *
	 * \param connection A reference to the connection
	 *
	 */
	int destroy_connection(SwitchboardConnection & connection);

	/*! \details Gets information from the switchboard. */
	int get_info(switchboard_info_t & info) const;

	/*! \details Gets information from the switchboard. */
	SwitchboardInfo get_info() const;

	void print_connections() const;

	/*! \details Sets the attributes of the switchboard.
	 *
	 * Use connect() and disconnect() to manage basic connections.
	 * This method can do more advanced features.
	 *
	 */
	int set_attr(switchboard_attr_t & attr) const;

};
}

#endif // SAPI_HAL_SWITCHBOARD_HPP_
