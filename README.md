# libcan

This repository contains code to simplify the development of cross-platform CAN-capable programs in C/C++.

## Features
It aims to support several CAN devices:

Linux:
  * all SocketCAN and SLCAN devices, specifically:
  * CANtact (SLCAN)
  * Peak-Systeme PCAN-USB (SocketCAN)

Windows:
  * CANtact (SLCAN)
  * Peak-Systeme PCAN-USB (via proprietary PCAN-Basic API)
  * Vector VN1630A (via proprietary XLLib)

Planned features:
* Support for import and replay of Vector CANalyzer log files

# License

Author: Matthias Bock

License: GNU GPLv3

Peak-Systeme's PCAN-Basic API and Vector's XLLib are not Open Source.
Not even the distribution of the binaries is unrestricted.
Therefore, unfortunately, these libraries can't be part of this repository.
If you wish to compile libcan under Windows with support for Peak-Systeme or Vector devices,
you need to download and add the corresponding libraries manually.

## Non-free add-ons

### PCANBasic API

The "PCANBasic API" is basically a DLL binary plus header files,
which allows development of software that makes use of Peak-Systeme's CAN adapters.
It can be downloaded without registration and free of charge, but without source code, from here:
* https://www.peak-system.com/Support.55.0.html

Excerpt from the ZIP file's ReadMe.txt:
```
PEAK-System Technik GmbH grants the right to the customer to use the files in
this software package as long as this is done in connection with original
hardware by PEAK-System or OEM hardware coming from PEAK-System. It is NOT
allowed to use any of these files (even not parts) with third-party hardware.
```

**Note**:

Under Linux you won't need the PCANBasic API as
an Open Source driver exists for Peak-Systeme's CAN adapters,
which appears to work perfectly.

### Vector XLLib

The "XL Driver Library" ("XLLib" for short) is a library,
which allows development of software that makes use of Vector's CAN adapters.
It (an installer EXE in a ZIP) can be downloaded without registration and free of charge, but without source code, from here:
* https://vector.com/vi_downloadcenter_en.html?product=xllib

libcan support for XLLib may come at a later point,
but is postponed for now,
since the effort-payoff ratio doesn't look so good to me right now.
Apparently there even is license-checking in the library...
looks like it could be a mess, trying to get something to actually work with that,
not to mention, writing a program with it, that also runs under Linux.

**Note**:

As of march 2018, none of Vector's CAN devices are not supported under Linux at all,
not even with non-free software.
