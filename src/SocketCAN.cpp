/**
 * @file
 * This file implements functions to receive
 * and transmit CAN frames via SocketCAN.
 */

#ifndef MINGW

#include <SocketCAN.h>
#include <stdio.h>
// strncpy
#include <string.h>
// close
#include <unistd.h>
// socket
#include <sys/socket.h>
// SIOCGIFINDEX
#include <sys/ioctl.h>

/*
 * https://github.com/JCube001/socketcan-demo
 * http://blog.mbedded.ninja/programming/operating-systems/linux/how-to-use-socketcan-with-c-in-linux
 * https://github.com/linux-can/can-utils/blob/master/candump.c
 */

/*
#include <endian.h>
#include <sys/socket.h>
#include <sys/types.h>
*/


SocketCAN::SocketCAN()
   :CANAdapter(),
    sockfd(-1),
    receiver_thread_id(0)
{
    adapter_type = ADAPTER_SOCKETCAN;
    printf("SocketCAN adapter created.\n");
}


SocketCAN::~SocketCAN()
{
    printf("Destroying SocketCAN adapter...\n");
    if (this->is_open())
    {
        this->close();
    }
}


void SocketCAN::open(char* interface)
{
    // Request a socket
    sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (sockfd == -1)
    {
        printf("Error: Unable to create a CAN socket\n");
        return;
    }
    printf("Created CAN socket with descriptor %d.\n", sockfd);

    // Get the index of the network interface
    strncpy(if_request.ifr_name, interface, IFNAMSIZ);
    if (ioctl(sockfd, SIOCGIFINDEX, &if_request) == -1)
    {
        printf("Unable to select CAN interface %s: I/O control error\n", interface);

        // Invalidate unusable socket
        close();
        return;
    }
    printf("Found: %s has interface index %d.\n", interface, if_request.ifr_ifindex);

    // Bind the socket to the network interface
    addr.can_family = AF_CAN;
    addr.can_ifindex = if_request.ifr_ifindex;
    int rc = bind(
        sockfd,
        reinterpret_cast<struct sockaddr*>(&addr),
        sizeof(addr)
    );
    if (rc == -1)
    {
        printf("Failed to bind socket to network interface\n");

        // Invalidate unusable socket
        close();
        return;
    }
    printf("Successfully bound socket to interface %d.\n", if_request.ifr_ifindex);

    // Start a separate, event-driven thread for frame reception
    start_receiver_thread();
}


void SocketCAN::close()
{
    terminate_receiver_thread = true;

    if (!is_open())
        return;

    // Close the file descriptor for our socket
    ::close(sockfd);
    sockfd = -1;

    printf("CAN socket destroyed.\n");
}


bool SocketCAN::is_open()
{
    return (sockfd != -1);
}


void SocketCAN::transmit(can_frame_t* frame)
{
    CANAdapter::transmit(frame);
    if (!is_open())
    {
        printf("Unable to transmit: Socket not open\n");
        return;
    }

    // TODO
    printf("Transmission via SocketCAN is not yet implemented.\n");
}


static void* socketcan_receiver_thread(void* argv)
{
    /*
     * The first and only argument to this function
     * is the pointer to the object, which started the thread.
     */
    SocketCAN* sock = (SocketCAN*) argv;

    // Holds the set of descriptors, that 'select' shall monitor
    fd_set descriptors;

    // Highest file descriptor in set
    int maxfd = sock->sockfd;

    // How long 'select' shall wait before returning with timeout
    struct timeval timeout;

    // Buffer to store incoming frame
    can_frame_t rx_frame;

    // Run until termination signal received
    while (!sock->terminate_receiver_thread)
    {
        // Clear descriptor set
        FD_ZERO(&descriptors);
        // Add socket descriptor
        FD_SET(sock->sockfd, &descriptors);
//        printf("Added %d to monitored descriptors.\n", sock->sockfd);

        // Set timeout
        timeout.tv_sec  = 1;
        timeout.tv_usec = 0;

        // Wait until timeout or activity on any descriptor
        if (select(maxfd+1, &descriptors, NULL, NULL, &timeout) == 1)
        {
//            printf("Something happened.\n");
            int len = read(sock->sockfd, &rx_frame, CAN_MTU);
//            printf("Received %d bytes: Frame from 0x%0X, DLC=%d\n", len, rx_frame.can_id, rx_frame.can_dlc);

            if (len < 0)
                continue;

            if (sock->reception_handler != NULL)
            {
                sock->reception_handler(&rx_frame);
            }

            if (sock->parser != NULL)
            {
//                printf("Invoking parser...\n");
                sock->parser->parse_frame(&rx_frame);
            }
            else
            {
//                printf("sock->parser is NULL.\n");
            }
        }
        else
        {
//            printf("Received nothing.\n");
        }
    }

    printf("Receiver thread terminated.\n");

    // Thread terminates
    return NULL;
}


void SocketCAN::start_receiver_thread()
{
    /*
     * Frame reception is accomplished in a separate, event-driven thread.
     *
     * See also: https://www.thegeekstuff.com/2012/04/create-threads-in-linux/
     */
    terminate_receiver_thread = false;
    int rc = pthread_create(&receiver_thread_id, NULL, &socketcan_receiver_thread, this);
    if (rc != 0)
    {
        printf("Unable to start receiver thread.\n");
        return;
    }
    printf("Successfully started receiver thread with ID %d.\n", (int) receiver_thread_id);
}

#endif
