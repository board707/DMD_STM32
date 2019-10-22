/*--------------------------------------------------------------------------------------

 dmd_cyrillic_chars

  DMD_STM32 example code for STM32F103xxx board
 ------------------------------------------------------------------------------------- */

/*--------------------------------------------------------------------------------------
  Includes
--------------------------------------------------------------------------------------*/
#include <DMD_STM32.h> 
//#include "st_fonts/SystemFont5x7.h"
//#include "st_fonts/Arial_Black_16_ISO_8859_1.h"
#include "st_fonts/UkrRusArial14.h";
#include "gfx_fonts/GlametrixLight12pt7b.h"
#include "gfx_fonts/GlametrixBold12pt7b.h"

// We'll use SPI 2   
SPIClass dmd_spi(2);


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
#define DMD_PIN_B PB12
#define DMD_PIN_nOE PB1
#define DMD_PIN_SCLK PB10

DMD dmd(DMD_PIN_A, DMD_PIN_B, DMD_PIN_nOE, DMD_PIN_SCLK, DISPLAYS_ACROSS, DISPLAYS_DOWN, dmd_spi );


// --- Define fonts ----
// DMD.h old style font
DMD_Standard_Font UkrRusArial_F(UkrRusArial_14);

// GFX font with sepatate parts for Latin and Cyrillic chars
//DMD_GFX_Font GlametrixL((uint8_t*)&GlametrixLight12pt7b,(uint8_t*)&GlametrixLight12pt8b_rus,0x80,13);
DMD_GFX_Font GlametrixBold((uint8_t*)&GlametrixBold12pt7b,(uint8_t*)&GlametrixBold12pt8b_rus, 0x80, 13); 


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
  setup
  Called by the Arduino architecture before the main loop begins
--------------------------------------------------------------------------------------*/
void setup(void)
{
   dmd.init();
   dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
   // set matrix brightness (0-255)
   dmd.setBrightness(80);
}


/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
--------------------------------------------------------------------------------------*/
void loop(void)
{
   
   const unsigned char m[] = "Привет Ардуино!";
   char k[30];
   dmd.selectFont(&GlametrixBold);
   utf8_rus(k,m);
   dmd.drawMarquee(k,strlen(k),(32*DISPLAYS_ACROSS)-1,0);
   
   long prev_step =millis();
   
   while(1){
     if ((millis() - prev_step) > 50 ) {
       dmd.stepMarquee(-1,0);
       prev_step=millis();
      
     }
   }
}
