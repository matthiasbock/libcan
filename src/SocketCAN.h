/**
 * @file
 * This file declares an interface to SocketCAN,
 * to facilitates frame transmission and reception.
 */

#include <CANAdapter.h>
#include <CANFrame.h>
#include <stdbool.h>

// IFNAMSIZ, ifreq
#include <net/if.h>

/**
 * Interface request structure used for socket ioctl's
 */
typedef struct ifreq interface_request_t;


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

    interface_request_t if_request;

  public:
	/** Constructor */
	SocketCAN();
	/** Destructor */
	~SocketCAN();

	/**
	 * Open and bind socket
	 */
	void open(char*);

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
