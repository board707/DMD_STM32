# DMD_STM32
Port of Freetronics DMD library (https://github.com/freetronics/DMD) for STM32Duino

This project based on DMDSTM by Evgen Mozok: https://github.com/mozok/DMDSTM

Notice
------
This software is experimental and a work in progress. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.

What works and not?
---------- 

* All examples of original DMD library are works
* Simple brightness control included (not fully tested)
* On the "bluepill" board can be used two independent DMD instances simultaneously - on SPI(1) and SPI(2) (see double_dmd example)
* Using more than one P10 matrix on channel are **not tested** yet.

Compatible IDE
----------
This library works with Arduino IDE 1.8, other versions are **not tested**

Compatible boards
-----------------

**The code only tested on STM32F103C8TB (bluepill) board !**

Connections
-----------

| DMD Signal | STM32 Pin | Comments |
| ---------- | --------- | -------- |
| A, B | PB6/PB7/PB10/PB11... | User adjustable, almost any digital pin, see exclusions |
| nOE | PA8/PB1... | User adjustable, should be PWM pin, see exclusions |
| CLK | PA5/PB13 for SPI(1)/SPI(2) | Predefined by SPI |
| SCLK | PB0/PB8... |  User adjustable, almost any digital pin, see exclusions |
| R_DATA | PA7/PB15 for SPI(1)/SPI(2) |  Predefined by SPI |

* **Exclusions:** Do not use these pins: PB3/PB4 (JTAG), PA11/PA12 (USB D+ D-) and PA15 - Timer(2) output
* For tested pin combinations see examples.
* Pulldown resistor 3-10K between nOE and GND is recommended.
