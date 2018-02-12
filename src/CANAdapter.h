/**
 * @file
 * This file declares a generic CANAdapter,
 * to facilitate frame transmission and reception.
 */

#include <CANFrame.h>

/**
 * Specifies the type of a CAN adapter
 */
typedef enum
{
    ADAPTER_NONE,
    ADAPTER_SOCKETCAN,
    ADAPTER_SLCAN,
} can_adapter_t;


/**
 * Facilitates frame transmission and reception via a CAN adapter
 */
class CANAdapter
{
  protected:
    can_adapter_t adapter_type;

  public:
	/** Constructor */
	CANAdapter();
	/** Destructor */
	virtual ~CANAdapter();

	/**
	 * Sends the referenced frame to the bus
	 */
	virtual void transmit(can_frame_t*);
};
