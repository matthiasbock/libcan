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
 * How a frame reception handler should look like
 */
typedef void (*reception_handler_t)(can_frame_t*);


/**
 * Facilitates frame transmission and reception via a CAN adapter
 */
class CANAdapter
{
  protected:
    can_adapter_t       adapter_type;

  public:
    /**
     * Pointer to a function which shall be called
     * when frames are being received from the CAN bus
     */
    reception_handler_t reception_handler;

    /** Constructor */
	CANAdapter();
	/** Destructor */
	virtual ~CANAdapter();

	/**
	 * Sends the referenced frame to the bus
	 */
	virtual void transmit(can_frame_t*);
};
