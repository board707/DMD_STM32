<img src="https://github.com/board707/DMD_STM32/blob/old-V1/.github/fok0.jpg" width="600" />

# DMD_STM32a - LED Matrix library with Unicode fonts support 

![GitHub last commit (branch)](https://img.shields.io/github/last-commit/board707/DMD_STM32/dev-V2) ![GitHub commits since tagged version (branch)](https://img.shields.io/github/commits-since/board707/DMD_STM32/v0.6.3) ![GitHub](https://img.shields.io/github/license/board707/DMD_STM32?color=g)
### Last version is v1.1.2 - Introduced multicolor for fixed and scrolling text 
<img src="https://github.com/board707/DMD_STM32/blob/old-V1/.github/dmd_multicolor_small.jpg" style="text-align: center" />

See [video](https://youtu.be/lw87UqoO50E) and dmd_multicolor example for details.

### Version v1.1.0 - Add support of F6353/FM6363 S-PWM drivers
### Attention! The repository was recently updated to v1.0.0
The main difference from 0.x.x versions is a new panel template format. The documentation will coming. You can get a brief explanation of the new templates from the comments of the [DMD_Panel_Templates.h](https://github.com/board707/DMD_STM32/blob/dev-V2/DMD_Panel_Templates.h) file.
### For last version with old panel templates [see v0.9.5](https://github.com/board707/DMD_STM32/releases/tag/v0.9.5)
The main improvement of the 0.9.x versions is the **support of the Raspberry Pi Pico and another RP2040-based boards**. Version 0.9.4 added Turkish font examples and some bugfixes.

About the library
-----------------

The library initially started out as STM32 port of Freetronics DMD library (https://github.com/freetronics/DMD). Now it has grown into a separate project with support for different types of monochrome, two-color and RGB panels. 

One of the important features of the library is support of Adafruit GFX format fonts: https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts. Using Adafruit `fontconvert` utility allows users to convert and display on DMD matrix Truetype fonts, including Unicode fonts with national characters of almost any language. The library includes **Cyrillic** and **Turkish** fonts. For using of national fonts, see the examples `dmd_rg.ino` and `dmd_rgb_turk.ino` (Turkish)

This code branch is further development of [DMD_STM32 library](https://github.com/board707/DMD_STM32/tree/old-V1). The code was totally rewritten, the library received a modular structure with a DMD_STM32a base class and several child classes for various matrices and connection types. 

LED panels supported
-----------------


| **Description**                 | **Interface** | **Pixels** |   **Scan**  | **Code module**                              |
|---------------------------------|:-------------:|:----------:|:-----------:|----------------------------------------------|
| Monochrome P10 panels           |     HUB12    |    32x16   |     1/4     | DMD_Monochrome_SPI.h <br/> DMD_Parallel.h  |
| | | | | |
| Indoor RGB                      |     HUB75    |    32x16   |     1/8     | DMD_RGB.h                                    |
|                                 |               |    32x32   |     1/16    |                                              |
|                                 |               |    64x32   |     1/16    |                                              |
|                                 |               |    64x64   |     1/32    |                                              |
|                                 |               |    80x40   |     1/20    |                                              |
|                                 |               |   128x64   |     1/32    |                                              |
| | | | | |
| Outdoor RGB                     |     HUB75    |    32x16   | 1/2 1/4 1/8 | DMD_RGB.h                                    |
| | | | | |
| Two-color indoor                |     HUB08    |    64x32   |     1/16    | DMD_RGB.h <br />  (work as RGB)          |
| | | | | |
| RGB with FM6126a driver         |     HUB75    |    64x32   |     1/16    | DMD_RGB_6126a.h                               |
| RGB with FM6353/6363 S-PWM drivers |     HUB75    |   128x64   |     1/32    | DMD_RGB_6353.h                             |
|                                 |               |    64x32   |     1/16    |                                              |

The set of supported matrices is constantly updated.

**Adding a new panels to the library**

If your panel is not supported by the library yet, please feel free to open an issue using [template](https://github.com/board707/DMD_STM32/issues/new?assignees=&labels=&projects=&template=add-a-new-panel-template.md&title=Add+a+new+panel)

Other features
------------
 - The graphics subsystem is inherited from Adafruit GFX library https://github.com/adafruit/Adafruit-GFX-Library
 - Dual memory buffering for reducing scanning artefacts and making some visual effects
 - Two color modes for RGB: highcolor RGB444 and low memory consuming RGB111 mode for LED signs, information boards etc.
 - Chaining up to 100 panels for Monochrome (46 tested) or 16 for RGB 64x32. The number of matrices is limited by the size of the controller memory.
 - For monochrome display - a new "Parallel" connection scheme, in which each horizontal row of panels is connected to a separate R_DATA pin


Attention! Pre-installation requirements
----------
This library works with Arduino IDE 1.6-1.9, Arduino IDE 2.x versions are **not tested**. 

**Adafruit_GFX library**

DMD_STM32a project **requires** Adafruit_GFX library version prior to 1.8.0 (v1.7.0 is OK) https://github.com/adafruit/Adafruit-GFX-Library/releases/tag/1.7.0

**STM32** 

The only Roger Clarks's repo https://github.com/rogerclarkmelbourne/Arduino_STM32 is supported for STM32 based boards on Arduino IDE.To support STM32F4 boards you need custom version of repo: https://github.com/board707/Arduino_STM32/tree/lto_for_c6

**Raspberry Pi Pico** 

This code **requires Earle Philhower core** https://github.com/earlephilhower/arduino-pico

Compatible boards
-----------------

* STM32F1 - STM32F103C8 (bluepill) and STM32F103C6 boards tested 
* STM32F4 - STM32F401CC and STM32F411CE boards (**Custom STM32 repo required!**)
* Raspberry Pi Pico and other RP2040-based boards 

Connection
----------
For detailed info about matrix connection see Wiki: 

Russian:
* [Wiki: Подключение монохромных панелей](https://github.com/board707/DMD_STM32/wiki/Connecting-for-Monochrome-(rus))
* [Wiki: Подключение RGB](https://github.com/board707/DMD_STM32/wiki/Connecting-for-RGB(rus))

English translation:

* [Wiki: Connections for Monochrome panels](https://github.com/board707/DMD_STM32/wiki/Connections---Monochrome)
* [Wiki: Connections for RGB](https://github.com/board707/DMD_STM32/wiki/Connections---RGB)

See the examples for recommended pin combinations.

Documentation
-----------
No documentation available (hopefully yet). See examples.

Example videos
--------------
* Using of dual buffereng to show fixed and scrolling text [https://youtu.be/DoOcfGb0PLw](https://youtu.be/DoOcfGb0PLw)
* Multicolor fixed and scrolling text [https://youtu.be/lw87UqoO50E](https://youtu.be/lw87UqoO50E)
* [Some other videos](https://github.com/board707/DMD_STM32/tree/old-V1#example-videos) are avaliable at the page of old version of library.

Adapters
--------
Sometimes wiring can be tricky so here I will put links to useful PCB-boards for use with this code (are not affiliated with the DMD_STM32)
* [DMD-STM32 Shield for P10 Monochrome LED Matrix Panel](https://www.tindie.com/products/lightwell/dmd-stm32-shield-for-p10-led-matrix-panel/)  Designed by LIGHTWELL in Bulgaria 

Most important versions
---------
(30 Nov 2023 - v1.1.0)  - Add support of panels with FM6353/6363 S-PWM drivers

(25 Mar 2023 - v1.0.4)  - Add support of panels with FM6126a chip

(12 Feb 2023 - v1.0.0)  - New panel template model with multiparameter specialization

(12 Dec 2022 - v0.9.2)  - Monochrome panels support for RP2040-based boards (Parallel connection mode)

(16 Sep 2022 - v0.9.0)  - Add support of RP2040-based boards (RGB modes only) and using the DMA in the RGB modes for STM32F4 boards

(10 Jul 2022 - v0.8.0)  - Add support of STM32F4 blackpills - STM32F401CC & STM32F411CE  (**Custom STM32 repo required!** see below)

(19 Feb 2022 - v0.7.0)  - Add support of "Outdoor" RGB panels with 1/2 1/4 1/8 scans

For full version history see [CHANGES.txt](CHANGES.txt)

Acknowledgements
-----------
- Evgeny Fokin for testing and provided matrices.
- Eduard Yansapov - for testing.
- @bilalibrir - for help with the code for Outdoor RGB matrix 

Credits to open source community
--------------------------------
* Initial version of STM32 specific code based on DMDSTM by Evgen Mozok: https://github.com/mozok/DMDSTM
* The principles of handling RGB matrices are based on Adafruit RGB-matrix-Panel library https://github.com/adafruit/RGB-matrix-Panel, with a changes, necessary to port code to STM32 controllers.
* Some other code solutions are inspired by [PxMatrix](https://github.com/2dom/PxMatrix) and [ESP32-HUB75-MatrixPanel-I2S-DMA](https://github.com/mrfaptastic/ESP32-HUB75-MatrixPanel-I2S-DMA) libraries

Notice
------
This software is experimental and a work in progress. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
