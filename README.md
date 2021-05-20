# DMD_STM32a - development branch of DMD_STM32 with RGB panels support
This code branch is further development of DMD_STM32 library. The code was rewritten by 70%, the library received a modular structure with a DMD_STM32a base class and several child classes for various matrices and connection types. Major change is **support of RGB matrix panels.** For more details on RGB matrices, [ see here.](https://cdn-learn.adafruit.com/downloads/pdf/32x16-32x32-rgb-led-matrix.pdf)

The principles of handling RGB matrices are based on RGBMatrixPanel library https://github.com/adafruit/RGB-matrix-Panel, with a changes, necessary to port code to STM32 controllers. For a start, the code can work with the following types of RGB matrices:

- 32x16 8scan
- 64x32 16scan
- 80x40 20scan
- 64x64 32scan

The number of matrices is limited by the size of the controller memory.

#### Other improvements:
 - The graphics subsystem is now inherited from Adafruit GFX library https://github.com/adafruit/Adafruit-GFX-Library
 - Dual memory buffering for reducing scanning artefacts and making some visual effects
 - For monochrome display - a new "Parallel" connection scheme, in which each horizontal row of panels is connected to a separate R_DATA pin
 

Notice
------
This software is experimental and a work in progress. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.

Versions
---------
For version history see [CHANGES.txt](CHANGES.txt)

Compatible IDE and libraries
----------
This library works with Arduino IDE 1.8, other versions are **not tested**. Roger Clarks's repo https://github.com/rogerclarkmelbourne/Arduino_STM32 is required to support STM32 based boards on Arduino IDE.

DMD_STM32a project requires Adafruit_GFX library version prior to 1.8.0 (v1.7.0 is OK) https://github.com/adafruit/Adafruit-GFX-Library/releases/tag/1.7.0

Compatible boards
-----------------

* STM32 - only STM32F103C8TB (bluepill) board tested !

Documentation
-----------
No documentation available (hopefully yet). See examples for connection.
