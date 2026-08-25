<img src="https://github.com/board707/DMD_STM32/blob/old-V1/.github/fok0.jpg" width="600" />

# DMD_STM32a - LED Matrix library with SPWM driver support

![GitHub last commit (branch)](https://img.shields.io/github/last-commit/board707/DMD_STM32/dev-V2) ![GitHub commits since tagged version (branch)](https://img.shields.io/github/commits-since/board707/DMD_STM32/v0.6.3) ![GitHub](https://img.shields.io/github/license/board707/DMD_STM32?color=g)

Brief introduction
------------------

This is a library that supports almost all types of monochrome and RGB LED panels using the HUB08, HUB12, and HUB75 interfaces. It runs on the STM32 and RP2040-based controllers in the Arduino environment.

The library’s main purpose is to collect knowledge about LED panel types and protocols. Please note: this project is not a finished product. It is an experimental platform for testing and implementing different software and hardware approaches for working with matrix panels.

There is no strict development plan. The project evolves in directions that interest the author and users. The project does not receive commercial support. The author would be grateful for your ideas, links to documentation, and samples of unusual panels and controllers for study.

If you find this library interesting, please consider starring it.

Latest updates
--------------

### Support for STMicroelectronics packages

Starting with v1.2.12, we began gradually adding support for STMicroelectronics (STM32duino) package for STM32. The Monochrome and RGB classes are partially implemented. RGB DMA mode and sPWM drivers are not yet supported.

The latest library versions are experimental and are not included in the official release. Please use the GitHub "Download" button to update. If you are using RP2040 or an STM32 with the old RogerClark add-on, we recommend still using release 1.2.11.

### Panels with a new SPWM drivers 

Since v1.2.5 release the library introduces comprehensive support for a set of new "PWM-type" LED drivers previously unsupported by most known libraries. The supported chips represents a three distinct PWM driver control architectures:
  * Unified Signal Control - both PWM timing and row switching managed by a single GCLK ( OE ) control signal  (supported: **ICN2153**, **FM6353**)
  * Dual Signal Synchronization - PWM timing coordinated through combined GCLK (OE -Output Enable) and  DCLK signals  ( driver model: **FM6363** )
  * Fully Decoupled Control Mechanism - PWM timing (DCLK) and row switching ( GCLK ) operated through completely independent signals (chips: **DP3264**, **ICND1065**,**ICND2055**, **FM6373** and **SM16380SH** )

Compatibility and Requirements: In case of STM32 core using a STM32F4 boards is strongly recommended. See [Notes about using a SPWM Drivers](https://github.com/board707/DMD_STM32/wiki/quick_start#notes-about-using-spwm-driver-classes) for details. Recommended to use a dmd_spwm_panel example as a starting point.

> Attention! Recent versions are incompatible with code prior v1.0.0 
> The main difference from 0.x.x versions is a new panel template format. You can see a brief explanation in the [Wiki/About matrix patterns](https://github.com/board707/DMD_STM32/wiki/Reference#appendix-a) and in the comments of the [DMD_Panel_Templates.h](https://github.com/board707/DMD_STM32/blob/dev-V2/DMD_Panel_Templates.h) file.  
> Last version with old panel templates [v0.9.5](https://github.com/board707/DMD_STM32/releases/tag/v0.9.5)

About the library
-----------------

The library initially started out as STM32 port of Freetronics DMD library (https://github.com/freetronics/DMD). Now it has grown into a separate project with support for different types of monochrome, two-color and RGB panels. 

One of the important features of the library is support of Adafruit GFX format fonts: https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts. Using Adafruit `fontconvert` utility allows users to convert and display on DMD matrix Truetype fonts, including Unicode fonts with national characters of almost any language. The library includes **Cyrillic** and **Turkish** fonts. For using of national fonts, see the examples `dmd_rgb.ino` and `dmd_rgb_turk.ino` (Turkish).

The main advantage of the library, which distinguishes it from its analogues, is the very wide range of supported RGB panels. Modules of almost any size, multiplexing type and scanning pattern can be used. All these are configured by "matrix pattern" - a strings of digits, represents a key characteristics of given panel. The library does provide to users a rich set of predefined matrix patterns, and if some panel is missing from the list, it can be easily added without changing the main library code.

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
| | | | | |
| RGB S-PWM driver panels         |     HUB75    |   128x64   |     1/32    | DMD_SPWM_Driver.h                             |
|  supports FM6353/6363/6373      |              |    64x32   |     1/16    |                                              |
|  ICND1065/2153/2055, DP3264, SM16380sh          | | | | |

Read more about supported panels in the [Wiki/Supported panels](https://github.com/board707/DMD_STM32/wiki/quick_start#supported-panels). The set of supported matrices is constantly updated.

**Adding a new panels to the library**

If your panel is not supported by the library yet, please feel free to open an issue using [template](https://github.com/board707/DMD_STM32/issues/new?assignees=&labels=&projects=&template=add-a-new-panel-template.md&title=Add+a+new+panel)

Other features
------------
 - The graphics subsystem is inherited from Adafruit GFX library https://github.com/adafruit/Adafruit-GFX-Library
 - Dual memory buffering for reducing scanning artifacts and making some visual effects (see [Wiki/Examples](https://github.com/board707/DMD_STM32/wiki/quick_start#examples)).
 - Two color modes for RGB: highcolor RGB444 and low memory consuming RGB111 mode for LED signs, information boards etc.
 - Multicolor strings for fixed text and scrolling (since v1.1.2)
 - Chaining up to 100 panels for Monochrome (46 tested) or 16 for RGB 64x32. The number of matrices is limited by the size of the controller memory.
 - For monochrome display - a new "Parallel" connection scheme, in which each horizontal row of panels is connected to a separate R_DATA pin


Compatible boards
-----------------

* STM32F1 — STM32F103C8/C6 (Roger Clark); STM32F103CBT (STM32duino, verified)
* STM32F4 — STM32F401CC, STM32F411CE (Roger Clark and STM32duino, verified)
* Raspberry Pi Pico and other RP2040-based boards. 
* RP2350 based boards should works as well, but not fully tested yet.

Installation
-------------

There are two ways to install the library:
* Download ZIP-archive directly from [Releases](https://github.com/board707/DMD_STM32/releases) section, open your Arduino IDE, click on `Sketch > Include Library > Add . ZIP Library`. Choose the zip file you just downloaded.
* Using Library Manager (since Arduino IDE 1.6.2): navigate to `Sketch > Include Library > Manage Libraries` inside your Arduino IDE and search for the library, then click `Install`.

#### Pre-installation requirements

* Adafruit_GFX library

    DMD_STM32a project requires [Adafruit GFX library](https://github.com/adafruit/Adafruit-GFX-Library)

   
#### Arduino support packages for STM32 and Raspberry Pi Pico

* STM32 — two cores, selected automatically at compile time:

  | Core | Arduino package | When active |
  |------|-----------------|-------------|
  | **Roger Clark (libmaple)** | [Arduino_STM32](https://github.com/rogerclarkmelbourne/Arduino_STM32) | `__STM32F1__` / `__STM32F4__`, without `ARDUINO_ARCH_STM32` |
  | **STM32duino** | [Arduino Core STM32](https://github.com/stm32duino/Arduino_Core_STM32) | `ARDUINO_ARCH_STM32` → `DMD_STM32DUINO` |

  Roger Clark uses the original path (`stm_int.h`, libmaple timers/GPIO). STM32duino uses a compatibility layer (`DMD_STM32duino.h` / `DMD_STM32duino.cpp`). Paths are split with `#if defined(DMD_STM32DUINO)`; building for one core does not replace the other.

  Upstream [board707/DMD_STM32](https://github.com/board707/DMD_STM32) documents Roger Clark only. STM32duino support is present in this tree as an additional port.

  > Roger Clark: core versions before [d05a128](https://github.com/rogerclarkmelbourne/Arduino_STM32/commit/d05a1289f1e2eaa5127a4bfed9602e2cd48c6ffe) (28 Apr 2024) are incompatible with recent Adafruit GFX. Use core ≥ d05a128 or Adafruit GFX ≤ 1.7.0 ([v1.7.0](https://github.com/adafruit/Adafruit-GFX-Library/releases/tag/1.7.0)).

  > STM32duino: both 2.x.x & recent 3.0.0 releases supported; using DMA in RGB modes are disabled, RGB uses bit-bang instead. Note that STM32duino core is not compatible with sPWM drivers support.

  **STM32duino port verified on:** STM32F103 (CBT), STM32F401, STM32F411 — RGB panels (`DMD_RGB`), dual buffer, GFX/Cyrillic fonts. Example: `examples/STM32duino/dmd_rgb_effects`.

* Raspberry Pi Pico/ Pico2

   This code requires Earle Philhower core https://github.com/earlephilhower/arduino-pico


Connection
----------
For detailed info about matrix connection see Wiki: 

* [Wiki: Connections for Monochrome panels](https://github.com/board707/DMD_STM32/wiki/Connections---Monochrome)
* [Wiki: Connections for RGB](https://github.com/board707/DMD_STM32/wiki/Connections---RGB)

Consult the examples for recommended pin combinations.

Documentation
-----------

* [Wiki: Home](https://github.com/board707/DMD_STM32/wiki/Home)
* [Quick start guide](https://github.com/board707/DMD_STM32/wiki/quick_start)
* [Examples](https://github.com/board707/DMD_STM32/wiki/quick_start#examples)
* [Library API Reference](https://github.com/board707/DMD_STM32/wiki/Reference)
* [LED Drivers Database](https://github.com/board707/DMD_STM32/wiki/Led_drivers)

Example videos
--------------
* Using of dual buffering to show fixed and scrolling text [https://youtu.be/DoOcfGb0PLw](https://youtu.be/DoOcfGb0PLw)
* Multicolor fixed and scrolling text [https://youtu.be/lw87UqoO50E](https://youtu.be/lw87UqoO50E)
* [Some other videos](https://github.com/board707/DMD_STM32/tree/old-V1#example-videos) are available at the page of old version of library.

Adapters
--------
Sometimes wiring can be tricky so here I will put links to useful PCB-boards for use with this code (are not affiliated with the DMD_STM32)
* [DMD-STM32 Shield for P10 Monochrome LED Matrix Panel](https://www.tindie.com/products/lightwell/dmd-stm32-shield-for-p10-led-matrix-panel/)  Designed by LIGHTWELL in Bulgaria 

Other most important versions
---------
(09 Dec 2025 - v1.2.4)  - Introduced a new class for SPWM type drivers

(22 Dec 2023 - v1.1.2)  - Introduced multicolor for fixed and scrolling text 

(30 Nov 2023 - v1.1.0)  - Add support of panels with FM6353/6363 S-PWM drivers

(25 Mar 2023 - v1.0.4)  - Add support of panels with FM6126a chip

(12 Feb 2023 - v1.0.0)  - New panel template model with multi-parameter specialization

(16 Sep 2022 - v0.9.0)  - Add support of RP2040-based boards and using the DMA in the RGB modes for STM32F4 boards

(10 Jul 2022 - v0.8.0)  - Add support of STM32F4 blackpills - STM32F401CC & STM32F411CE  (**Custom STM32 repo required!** see below)

(19 Feb 2022 - v0.7.0)  - Add support of "Outdoor" RGB panels with 1/2 1/4 1/8 scans

For full version history see [CHANGES.txt](CHANGES.txt)

Acknowledgements
-----------
- Evgeny Fokin for testing and provided matrices.
- Alexander Pikulik - for interesting panel with FM6373 SPWM driver.
- Eugeny Cherny - thanks for providing a panel with new driver.
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
