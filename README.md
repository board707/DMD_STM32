# DMD_STM32a - development branch of DMD_STM32 with RGB panels support
![GitHub last commit (branch)](https://img.shields.io/github/last-commit/board707/DMD_STM32/dev-V2) ![GitHub commits since tagged version (branch)](https://img.shields.io/github/commits-since/board707/DMD_STM32/v0.6.3) ![GitHub](https://img.shields.io/github/license/board707/DMD_STM32?color=g)
### The last version is v.0.6.11. For more stable beta [see 0.6.3](https://github.com/board707/DMD_STM32/releases/tag/v0.6.3)
This code branch is further development of [DMD_STM32 library](https://github.com/board707/DMD_STM32/tree/master). The code was rewritten by 70%, the library received a modular structure with a DMD_STM32a base class and several child classes for various matrices and connection types. Major change is **support of RGB matrix panels.** For more details on RGB matrices, [ see here.](https://cdn-learn.adafruit.com/downloads/pdf/32x16-32x32-rgb-led-matrix.pdf)

The principles of handling RGB matrices are based on RGBMatrixPanel library https://github.com/adafruit/RGB-matrix-Panel, with a changes, necessary to port code to STM32 controllers. For a start, the code can work with the following types of RGB matrices:

- 32x16 8scan
- 64x32 16scan
- 80x40 20scan
- 64x64 32scan
- 128x64 32 scan

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
(15 Jan 2022 - v0.6.11) - Fix incorrect string bounds for Standard and GFXFonts - Fix artefacts in Parallel Monochrome mode - Add ability to choose timer for OE other than Tim3

For full version history see [CHANGES.txt](CHANGES.txt)

Compatible IDE and libraries
----------
This library works with Arduino IDE 1.8, other versions are **not tested**. Roger Clarks's repo https://github.com/rogerclarkmelbourne/Arduino_STM32 is required to support STM32 based boards on Arduino IDE.

DMD_STM32a project requires Adafruit_GFX library version prior to 1.8.0 (v1.7.0 is OK) https://github.com/adafruit/Adafruit-GFX-Library/releases/tag/1.7.0

Compatible boards
-----------------

* STM32 - only STM32F103C8TB (bluepill) board tested !

Documentation
-----------
No english documentation available (hopefully yet). See examples.

Detailed info about matrix connection availiable at russian: [Wiki: Connections (rus)](https://github.com/board707/DMD_STM32/wiki/Connecting-for-Monochrome-(rus))

Repo stats
----------
Downloads since Jan23, 2022:  ![GitHub all releases](https://img.shields.io/github/downloads/board707/DMD_STM32/total)
