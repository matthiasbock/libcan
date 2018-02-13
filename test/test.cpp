
// sleep
#include <unistd.h>
// printf
#include <stdio.h>
// uintxx_t
#include <stdint.h>
#include <SocketCAN.h>


void rx_handler(can_frame_t* frame)
{
    // TODO: Do something here with the received frame
}


int main()
{
    SocketCAN* adapter = new SocketCAN();
    adapter->reception_handler = &rx_handler;
    adapter->open("can0");

    sleep(5);

    can_frame_t frame;
    frame.can_id = 0x123;
    frame.can_dlc = 3;
    frame.data[0] = 1;
    frame.data[1] = 2;
    frame.data[2] = 3;

    adapter->transmit(&frame);

    delete adapter;

    sleep(1.1);

    return 0;
}
