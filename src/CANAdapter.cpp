
#include <CANAdapter.h>
#include <stdio.h>


CANAdapter::CANAdapter()
    :adapter_type(ADAPTER_NONE),
     reception_handler(NULL)
{
    printf("CAN adapter created.\n");
}


CANAdapter::~CANAdapter()
{
    printf("Destroying CAN adapter...\n");
}


void CANAdapter::transmit(can_frame_t* frame)
{
    if (adapter_type == ADAPTER_NONE)
    {
        printf("Unable to send: Unspecified CAN adapter\n");
        return;
    }
    printf("Transmitting frame...\n");
}
