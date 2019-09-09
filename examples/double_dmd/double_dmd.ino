/*--------------------------------------------------------------------------------------

 double_dmd

 Using of two instances of DMD class on SPI(1) and SPI(2) 
*/   



/*--------------------------------------------------------------------------------------
  Includes
--------------------------------------------------------------------------------------*/
#include <DMD_STM32.h> 
//#include "st_fonts/SystemFont5x7.h"
//#include "st_fonts/Arial_Black_16_ISO_8859_1.h"
#include "st_fonts/UkrRusArial14.h";
#include "gfx_fonts/GlametrixLight12pt7b.h"
#include "gfx_fonts/GlametrixBold9pt7b.h"

// We'll use SPI_1 for first DMD and SPI_2 for second
SPIClass dmd_spi(1);
SPIClass dmd_spi2(2);

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
#define DMD_PIN_SCLK PA3

//Fire up the DMD library at first as dmd
DMD dmd(DMD_PIN_A, DMD_PIN_B, DMD_PIN_nOE, DMD_PIN_SCLK, DISPLAYS_ACROSS, DISPLAYS_DOWN, dmd_spi );

#define DMD2_PIN_A PA10
#define DMD2_PIN_B PA9
#define DMD2_PIN_nOE PB0
#define DMD2_PIN_SCLK PA8 

// and at second as dmd2
DMD dmd2(DMD2_PIN_A, DMD2_PIN_B, DMD2_PIN_nOE, DMD2_PIN_SCLK, DISPLAYS_ACROSS, DISPLAYS_DOWN, dmd_spi2 );

// --- Define fonts ----
// DMD.h old style font
DMD_Standard_Font UkrRusArial_F(UkrRusArial_14);

// GFX font with sepatate parts for Latin and Cyrillic chars
DMD_GFX_Font GlametrixL((uint8_t*)&GlametrixLight12pt7b,(uint8_t*)&GlametrixLight12pt8b_rus,0x80,13);
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
   // initialize Timer
    Timer3.setMode(TIMER_CH4, TIMER_OUTPUTCOMPARE);
    Timer3.setPeriod(3000);          // in microseconds
    Timer3.setCompare(TIMER_CH4, 1); // overflow might be small
    Timer3.attachInterrupt(TIMER_CH4, ScanDMD);
   
   //clear/init the DMD pixels held in RAM
   dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
  dmd2.clearScreen( true );  
  
  
}
int utf8_rus(char* dest, const unsigned char* src) {
  
  uint8_t i, j;
  for ( i =0, j =0; src[i]; i++) {
   if ((src[i] == 0xD0 )&& src[i+1])  { dest[j++] = src[++i] - 0x10;}
    else if ((src[i] == 0xD1 )&& src[i+1]) {dest[j++] = src[++i] + 0x30;  }
    else dest[j++] = src[i];
  }
  dest[j] ='\0';
  return j;
}
/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
--------------------------------------------------------------------------------------*/
void loop(void)
{
   
   dmd.selectFont(&UkrRusArial_F);
   const char *MSG = "Привет Ардуино";
   dmd.drawMarquee(MSG,strlen(MSG),(32*DISPLAYS_ACROSS)-1,0);
   // set brightness ( 0-65536, default is 30000)
   dmd.setBrightness(4000);
   long prev_step =millis();

   dmd2.clearScreen( true );
   dmd2.selectFont(&GlametrixL);
   char k[30];
   const unsigned char MSG2[] = "Привет STM32";
   utf8_rus(k,MSG2);
   dmd2.drawMarquee(k,strlen(k),(32*DISPLAYS_ACROSS)-1,0);
   dmd2.setBrightness(2000);
   
   while(1){
     if ((millis() - prev_step) > 50 ) {
       dmd.stepMarquee(-1,0);
       dmd2.stepMarquee(-1,0);
       prev_step=millis();
      
     }
   }
}

