/*--------------------------------------------------------------------------------------

 dmd_cyrillic_chars
   Demo and example UTF-8 encoding project for the Freetronics DMD, a 512 LED matrix display
   panel arranged in a 32 x 16 layout.

See http://www.freetronics.com/dmd for resources and a getting started guide. */

/*--------------------------------------------------------------------------------------
  Includes
--------------------------------------------------------------------------------------*/
#include <DMD_STM32.h> 
#include "SystemFont5x7.h"
#include "Arial_Black_16_ISO_8859_1.h"
#include "UkrRusArial14.h";

// We'll use SPI 1   
SPIClass dmd_spi(1);

// We'll use timer 2
HardwareTimer timer(2);


//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1

// ----- Select pins for P10 matrix connection ------------
// pins A, B, SCLK may be any digital I/O, pin nOE should be PWM pin as PB1,PA8

// SPI specific pins as CLK and R_DATA has predefined values:
//   for SPI(1) CLK = PA5  R_DATA = PA7
//   for SPI(2) CLK = PB13  R_DATA = PB15
// --------------------------------------------------------

#define DMD_PIN_A PB11
#define DMD_PIN_B PB10
#define DMD_PIN_OE PB1
#define DMD_PIN_SCLK PB0
DMD dmd(DMD_PIN_A, DMD_PIN_B, DMD_PIN_OE, DMD_PIN_SCLK, DISPLAYS_ACROSS, DISPLAYS_DOWN, dmd_spi );
/*--------------------------------------------------------------------------------------
  Timer2 ch1 setup 
--------------------------------------------------------------------------------------*/
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
   dmd.brightness =20000;
}

/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
--------------------------------------------------------------------------------------*/
void loop(void)
{
   dmd.clearScreen( true );
   dmd.selectFont(UkrRusArial_14);
   const char *MSG = "Привет Ардуино";
   dmd.drawMarquee(MSG,strlen(MSG),(32*DISPLAYS_ACROSS)-1,0);
   dmd.brightness =20000;
   long prev_step =millis();
   
   while(1){
     if ((millis() - prev_step) > 50 ) {
       dmd.stepMarquee(-1,0);
       prev_step=millis();
      
     }
   }
}

