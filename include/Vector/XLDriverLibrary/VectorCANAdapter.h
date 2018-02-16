/**
 * @file
 * This file declares a CAN adapter class,
 * which facilitates frame reception and transmission
 * via one of Vector's CAN adapters
 * using Vector's (binary,proprietary) XL driver library.
 *
 * Documentation about Vector's XL-Driver-Library:
 *  https://vector.com/vi_xl_driver_library_en.html
 *
 * The driver can be obtained from here:
 *  https://vector.com/vi_downloadcenter_en.html?product=XLLib&formular_treffer_submit=1
 *
 * This third-party software aims at establishing
 * compatibility with Vector's software and hardware.
 * The author is not affiliated with Vector.
 * Vector did neither endorse nor support this project.
 */

#if defined(ENABLE_VECTOR) && (!defined(VECTORCANADAPTER_H))
#define VECTORCANADAPTER_H

#include <CANAdapter.h>


class VectorCANAdapter: public CANAdapter
{

};

#endif
