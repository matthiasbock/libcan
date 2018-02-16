/**
 * @file
 * This file declares an interface to an SLCAN adapter,
 * to facilitates frame transmission and reception.
 */

#ifndef SLCAN_H
#define SLCAN_H

#include <stdbool.h>
#include <CANAdapter.h>
#include <CANFrame.h>
#include <termios.h>

// Multi-threading
#include <pthread.h>


#define SLCAN_MTU           30
#define SLCAN_TERMINATOR    '\r'


/**
 * Facilitates frame transmission and reception via a CAN adapter
 */
class SLCAN: public CANAdapter
{
  private:
    struct termios tio;
    struct termios stdio;
    struct termios old_stdio;
    int tty_fd;
    pthread_t receiver_thread_id;

  public:
    /**
     * Request for the child thread to terminate
     */
    bool terminate_receiver_thread = false;

    /** Constructor */
    SLCAN();
    /** Destructor */
    ~SLCAN();

    /**
     * Open and bind socket
     */
    void open(char*);

    /**
     * Close and unbind socket
     */
    void close();

    /**
     * Returns whether the socket is open or closed
     *
     * @retval true     Socket is open
     * @retval false    Socket is closed
     */
    bool is_open();

    /**
     * Sends the referenced frame to the bus
     */
    void transmit(can_frame_t*);

    /**
     * Starts a new thread, that will wait for socket events
     */
    void start_receiver_thread();
};

#endif
