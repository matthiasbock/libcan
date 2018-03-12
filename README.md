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

Peak-Systeme PCAN-Basic and Vector XLLib are not Open Source
and can therefore not be part of this repository.
If you wish to compile this library with support for those two under Windows,
you need to download and add them manually.
