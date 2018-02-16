/**
 * @file
 * This file implements functions to receive
 * and transmit CAN frames via a SLCAN adapter.
 */

#include <SLCAN.h>
#include <stdint.h>
// printf
#include <stdio.h>
// strncpy
#include <string.h>
// close
#include <unistd.h>

#include <string.h>
#include <stdlib.h>
#include <fcntl.h>


SLCAN::SLCAN()
   :CANAdapter(),
    tty_fd(-1),
    receiver_thread_id(0)
{
    adapter_type = ADAPTER_SOCKETCAN;
    printf("SLCAN adapter created.\n");
}


SLCAN::~SLCAN()
{
    printf("Destroying SLCAN adapter...\n");
    if (this->is_open())
    {
        this->close();
    }
}


void SLCAN::open(char* port)
{
    printf("Opening serial port %s ...\n", port);

    tty_fd = ::open(port, O_RDWR | O_NONBLOCK);

    if (tty_fd == -1)
    {
        printf("Opening serial port failed.\n");
        return;
    }
    printf("Opened port with file descriptor %d.\n", tty_fd);

    memset(&tio,0,sizeof(tio));

    cfsetispeed(&tio, B115200);            // 115200 baud
    cfsetospeed(&tio, B115200);            // 115200 baud

    tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;

    tcsetattr(tty_fd, TCSANOW, &tio);

    printf("Configured port parameters.\n");

    // Start a separate, event-driven thread for frame reception
    start_receiver_thread();
}


void SLCAN::close()
{
    terminate_receiver_thread = true;
    ::close(tty_fd);
    tcsetattr(STDOUT_FILENO, TCSANOW, &old_stdio);

    printf("SLCAN: Serial port closed.\n");
}


bool SLCAN::is_open()
{
    return (tty_fd != -1);
}


void SLCAN::transmit(can_frame_t* frame)
{
    CANAdapter::transmit(frame);

    if (!is_open())
    {
        printf("Unable to transmit: Socket not open\n");
        return;
    }

    // TODO
    printf("Transmission via SLCAN is not yet implemented.\n");
}


static void* slcan_receiver_thread(void* argv)
{
    // Get this thread's owner object
    SLCAN* adapter = (SLCAN*) argv;

    char rx_buffer[SLCAN_MTU];
    uint8_t rx_size = 0;

    // Run until termination signal received
    while (!adapter->terminate_receiver_thread)
    {
        // TODO: Perform select() on open serial port

        // TODO: Read from serial port

        if (rx_buffer[rx_size] == SLCAN_TERMINATOR)
        {
            // TODO: Construct and yield CAN frame
        }
    }

    // Thread terminates
    return NULL;
}


void SLCAN::start_receiver_thread()
{
    /*
     * Frame reception is accomplished using a separate, event-driven thread.
     */
    terminate_receiver_thread = false;
    int rc = pthread_create(&receiver_thread_id, NULL, &slcan_receiver_thread, this);
    if (rc != 0)
    {
        printf("Unable to start receiver thread.\n");
        return;
    }
    printf("Successfully started receiver thread with ID %d.\n", (int) receiver_thread_id);
}
