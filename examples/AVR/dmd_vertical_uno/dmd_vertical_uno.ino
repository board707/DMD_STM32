/*--------------------------------------------------------------------------------------

 dmd_cyrillic_chars

  DMD_STM32 example code for Atmega328 board
  */

/*--------------------------------------------------------------------------------------
  Includes
--------------------------------------------------------------------------------------*/
#include <DMD_STM32.h> 
#include <TimerOne.h> 
//#include "st_fonts/SystemFont5x7.h"
//#include "st_fonts/Arial_Black_16_ISO_8859_1.h"
#include "st_fonts/UkrRusArial14.h";
#include "gfx_fonts/GlametrixLight12pt7b.h"
#include "gfx_fonts/GlametrixBold9pt7b.h"


// We'll use SPI 1   
SPIClass dmd_spi;

//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1

// ----- Select pins for P10 matrix connection ------------
// pins A, B, SCLK may be any digital I/O, pin nOE should be PWM pin as PB1,PA8


// --------------------------------------------------------

#define DMD_PIN_A 6
#define DMD_PIN_B 7
#define DMD_PIN_OE 9
#define DMD_PIN_SCLK 8
DMD dmd(DMD_PIN_A, DMD_PIN_B, DMD_PIN_OE, DMD_PIN_SCLK, DISPLAYS_ACROSS, DISPLAYS_DOWN, dmd_spi );


// --- Define fonts ----
// DMD.h old style font
DMD_Standard_Font UkrRusArial_F(UkrRusArial_14);

// GFX font with sepatate parts for Latin and Cyrillic chars
DMD_GFX_Font GlametrixL((uint8_t*)&GlametrixLight12pt7b,(uint8_t*)&GlametrixLight12pt8b_rus,0x80,13);
//DMD_GFX_Font GlametrixBold((uint8_t*)&GlametrixBold9pt7b,(uint8_t*)&GlametrixBold9pt8b_rus, 0x80, 11); 


/*--------------------------------------------------------------------------------------
  UTF8 char recoding
 
--------------------------------------------------------------------------------------*/
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
   

   //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
   Timer1.initialize( 3000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
   Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()
   
  //clear/init the DMD pixels held in RAM
   dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
   
}

/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
--------------------------------------------------------------------------------------*/
void loop(void)
{
   
   const unsigned char m[] = "Привет Ардуино!";
   char k[30];
   dmd.selectFont(&UkrRusArial_F);
   const char *MSG = "DMD STM32";
   dmd.drawString(0, 0, MSG, strlen(MSG), GRAPHICS_NORMAL);
   delay(5000);
   dmd.clearScreen( true ); 
   dmd.selectFont(&GlametrixL);
   utf8_rus(k,m);
   dmd.drawMarquee(k,strlen(k),(32*DISPLAYS_ACROSS)-1,0,1);
   
   long prev_step =millis();
   
   while(1){
     if ((millis() - prev_step) > 30 ) {
       dmd.stepMarquee(-1,0,1);
       prev_step=millis();
      
     }
   }
}
