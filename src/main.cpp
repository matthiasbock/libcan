
#include <SocketCAN.h>
#include <iostream>


using namespace std;

int main()
{
    /*
     * Instantiate CAN adapter
     * This will automatically call the constructor.
     */
    SocketCAN can0;

    can0.open("can0");

    can_frame_t frame;
    frame.can_id = 0x123;
    frame.can_dlc = 3;
    frame.data[0] = 1;
    frame.data[1] = 2;
    frame.data[2] = 3;

    can0.transmit(&frame);

	return 0;
}
