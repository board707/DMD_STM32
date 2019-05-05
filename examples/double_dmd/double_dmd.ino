/*--------------------------------------------------------------------------------------

 double_dmd

 Using of two instances of DMD class on SPI(1) and SPI(2) 
*/   



/*--------------------------------------------------------------------------------------
  Includes
--------------------------------------------------------------------------------------*/
#include <DMD_STM32.h> 
#include "SystemFont5x7.h"
#include "Arial_Black_16_ISO_8859_1.h"
#include "UkrRusArial14.h";

// We'll use SPI_1 for first DMD and SPI_2 for second
SPIClass dmd_spi(1);
SPIClass dmd_spi2(2);

// We'll use timer 2 for ScanDMD()
HardwareTimer timer(2);



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
#define DMD_PIN_nOE PB1
#define DMD_PIN_SCLK PB0

//Fire up the DMD library at first as dmd
DMD dmd(DMD_PIN_A, DMD_PIN_B, DMD_PIN_nOE, DMD_PIN_SCLK, DISPLAYS_ACROSS, DISPLAYS_DOWN, dmd_spi );


#define DMD2_PIN_A PB7
#define DMD2_PIN_B PB6
#define DMD2_PIN_nOE PA8
#define DMD2_PIN_SCLK PB8

// and at second as dmd2
DMD dmd2(DMD2_PIN_A, DMD2_PIN_B, DMD2_PIN_nOE, DMD2_PIN_SCLK, DISPLAYS_ACROSS, DISPLAYS_DOWN, dmd_spi2 );
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
  dmd2.scanDisplayBySPI();
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
  dmd2.clearScreen( true );  
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
   // set brightness ( 0-65536, default is 30000)
   dmd.brightness =20000;
   long prev_step =millis();

   dmd2.clearScreen( true );
   dmd2.selectFont(UkrRusArial_14);
   const char *MSG2 = "Привет STM32";
   dmd2.drawMarquee(MSG2,strlen(MSG2),(32*DISPLAYS_ACROSS)-1,0);
   dmd2.brightness =20000;
   
   while(1){
     if ((millis() - prev_step) > 50 ) {
       dmd.stepMarquee(-1,0);
       dmd2.stepMarquee(-1,0);
       prev_step=millis();
      
     }
   }
}

