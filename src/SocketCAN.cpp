/**
 * @file
 * This file implements functions to receive
 * and transmit CAN frames via SocketCAN.
 */

#include <SocketCAN.h>
#include <stdio.h>

// close
#include <unistd.h>
// socket
#include <sys/socket.h>

/*
 * https://github.com/JCube001/socketcan-demo
 * http://blog.mbedded.ninja/programming/operating-systems/linux/how-to-use-socketcan-with-c-in-linux
 * https://github.com/linux-can/can-utils/blob/master/candump.c
 */

/*
#include <endian.h>
#include <net/if.h>
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


void SocketCAN::open()
{
    sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (sockfd == -1)
    {
        printf("Error opening CAN socket\n");
        return;
    }
    printf("CAN socket opened.\n");
}


void SocketCAN::close()
{
    if (!is_open())
        return;
    ::close(sockfd);

    printf("CAN socket closed.\n");
}


bool SocketCAN::is_open()
{
    return (sockfd != -1);
}


void SocketCAN::transmit(can_frame_t* frame)
{
    CANAdapter::transmit(frame);

    // TODO
    printf("Transmission via SocketCAN is not yet implemented.\n");
}
