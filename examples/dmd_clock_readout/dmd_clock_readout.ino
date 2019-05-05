/*--------------------------------------------------------------------------------------

 dmd_clock_readout.cpp 
   Example clock readout project for the Freetronics DMD, a 512 LED matrix display
   panel arranged in a 32 x 16 layout.

 Copyright (C) 2011 Marc Alexander (info <at> freetronics <dot> com)

 See http://www.freetronics.com/dmd for resources and a getting started guide.

 Note that the DMD library uses the SPI port for the fastest, low overhead writing to the
 display. Keep an eye on conflicts if there are any other devices running from the same
 SPI port, and that the chip select on those devices is correctly set to be inactive
 when the DMD is being written to.

 USAGE NOTES
 -----------

 - Place the DMD library folder into the "arduino/libraries/" folder of your Arduino installation.
 - Get the TimerOne library from here: http://code.google.com/p/arduino-timerone/downloads/list
   or download the local copy from the DMD library page (which may be older but was used for this creation)
   and place the TimerOne library folder into the "arduino/libraries/" folder of your Arduino installation.
 - Restart the IDE.
 - In the Arduino IDE, you can open File > Examples > DMD > dmd_demo, or dmd_clock_readout, and get it
   running straight away!

 * The DMD comes with a pre-made data cable and DMDCON connector board so you can plug-and-play straight
   into any regular size Arduino Board (Uno, Freetronics Eleven, EtherTen, USBDroid, etc)
  
 * Please note that the Mega boards have SPI on different pins, so this library does not currently support
   the DMDCON connector board for direct connection to Mega's, please jumper the DMDCON pins to the
   matching SPI pins on the other header on the Mega boards.

 This example code is in the public domain.
 The DMD library is open source (GPL), for more see DMD.cpp and DMD.h

--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
  Includes
--------------------------------------------------------------------------------------*/
#include <DMD_STM32.h> 
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

// We'll use SPI 1   
SPIClass dmd_spi(1);

// We'll use timer 2
HardwareTimer timer(2);


//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1

// ----- Select pins for P10 matrix connection ------------
// pins A, B, SCLK may be any digital I/O, pin nOE should be PWM pin as PB1, PA8

// SPI specific pins as CLK and R_DATA has predefined values:
//   for SPI(1) CLK = PA5  R_DATA = PA7
//   for SPI(2) CLK = PB13  R_DATA = PB15
// --------------------------------------------------------
#define DMD_PIN_A PB11
#define DMD_PIN_B PB10
#define DMD_PIN_nOE PB1
#define DMD_PIN_SCLK PB0

DMD dmd(DMD_PIN_A, DMD_PIN_B, DMD_PIN_nOE, DMD_PIN_SCLK, DISPLAYS_ACROSS, DISPLAYS_DOWN, dmd_spi );

void Timer_2_Init() {
  
   // Pause the timer while we're configuring it
    timer.pause();

   // Set up period
    timer.setPeriod(3000); // in microseconds

    // Set up an interrupt on channel 1
    timer.setChannel1Mode(TIMER_OUTPUT_COMPARE);
    timer.setCompare(TIMER_CH1, 1);  // Interrupt 1 count after each update
    timer.attachCompare1Interrupt( ScanDMD );

    // Refresh the timer's count, prescale, and overflow
    timer.refresh();

    // Start the timer counting
    timer.resume();
}
/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets
  called at the period set in Timer1.initialize();
--------------------------------------------------------------------------------------*/
void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

/*--------------------------------------------------------------------------------------
  setup
  Called by the Arduino architecture before the main loop begins
--------------------------------------------------------------------------------------*/
void setup(void)
{
   // initialize Timer2
   Timer_2_Init();
   
   //clear/init the DMD pixels held in RAM
   dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
   dmd.selectFont(Arial_Black_16);
}
/*--------------------------------------------------------------------------------------
  Show clock numerals on the screen from a 4 digit time value, and select whether the
  flashing colon is on or off
--------------------------------------------------------------------------------------*/
void ShowClockNumbers( unsigned int uiTime, byte bColonOn )
{
   dmd.clearScreen(true);
   // set brightness ( 0-65536, default is 30000)
   dmd.brightness =20000;
   
   dmd.drawChar(  1,  3,'0'+((uiTime%10000)/1000), GRAPHICS_NORMAL );   // thousands
   dmd.drawChar(  8,  3, '0'+((uiTime%1000) /100),  GRAPHICS_NORMAL );   // hundreds
   dmd.drawChar( 17,  3, '0'+((uiTime%100)  /10),   GRAPHICS_NORMAL );   // tens
   dmd.drawChar( 25,  3, '0'+ (uiTime%10),          GRAPHICS_NORMAL );   // units
   if( bColonOn )
      dmd.drawChar( 15,  3, ':', GRAPHICS_OR     );   // clock colon overlay on
   else
      dmd.drawChar( 15,  3, ':', GRAPHICS_NOR    );   // clock colon overlay off
}


/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
--------------------------------------------------------------------------------------*/
void loop(void)
{
   unsigned int ui;
   
   // 10 x 14 font clock, including demo of OR and NOR modes for pixels so that the flashing colon can be overlayed
   ui = 1234;
   ShowClockNumbers( ui, true );
   delay( 1000 );
   ShowClockNumbers( ui, false );
   delay( 1000 );
   ShowClockNumbers( ui, true );
   delay( 1000 );
   ShowClockNumbers( ui, false );
   delay( 1000 );

   ui = 2345;
   ShowClockNumbers( ui, true );
   delay( 1000 );
   ShowClockNumbers( ui, false );
   delay( 1000 );
   ShowClockNumbers( ui, true );
   delay( 1000 );
   ShowClockNumbers( ui, false );
   delay( 1000 );
}
