/**
 * @file
 * This file implements functions to receive
 * and transmit CAN frames via SocketCAN.
 */

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
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
*/


SocketCAN::SocketCAN()
   :CANAdapter(),
    sockfd(-1)
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
        printf("Error creating a CAN socket\n");
        return;
    }
    printf("CAN socket created.\n");

    // Get the index of the network interface
    strncpy(if_request.ifr_name, interface, IFNAMSIZ);
    if (ioctl(sockfd, SIOCGIFINDEX, &if_request) == -1)
    {
        printf("Unable to select CAN interface %s: I/O control error\n", interface);

        // Invalidate unusable socket
        close();
        return;
    }


}


void SocketCAN::close()
{
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
