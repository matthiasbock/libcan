/**
 * @file
 * This file defines can_frame_t as a derivative
 * of the CAN frame struct in <linux/can.h>.
 */

#ifndef CAN_FRAME_H
#define CAN_FRAME_H

// struct can_frame
#include <linux/can.h>
//#include <linux/can/raw.h>

/**
 * Holds the content of one CAN frame
 * Struct delcared in <linux/can.h>
 */
typedef struct can_frame can_frame_t;

#endif
