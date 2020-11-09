/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.

#ifndef SAPI_SYS_MQ_HPP_
#define SAPI_SYS_MQ_HPP_

#ifndef __link

#include <sos/link.h>
#include <mqueue.h>
#include <fcntl.h>
#include <cstring>
#include "../api/SysObject.hpp"
#include "../var/ConstString.hpp"
#include "../fs/Stat.hpp"


namespace sys {

class Mq;

/*! \brief Message Queue Attribute Class */
class MqAttributes {
	friend class Mq;
public:
	MqAttributes(){ memset(&m_attr, 0, sizeof(m_attr)); }
	MqAttributes(long f, long m, long s){
		m_attr.mq_flags = f;
		m_attr.mq_curmsgs = 0;
		m_attr.mq_maxmsg = m;
		m_attr.mq_msgsize = s;
	}

	/*! \details Message queue attribute flags */
	enum open_flags {
		open_nonblock /*! \brief Non-blocking queue */ = LINK_O_NONBLOCK,
		open_read_write /*! \brief Read/write queue */ = LINK_O_RDWR,
		open_read_only /*! \brief Read only queue */ = LINK_O_RDONLY,
		open_write_only /*! \brief Write only queue */ = LINK_O_WRONLY
	};

	long flags() const { return m_attr.mq_flags; }
	long current_message_count() const { return m_attr.mq_curmsgs; }
	long maximum_message_count() const { return m_attr.mq_maxmsg; }
	long message_size() const { return m_attr.mq_msgsize; }

	long curmsgs() const { return m_attr.mq_curmsgs; }
	long maxmsg() const { return m_attr.mq_maxmsg; }
	long msgsize() const { return m_attr.mq_msgsize; }

	MqAttributes & set_flags(long v) { m_attr.mq_flags = v; return *this; }
	MqAttributes & set_current_message_count(long v) { m_attr.mq_curmsgs = v; return *this; }
	MqAttributes & set_maximum_message_count(long v) { m_attr.mq_maxmsg = v; return *this; }
	MqAttributes & set_message_size(long v) { m_attr.mq_msgsize = v; return *this; }

private:
	struct mq_attr m_attr;
};

/*! \brief Message Queue Class */
/*! \details This class is a wrapper for POSIX message queues.
 *
 */
class Mq : public api::WorkObject {
public:
	Mq();

	/*! \details Bitwise flags for open() */
	enum flags {
		flag_create /*! \brief Create a new message queue */ = O_CREAT,
		flag_exclusive /*! \brief Create exclusively */ = O_EXCL
	};


	/*! \details Opens a message queue.
	 *
	 * @param name The name of the message queue
	 * @param oflag Open flags
	 * @param mode Access mode
	 * @param attr Pointer to attributes
	 * @return Less than zero for an error (use perror())
	 */
	int open(
			const var::String & name,
			int oflag,
			const fs::Permissions & permissions = fs::Permissions(0666),
			const struct mq_attr * attr = 0
			);

	/*! \details Creates a new message queue.
	 *
	 * @param name  The name of the queue
	 * @param oflag EXCLUSIVE or 0
	 * @param mode Permissions
	 * @param flags Message queue flags
	 * @param maxmsg Max number of messages
	 * @param msgsize Message size
	 * @return Less than zero for an error (use perror())
	 */
	int create(const var::String & name,
			int oflag,
			const fs::Permissions & permissions,
			long flags,
			long maxmsg,
			long msgsize
			);

	/*! \brief Closes the message queue. */
	int close();

	/*! \details Returns true if the message queue is open. */
	bool is_open() const { return m_handle != -1; }

	/*! \details Is not currently supported. */
	int notify(const struct sigevent *notification);

	/*! \details Copies message queue attributes to mqstat. */
	int get_attr(struct mq_attr & mqstat);

	/*! \details Returns a copy of the message queue attributes. */
	MqAttributes get_attributes();

	int set_attributes(const struct mq_attr * mqstat, struct mq_attr * omqstat = 0);

	/*! \details Sets the message queue attributes.
	  *
	  * The flags() value can be set using this method.
	  *
	  * The maxmsg(), msgsize() and curmsgs() are ignored (these
	  * properties are not mutable.
	  *
	  */
	int set_attributes(const MqAttributes & attributes);

	Mq & operator << (const MqAttributes & attributes){
		set_attributes(attributes);
		return *this;
	}

	/*! \details Receives a message from the queue.
	 *
	 * @param msg_ptr A pointer to the destination message
	 * @param msg_len The number of bytes available in \a msg_ptr
	 * @return The number of bytes read
	 *
	 */
	s32 receive(char * msg_ptr, u32 msg_len);

	s32 timedreceive(char * msg_ptr, u32 msg_len, const struct timespec * abs_timeout);
	s32 receive_timed(char * msg_ptr, u32 msg_len, const struct timespec * abs_timeout){ return timedreceive(msg_ptr, msg_len, abs_timeout); }

	/*! \details Sends a message to the queue.
	 *
	 * @param msg_ptr A pointer to the message to send
	 * @param msg_len The number of bytes to send
	 * @param msg_prio The message priority (default is 0, lowest priority)
	 * @return The number of bytes sent
	 *
	 */
	int send(const char * msg_ptr, u32 msg_len, unsigned msg_prio = 0);

	/*! \details Send a message to the queue with a timeout */
	int timedsend(const char * msg_ptr, u32 msg_len, unsigned msg_prio, const struct timespec * abs_timeout);
	int send_timed(const char * msg_ptr, u32 msg_len, unsigned msg_prio, const struct timespec * abs_timeout){ return timedsend(msg_ptr, msg_len, msg_prio, abs_timeout); }

	/*! \details Deletes a named message queue. */
	static int unlink(const char * name);

	/*! \details Returns the message priority of last message received. */
	unsigned message_priority() const { return m_msg_prio; }
	unsigned msg_prio() const { return m_msg_prio; }

private:
	mqd_t m_handle;
	unsigned m_msg_prio;
};

}

#endif

#endif /* SAPI_SYS_MQ_HPP_ */
