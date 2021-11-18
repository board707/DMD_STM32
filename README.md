# DMD_STM32 with Unicode fonts support 
### Attention - this branch contains old version of library, for new [see here](https://github.com/board707/DMD_STM32/tree/dev-V2)
The library is STM32 port of Freetronics DMD library (https://github.com/freetronics/DMD) and designed to make it easy to display graphics and scrolling text on p10 DMD 32x16 matrix display. Its fundamental difference from the original DMD library is support of Adafruit GFX format fonts: https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts. Using Adafruit `fontconvert` utility allows users to convert and display on DMD matrix Truetype fonts, including Unicode fonts with national characters of almost any language.

Last version of the code has significantly improved performance through the use of DMA for SPI transfer. You can connect up to 16 DMD matrices on channel without significant slowing down the main program code

Initial version of STM32 specific code based on DMDSTM by Evgen Mozok: https://github.com/mozok/DMDSTM

Notice
------
This software is experimental and a work in progress. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.

What works and not?
---------- 

* All examples adopted from original DMD library are works
* Adafruit_GFX fonts can be used on drawString() and drawMarquee() routines (see dmd_cyr_chars example)
* Simple brightness control included (STM32 only)
* On the "bluepill" board can be used two independent DMD instances simultaneously - on SPI(1) and SPI(2) (see double_dmd example)
* On STM run up to 16 DMD matrices on channel without significant performance loss (6 tested)  

Example videos
--------------
* Two simultaneous scrolling texts on STM32 https://youtu.be/OCpLTLpwgRI
* Displaying text with converted Unicode font (Cyrillic) https://youtu.be/9xUB8-jk5Tc
* Vertical scrolling text https://youtu.be/JNL-5qp6bDc

Versions
---------
This branch is contain the stable version 0.4.2 of the code. Development version of the library [see here](https://github.com/board707/DMD_STM32/tree/dev-V2)

For version history see [CHANGES.txt](CHANGES.txt)

Compatible IDE
----------
This library works with Arduino IDE 1.8, other versions are **not tested**

Compatible boards
-----------------

* STM32 - only STM32F103C8TB (bluepill) board tested !
* AVR - Atmega328

Connections
-----------

| DMD Signal | STM32 Pin | Comments |
| ---------- | --------- | -------- |
| A, B | PB6/PB7/PB10/PB11... | User adjustable, almost any digital pin, see exclusions |
| nOE | PB0/PB1 | Should be TIMER3 PWM pin
| CLK | PA5/PB13 for SPI(1)/SPI(2) | Predefined by SPI |
| SCLK | PB11/PB8... |  User adjustable, almost any digital pin, see exclusions |
| R_DATA | PA7/PB15 for SPI(1)/SPI(2) |  Predefined by SPI |

* **Exclusions:** Do not use these pins: PB3/PB4 (JTAG), PA11/PA12 (USB D+ D-) 
* For tested pin combinations see examples.
* Pulldown resistor 3-10K between nOE and GND is recommended.

For detailed info about matric connection see [Wiki: Connections](https://github.com/board707/DMD_STM32/wiki/Connecting-for-Monochrome-(rus))(russian)

Adapters
--------
Sometimes wiring can be tricky so here I will put links to useful PCB-boards for use with this code (are not affiliated with the DMD_STM32)
* [DMD-STM32 Shield for P10 LED Matrix Panel](https://www.tindie.com/products/lightwell/dmd-stm32-shield-for-p10-led-matrix-panel/)  Designed by LIGHTWELL in Bulgaria 

Acknowledgements
-----------
- Evgeny Fokin for testing and provided matrices.
- Eduard Yansapov - for testing.
