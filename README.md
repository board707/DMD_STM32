<img src="https://github.com/board707/DMD_STM32/blob/old-V1/.github/fok0.jpg" width="600" />

# DMD_STM32a - LED Matrix library with Unicode fonts support 

![GitHub last commit (branch)](https://img.shields.io/github/last-commit/board707/DMD_STM32/dev-V2) ![GitHub commits since tagged version (branch)](https://img.shields.io/github/commits-since/board707/DMD_STM32/v0.6.3) ![GitHub](https://img.shields.io/github/license/board707/DMD_STM32?color=g)
### The last version is v.0.6.11. For more stable beta [see 0.6.3](https://github.com/board707/DMD_STM32/releases/tag/v0.6.3)
The library initially started out as STM32 port of Freetronics DMD library (https://github.com/freetronics/DMD). Now it has grown into a separate project with support for different types of monochrome, two-color and RGB panels. One of the important features of the library is support of Adafruit GFX format fonts: https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts. Using Adafruit `fontconvert` utility allows users to convert and display on DMD matrix Truetype fonts, including Unicode fonts with national characters of almost any language.

This code branch is further development of [DMD_STM32 library](https://github.com/board707/DMD_STM32/tree/old-V1). The code was totally rewritten, the library received a modular structure with a DMD_STM32a base class and several child classes for various matrices and connection types. At the moment the library has been tested with the following types of matrices:

| **Description**                 | **Interface** | **Pixels** |   **Scan**  | **Code module**                              |
|---------------------------------|:-------------:|:----------:|:-----------:|----------------------------------------------|
| Monochrome P10 panels           |     HUB12    |    32x16   |     1/4     | DMD_Monochrome_SPI.h <br/> DMD_Parallel.h  |
| | | | | |
| Indoor RGB                      |     HUB75    |    32x16   |     1/8     | DMD_RGB.h                                    |
|                                 |               |    64x32   |     1/16    |                                              |
|                                 |               |    64x64   |     1/32    |                                              |
|                                 |               |    80x40   |     1/20    |                                              |
|                                 |               |   128x64   |     1/32    |                                              |
| | | | | |
| Outdoor RGB                     |     HUB75    |    32x16   | 1/2 1/4 1/8 | DMD_RGB.h                                    |
| | | | | |
| Two-color indoor                |     HUB08    |    64x32   |     1/16    | DMD_RGB.h <br />  (work as RGB)          |
| | | | | |
| RGB with FM6216a driver         |     HUB75    |    64x32   |     1/16    | experimental, contact author                               |
| RGB with FM6353 s-pwm type driver |     HUB75    |   128x64   |     1/32    | experimental, contact author                               |

The set of supported matrices is constantly updated.

Other features
------------
 - The graphics subsystem is inherited from Adafruit GFX library https://github.com/adafruit/Adafruit-GFX-Library
 - Dual memory buffering for reducing scanning artefacts and making some visual effects
 - Two color modes for RGB: highcolor RGB444 and low memory consuming RGB111 mode for LED signs, information boards etc.
 - Chaining up to 100 panels for Monochrome (46 tested) or 16 for RGB 32x16. The number of matrices is limited by the size of the controller memory.
 - For monochrome display - a new "Parallel" connection scheme, in which each horizontal row of panels is connected to a separate R_DATA pin


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

Connection
----------
Detailed info about matrix connection availiable at russian: 
* [Wiki: Connections for Monochrome panels (rus)](https://github.com/board707/DMD_STM32/wiki/Connecting-for-Monochrome-(rus))
* [Wiki: Connections for RGB (rus)](https://github.com/board707/DMD_STM32/wiki/Connecting-for-RGB(rus))

Documentation
-----------
No english documentation available (hopefully yet). See examples.

Example videos
--------------
[Some videos](https://github.com/board707/DMD_STM32#example-videos) are avaliable at the page of old version of library.

Adapters
--------
Sometimes wiring can be tricky so here I will put links to useful PCB-boards for use with this code (are not affiliated with the DMD_STM32)
* [DMD-STM32 Shield for P10 Monochrome LED Matrix Panel](https://www.tindie.com/products/lightwell/dmd-stm32-shield-for-p10-led-matrix-panel/)  Designed by LIGHTWELL in Bulgaria 

Acknowledgements
-----------
- Evgeny Fokin for testing and provided matrices.
- Eduard Yansapov - for testing.
- @bilalibrir - for help with the code for Outdoor RGB matrix 

Notice
------
This software is experimental and a work in progress. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.


Repo stats
----------
Downloads since Jan23, 2022:  ![GitHub all releases](https://img.shields.io/github/downloads/board707/DMD_STM32/total)
