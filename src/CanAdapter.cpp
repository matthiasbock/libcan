
#include <CanAdapter.h>

#include <stdio.h>

#include <unistd.h>  // close
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <linux/can.h>
#include <linux/can/raw.h>

/*
#include <endian.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
*/

CanAdapter::CanAdapter()
{
    sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (sockfd == -1)
    {
        printf("Error opening CAN socket\n");
        return;
    }
    printf("CAN socket opened.\n");
}

CanAdapter::~CanAdapter()
{
    if (sockfd == -1)
        return;
    close(sockfd);

    printf("CAN socket closed.\n");
}
