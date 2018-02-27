
#ifndef CAN_FRAME_PARSER
#define CAN_FRAME_PARSER

#include <CANFrame.h>


class CANFrameParser
{
  public:
    CANFrameParser();
    virtual ~CANFrameParser();

    virtual void parse_frame(can_frame_t*);
};

#endif
