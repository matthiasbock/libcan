/**
 * @file
 * This file declares an interface to SocketCAN,
 * to facilitates frame transmission and reception.
 */

#include <CANAdapter.h>
#include <CANFrame.h>
#include <stdbool.h>

/**
 * Facilitates frame transmission and reception via a CAN adapter
 */
class SocketCAN: public CANAdapter
{
  private:
    /**
     * CAN socket file descriptor
     */
	int sockfd;

  public:
	/** Constructor */
	SocketCAN();
	/** Destructor */
	~SocketCAN();

	/**
	 * Open and bind socket
	 */
	void open();

	/**
	 * Returns whether the socket is open or closed
	 *
	 * @retval true     Socket is open
	 * @retval false    Socket is closed
	 */
	bool is_open();

	/**
	 * Close and unbind socket
	 */
	void close();

	/**
	 * Sends the referenced frame to the bus
	 */
	void transmit(can_frame_t*);
};
