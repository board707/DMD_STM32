/*--------------------------------------------------------------------------------------

 DMD_STM32.cpp  - STM32 port of DMD.h library (see below)
 
 adapted by Dmitry Dmitriev (c) 2019
 
 DMD.cpp - Function and support library for the Freetronics DMD, a 512 LED matrix display
           panel arranged in a 32 x 16 layout.

 Copyright (C) 2011 Marc Alexander (info <at> freetronics <dot> com)

 ---

 This program is free software: you can redistribute it and/or modify it under the terms
 of the version 3 GNU General Public License as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with this program.
 If not, see <http://www.gnu.org/licenses/>.

--------------------------------------------------------------------------------------*/
#include "DMD_STM32.h"


#if defined(__STM32F1__)
static volatile DMD* running_dmds[2];
static volatile uint8_t running_dmd_len =0;
static uint16_t scan_int = 2000;

static void register_running_dmd(DMD *dmd)
{
  uint8_t spi_num =dmd->spi_num;
  if (!spi_num) return;
  if (running_dmd_len == 0) {
	  Timer4.pause(); // останавливаем таймер перед настройкой
      Timer4.setPeriod(scan_int); // время в микросекундах (500мс)
      Timer4.attachInterrupt(TIMER_UPDATE_INTERRUPT, scan_running_dmds); // активируем прерывание
      Timer4.refresh(); // обнулить таймер 
      Timer4.resume(); // запускаем таймер  

      Timer3.pause();
      Timer3.setPeriod(30); 
      Timer3.refresh();
	  Timer3.resume();
	  }
  if (!running_dmds[spi_num -1]) running_dmd_len++;

  running_dmds[spi_num -1] = dmd;
}

static void inline __attribute__((always_inline)) scan_running_dmds()
{
  static volatile uint8_t i =0;
 
    DMD *next = (DMD*)running_dmds[i%2];
	i++;
    if(next) {
      next->scanDisplayByDMA();
	  
    }
  
}
static void SPI1_DMA_callback() {
	DMD *next = (DMD*)running_dmds[0];
	next->latchDMA();
}

static void SPI2_DMA_callback() {
	DMD *next = (DMD*)running_dmds[1];
	next->latchDMA();
}

  
#endif


/*--------------------------------------------------------------------------------------
 Setup and instantiation of DMD library
 Note this currently uses the SPI port for the fastest performance to the DMD, be
 careful of possible conflicts with other SPI port devices
--------------------------------------------------------------------------------------*/


DMD::DMD(byte _pin_A, byte _pin_B, byte _pin_nOE, byte _pin_SCLK, byte panelsWide, byte panelsHigh, SPIClass _spi )
:pin_DMD_A(_pin_A), pin_DMD_B(_pin_B), pin_DMD_nOE(_pin_nOE), pin_DMD_SCLK(_pin_SCLK), 
 DisplaysWide(panelsWide), DisplaysHigh(panelsHigh), SPI_DMD(_spi)
{
	
	uint16_t ui;
    
    DisplaysTotal=DisplaysWide*DisplaysHigh;
    row1 = DisplaysTotal<<4;
    row2 = DisplaysTotal<<5;
    row3 = ((DisplaysTotal<<2)*3)<<2;
    bDMDScreenRAM = (byte *) malloc(DisplaysTotal*DMD_RAM_SIZE_BYTES);
    
 #if defined(__STM32F1__)
    pin_DMD_CLK = SPI_DMD.sckPin();   
    pin_DMD_R_DATA = SPI_DMD.mosiPin() ; 
	pinMode(pin_DMD_nOE, PWM);  // setup the pin as PWM
	SPI_DMD.begin(); //Initialize the SPI_2 port.
	/*SPI_DMD.setBitOrder(MSBFIRST); // Set the SPI_2 bit order
	SPI_DMD.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
	SPI_DMD.setClockDivider(SPI_CLOCK_DIV16);  // Use a different speed to SPI 1 */
	//SPI_DMD.beginTransaction(SPISettings(DMD_SPI_CLOCK, MSBFIRST, SPI_MODE0));
#if defined( DMD_USE_DMA )	
	dmd_dma_buf = (byte *) malloc(DisplaysTotal*DMD_DMA_BUF_SIZE);
    rx_dma_buf =  (byte *) malloc(DisplaysTotal*DMD_DMA_BUF_SIZE);
    spiDmaDev = DMA1;
    if (SPI_DMD.dev() == SPI1) {
      	  spiTxDmaChannel = DMA_CH3;
		  spi_num =1;
      }
      else {
		  spiTxDmaChannel = DMA_CH5;
		  spi_num =2;
      }
#endif
	
#elif defined(__AVR_ATmega328P__)
    pin_DMD_CLK = 13;
    pin_DMD_R_DATA = 11;
	pinMode(pin_DMD_nOE, OUTPUT); 
	 // initialize the SPI port
    SPI.begin();		// probably don't need this since it inits the port pins only, which we do just below with the appropriate DMD interface setup
    SPI.setBitOrder(MSBFIRST);	//
    SPI.setDataMode(SPI_MODE0);	// CPOL=0, CPHA=0
    SPI.setClockDivider(DMD_SPI_CLOCK);
 #endif
    

    digitalWrite(pin_DMD_A, LOW);	// 
    digitalWrite(pin_DMD_B, LOW);	// 
    digitalWrite(pin_DMD_CLK, LOW);	// 
    digitalWrite(pin_DMD_SCLK, LOW);	// 
    digitalWrite(pin_DMD_R_DATA, HIGH);	// 
  
    pinMode(pin_DMD_A, OUTPUT);	//
    pinMode(pin_DMD_B, OUTPUT);	//
    pinMode(pin_DMD_CLK, OUTPUT);	//
    pinMode(pin_DMD_SCLK, OUTPUT);	//
    pinMode(pin_DMD_R_DATA, OUTPUT);	//
    

    clearScreen(true);
    //brightness =20000;
    bDMDByte = 0;

}


//DMD::~DMD()
//{
//   // nothing needed here
//}

void DMD::init(uint16_t scan_interval) {
#if defined(__STM32F1__)
    scan_int = scan_interval;
	SPI_DMD.begin(); //Initialize the SPI_2 port.
	SPI_DMD.setBitOrder(MSBFIRST); // Set the SPI_2 bit order
	SPI_DMD.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
	//SPI_DMD.setClockDivider(SPI_CLOCK_DIV16);  // Use a different speed to SPI 1 */
	SPI_DMD.beginTransaction(SPISettings(DMD_SPI_CLOCK, MSBFIRST, SPI_MODE0));
	register_running_dmd(this);
	brightrange = Timer3.getOverflow();
	setBrightness(brightrange/3);
	/*
	pinMode(PA1, OUTPUT);
	digitalWrite(PA1, LOW);*/
	
#endif
}
//DMD I/O pin macros
void
 DMD::LIGHT_DMD_ROW_01_05_09_13()       { digitalWrite( pin_DMD_B,  LOW ); digitalWrite( pin_DMD_A,  LOW ); }
void
 DMD::LIGHT_DMD_ROW_02_06_10_14()       { digitalWrite( pin_DMD_B,  LOW ); digitalWrite( pin_DMD_A, HIGH ); }
void
 DMD::LIGHT_DMD_ROW_03_07_11_15()       { digitalWrite( pin_DMD_B, HIGH ); digitalWrite( pin_DMD_A,  LOW ); }
void
 DMD::LIGHT_DMD_ROW_04_08_12_16()       { digitalWrite( pin_DMD_B, HIGH ); digitalWrite( pin_DMD_A, HIGH ); }
void
 DMD::LATCH_DMD_SHIFT_REG_TO_OUTPUT()   { digitalWrite( pin_DMD_SCLK, HIGH ); 
                                          //delayMicroseconds(1);
                                          digitalWrite( pin_DMD_SCLK,  LOW ); }
 #if defined(__STM32F1__)
    void DMD::OE_DMD_ROWS_OFF()                 { pinMode( pin_DMD_nOE, INPUT  ); }
	void DMD::OE_DMD_ROWS_ON()                 { pinMode( pin_DMD_nOE, OUTPUT  ); }
  #elif defined(__AVR_ATmega328P__)
    void DMD::OE_DMD_ROWS_OFF()                 { digitalWrite( pin_DMD_nOE, LOW  ); }
    void DMD::OE_DMD_ROWS_ON()                  { digitalWrite( pin_DMD_nOE, HIGH ); }
 #endif
 



/*--------------------------------------------------------------------------------------
 Set or clear a pixel at the x and y location (0,0 is the top left corner)
--------------------------------------------------------------------------------------*/
void
 DMD::writePixel(unsigned int bX, unsigned int bY, byte bGraphicsMode, byte bPixel)
{
    unsigned int uiDMDRAMPointer;

    if (bX >= (DMD_PIXELS_ACROSS*DisplaysWide) || bY >= (DMD_PIXELS_DOWN * DisplaysHigh)) {
	    return;
    }
	// inverse data bits for some panels
	bPixel = bPixel^inverse_ALL_flag;
	
    byte panel=(bX/DMD_PIXELS_ACROSS) + (DisplaysWide*(bY/DMD_PIXELS_DOWN));
    bX=(bX % DMD_PIXELS_ACROSS) + (panel<<5);
    bY=bY % DMD_PIXELS_DOWN;
    //set pointer to DMD RAM byte to be modified
    uiDMDRAMPointer = bX/8 + bY*(DisplaysTotal<<2);

    byte lookup = bPixelLookupTable[bX & 0x07];

    switch (bGraphicsMode) {
    case GRAPHICS_NORMAL:
	    if (bPixel == true)
		bDMDScreenRAM[uiDMDRAMPointer] &= ~lookup;	// zero bit is pixel on
	    else
		bDMDScreenRAM[uiDMDRAMPointer] |= lookup;	// one bit is pixel off
	    break;
    case GRAPHICS_INVERSE:
	    if (bPixel == false)
		    bDMDScreenRAM[uiDMDRAMPointer] &= ~lookup;	// zero bit is pixel on
	    else
		    bDMDScreenRAM[uiDMDRAMPointer] |= lookup;	// one bit is pixel off
	    break;
    case GRAPHICS_TOGGLE:
	    if (bPixel == true) {
		if ((bDMDScreenRAM[uiDMDRAMPointer] & lookup) == 0)
		    bDMDScreenRAM[uiDMDRAMPointer] |= lookup;	// one bit is pixel off
		else
		    bDMDScreenRAM[uiDMDRAMPointer] &= ~lookup;	// one bit is pixel off
	    }
	    break;
    case GRAPHICS_OR:
	    //only set pixels on
	    if (bPixel == true)
		    bDMDScreenRAM[uiDMDRAMPointer] &= ~lookup;	// zero bit is pixel on
	    break;
    case GRAPHICS_NOR:
	    //only clear on pixels
	    if ((bPixel == true) &&
		    ((bDMDScreenRAM[uiDMDRAMPointer] & lookup) == 0))
		    bDMDScreenRAM[uiDMDRAMPointer] |= lookup;	// one bit is pixel off
	    break;
    }

}
/*--------------------------------------------------------------------------------------*/
 void DMD::drawStringX(int bX, int bY, const char *bChars,
		     byte bGraphicsMode, byte orientation)
{
	int len =0;
	while (bChars[len] && len < MAX_STRING_LEN) {len++;}
	DMD::drawString(bX, bY, bChars, len, bGraphicsMode, orientation);
}
/*--------------------------------------------------------------------------------------*/
void DMD::drawString(int bX, int bY, const char *bChars, int length,
		     byte bGraphicsMode, byte orientation)
{
    if (bX >= (DMD_PIXELS_ACROSS*DisplaysWide) || bY >= DMD_PIXELS_DOWN * DisplaysHigh)
	return;
    uint8_t height = Font->get_height(); 
    if (bY+height<0) return;

    int strWidth = 0;
	this->drawLine(bX -1 , bY, bX -1 , bY + height, GRAPHICS_INVERSE);

    for (int i = 0; i < length; i++) {
        
		int charWide = this->drawChar(bX+strWidth, bY, bChars[i], bGraphicsMode, orientation); 
		
		//DEBUG
	    //Serial.println(bChars[i]);
		//Serial.println(bChars[i], HEX);
		//Serial.println(charWide);
		 
		//DEBUG
	    if (charWide > 0) {
	        strWidth += charWide ;
	        this->drawLine(bX + strWidth , bY, bX + strWidth , bY + height, GRAPHICS_INVERSE);
            strWidth++;
        } else if (charWide < 0) {
            return;
        }
        if ((bX + strWidth) >= DMD_PIXELS_ACROSS * DisplaysWide || bY >= DMD_PIXELS_DOWN * DisplaysHigh) return;
    }
}
/*--------------------------------------------------------------------------------------*/
void DMD::drawMarqueeX(const char *bChars, int left, int top, byte orientation) 
{   int len =0;
	while (bChars[len] && len < MAX_STRING_LEN) {len++;}
	DMD::drawMarquee(bChars, len, left, top, orientation) ;
}
/*--------------------------------------------------------------------------------------*/
void DMD::drawMarquee(const char *bChars, int length, int left, int top, byte orientation) 
{    
// temp parameter for beta version
	uint8_t matrix_h =16;
	
    marqueeWidth = 0;
    for (int i = 0; i < length; i++) {
	    marqueeText[i] = bChars[i];
		marqueeWidth += charWidth(bChars[i], orientation) + 1;
	 }
	
	
	if (orientation == 1) {
		  marqueeHeight = matrix_h;
		}
	else {
		  marqueeHeight= Font->get_height(); 
		}
    
    marqueeText[length] = '\0';
    marqueeOffsetY = top;
    marqueeOffsetX = left;
    marqueeLength = length;
    drawString(marqueeOffsetX, marqueeOffsetY, marqueeText, marqueeLength,
	   GRAPHICS_NORMAL, orientation);
}
 /*--------------------------------------------------------------------------------------
 
--------------------------------------------------------------------------------------*/
boolean DMD::stepMarquee(int amountX, int amountY, byte orientation)
{
    uint8_t msb_bit = 0x80;
    uint8_t lsb_bit = 0x01;
    
    if (inverse_ALL_flag) {
    	msb_bit = 0;
        lsb_bit = 0;
    }
    
    boolean ret=false;
    marqueeOffsetX += amountX;
    marqueeOffsetY += amountY;
    if (marqueeOffsetX < -marqueeWidth) {
	    marqueeOffsetX = DMD_PIXELS_ACROSS * DisplaysWide;
	    clearScreen(true);
        ret=true;
    } else if (marqueeOffsetX > DMD_PIXELS_ACROSS * DisplaysWide) {
	    marqueeOffsetX = -marqueeWidth;
	    clearScreen(true);
        ret=true;
    }
    
        
    if (marqueeOffsetY < -marqueeHeight) {
	    marqueeOffsetY = DMD_PIXELS_DOWN * DisplaysHigh;
	    clearScreen(true);
        ret=true;
    } else if (marqueeOffsetY > DMD_PIXELS_DOWN * DisplaysHigh) {
	    marqueeOffsetY = -marqueeHeight;
	    clearScreen(true);
        ret=true;
    }

    // Special case horizontal scrolling to improve speed
    if (amountY==0 && amountX==-1) {
        // Shift entire screen one bit
        for (int i=0; i<DMD_RAM_SIZE_BYTES*DisplaysTotal;i++) {
            if ((i%(DisplaysWide*4)) == (DisplaysWide*4) -1) {
                bDMDScreenRAM[i]=(bDMDScreenRAM[i]<<1)+lsb_bit;
            } else {
                bDMDScreenRAM[i]=(bDMDScreenRAM[i]<<1) + ((bDMDScreenRAM[i+1] & 0x80) >>7);
            }
        }

        // Redraw last char on screen
        int strWidth=marqueeOffsetX;
        for (int i=0; i < marqueeLength; i++) {
            int wide = charWidth(marqueeText[i], orientation);
            if (strWidth+wide >= DisplaysWide*DMD_PIXELS_ACROSS) {
                drawChar(strWidth, marqueeOffsetY,marqueeText[i],GRAPHICS_NORMAL, orientation);
                return ret;
            }
            strWidth += wide+1;
        }
    } else if (amountY==0 && amountX==1) {
        // Shift entire screen one bit
        for (int i=(DMD_RAM_SIZE_BYTES*DisplaysTotal)-1; i>=0;i--) {
            if ((i%(DisplaysWide*4)) == 0) {
                bDMDScreenRAM[i]=(bDMDScreenRAM[i]>>1)+msb_bit;
            } else {
                bDMDScreenRAM[i]=(bDMDScreenRAM[i]>>1) + ((bDMDScreenRAM[i-1] & 1) <<7);
            }
        }

        // Redraw last char on screen
        int strWidth=marqueeOffsetX;
        for (int i=0; i < marqueeLength; i++) {
            int wide = charWidth(marqueeText[i], orientation);
            if (strWidth+wide >= 0) {
                drawChar(strWidth, marqueeOffsetY,marqueeText[i],GRAPHICS_NORMAL, orientation);
                return ret;
            }
            strWidth += wide+1;
        }
    } else {
        drawString(marqueeOffsetX, marqueeOffsetY, marqueeText, marqueeLength,
	       GRAPHICS_NORMAL, orientation);
    }

    return ret;
}


/*--------------------------------------------------------------------------------------
 Clear the screen in DMD RAM
--------------------------------------------------------------------------------------*/
void DMD::clearScreen(byte bNormal)
{
    if (bNormal^inverse_ALL_flag) // clear all pixels
        memset(bDMDScreenRAM,0xFF,DMD_RAM_SIZE_BYTES*DisplaysTotal);
    else // set all pixels
        memset(bDMDScreenRAM,0x00,DMD_RAM_SIZE_BYTES*DisplaysTotal);
}

/*--------------------------------------------------------------------------------------
 Draw or clear a line from x1,y1 to x2,y2
--------------------------------------------------------------------------------------*/
void DMD::drawLine(int x1, int y1, int x2, int y2, byte bGraphicsMode)
{
    int dy = y2 - y1;
    int dx = x2 - x1;
    int stepx, stepy;

    if (dy < 0) {
	    dy = -dy;
	    stepy = -1;
    } else {
	    stepy = 1;
    }
    if (dx < 0) {
	    dx = -dx;
	    stepx = -1;
    } else {
	    stepx = 1;
    }
    dy <<= 1;			// dy is now 2*dy
    dx <<= 1;			// dx is now 2*dx

    writePixel(x1, y1, bGraphicsMode, true);
    if (dx > dy) {
	    int fraction = dy - (dx >> 1);	// same as 2*dy - dx
	    while (x1 != x2) {
	        if (fraction >= 0) {
		        y1 += stepy;
		        fraction -= dx;	// same as fraction -= 2*dx
	        }
	        x1 += stepx;
	        fraction += dy;	// same as fraction -= 2*dy
	        writePixel(x1, y1, bGraphicsMode, true);
	    }
    } else {
	    int fraction = dx - (dy >> 1);
	    while (y1 != y2) {
	        if (fraction >= 0) {
		        x1 += stepx;
		        fraction -= dy;
	        }
	        y1 += stepy;
	        fraction += dx;
	        writePixel(x1, y1, bGraphicsMode, true);
	    }
    }
}

/*--------------------------------------------------------------------------------------
 Draw or clear a circle of radius r at x,y centre
--------------------------------------------------------------------------------------*/
void DMD::drawCircle(int xCenter, int yCenter, int radius,
		     byte bGraphicsMode)
{
    int x = 0;
    int y = radius;
    int p = (5 - radius * 4) / 4;

    drawCircleSub(xCenter, yCenter, x, y, bGraphicsMode);
    while (x < y) {
	    x++;
	    if (p < 0) {
	        p += 2 * x + 1;
	    } else {
	        y--;
	        p += 2 * (x - y) + 1;
	    }
	    drawCircleSub(xCenter, yCenter, x, y, bGraphicsMode);
    }
}

void DMD::drawCircleSub(int cx, int cy, int x, int y, byte bGraphicsMode)
{

    if (x == 0) {
	    writePixel(cx, cy + y, bGraphicsMode, true);
	    writePixel(cx, cy - y, bGraphicsMode, true);
	    writePixel(cx + y, cy, bGraphicsMode, true);
	    writePixel(cx - y, cy, bGraphicsMode, true);
    } else if (x == y) {
	    writePixel(cx + x, cy + y, bGraphicsMode, true);
	    writePixel(cx - x, cy + y, bGraphicsMode, true);
	    writePixel(cx + x, cy - y, bGraphicsMode, true);
	    writePixel(cx - x, cy - y, bGraphicsMode, true);
    } else if (x < y) {
	    writePixel(cx + x, cy + y, bGraphicsMode, true);
	    writePixel(cx - x, cy + y, bGraphicsMode, true);
	    writePixel(cx + x, cy - y, bGraphicsMode, true);
	    writePixel(cx - x, cy - y, bGraphicsMode, true);
	    writePixel(cx + y, cy + x, bGraphicsMode, true);
	    writePixel(cx - y, cy + x, bGraphicsMode, true);
	    writePixel(cx + y, cy - x, bGraphicsMode, true);
	    writePixel(cx - y, cy - x, bGraphicsMode, true);
    }
}

/*--------------------------------------------------------------------------------------
 Draw or clear a box(rectangle) with a single pixel border
--------------------------------------------------------------------------------------*/
void DMD::drawBox(int x1, int y1, int x2, int y2, byte bGraphicsMode)
{
    drawLine(x1, y1, x2, y1, bGraphicsMode);
    drawLine(x2, y1, x2, y2, bGraphicsMode);
    drawLine(x2, y2, x1, y2, bGraphicsMode);
    drawLine(x1, y2, x1, y1, bGraphicsMode);
}

/*--------------------------------------------------------------------------------------
 Draw or clear a filled box(rectangle) with a single pixel border
--------------------------------------------------------------------------------------*/
void DMD::drawFilledBox(int x1, int y1, int x2, int y2,
			byte bGraphicsMode)
{
    for (int b = x1; b <= x2; b++) {
	    drawLine(b, y1, b, y2, bGraphicsMode);
    }
}

/*--------------------------------------------------------------------------------------
 Draw the selected test pattern
--------------------------------------------------------------------------------------*/
void DMD::drawTestPattern(byte bPattern)
{
    unsigned int ui;

    int numPixels=DisplaysTotal * DMD_PIXELS_ACROSS * DMD_PIXELS_DOWN;
    int pixelsWide=DMD_PIXELS_ACROSS*DisplaysWide;
    for (ui = 0; ui < numPixels; ui++) {
	    switch (bPattern) {
	    case PATTERN_ALT_0:	// every alternate pixel, first pixel on
		    if ((ui & pixelsWide) == 0)
		        //even row
		        writePixel((ui & (pixelsWide-1)), ((ui & ~(pixelsWide-1)) / pixelsWide), GRAPHICS_NORMAL, ui & 1);
		    else
		        //odd row
		        writePixel((ui & (pixelsWide-1)), ((ui & ~(pixelsWide-1)) / pixelsWide), GRAPHICS_NORMAL, !(ui & 1));
		    break;
	    case PATTERN_ALT_1:	// every alternate pixel, first pixel off
		    if ((ui & pixelsWide) == 0)
		        //even row
		        writePixel((ui & (pixelsWide-1)), ((ui & ~(pixelsWide-1)) / pixelsWide), GRAPHICS_NORMAL, !(ui & 1));
		    else
		        //odd row
		        writePixel((ui & (pixelsWide-1)), ((ui & ~(pixelsWide-1)) / pixelsWide), GRAPHICS_NORMAL, ui & 1);
		    break;
	    case PATTERN_STRIPE_0:	// vertical stripes, first stripe on
		    writePixel((ui & (pixelsWide-1)), ((ui & ~(pixelsWide-1)) / pixelsWide), GRAPHICS_NORMAL, ui & 1);
		    break;
	    case PATTERN_STRIPE_1:	// vertical stripes, first stripe off
		    writePixel((ui & (pixelsWide-1)), ((ui & ~(pixelsWide-1)) / pixelsWide), GRAPHICS_NORMAL, !(ui & 1));
		    break;
        }
    }
}

#if defined(__STM32F1__)

void DMD::latchDMA() {
	   //SPI_DMD.dmaTransferFinish();
	  while (spi_is_tx_empty(SPI_DMD.dev()) == 0); // "5. Wait until TXE=1 ..."
      while (spi_is_busy(SPI_DMD.dev()) != 0); // "... and then wait until BSY=0 before disabling the SPI." 
      spi_tx_dma_disable(SPI_DMD.dev());
     
      dma_disable(spiDmaDev, spiTxDmaChannel);
      dma_clear_isr_bits(spiDmaDev, spiTxDmaChannel);
      
	  pwmWrite(pin_DMD_nOE, 0);	//for stm32

		
        LATCH_DMD_SHIFT_REG_TO_OUTPUT();
        switch (bDMDByte) {
        case 0:			// row 1, 5, 9, 13 were clocked out
            LIGHT_DMD_ROW_01_05_09_13();
            bDMDByte=1;
            break;
        case 1:			// row 2, 6, 10, 14 were clocked out
            LIGHT_DMD_ROW_02_06_10_14();
            bDMDByte=2;
            break;
        case 2:			// row 3, 7, 11, 15 were clocked out
            LIGHT_DMD_ROW_03_07_11_15();
            bDMDByte=3;
            break;
        case 3:			// row 4, 8, 12, 16 were clocked out
            LIGHT_DMD_ROW_04_08_12_16();
            bDMDByte=0;
            break;
        }
       

   pwmWrite(pin_DMD_nOE, brightness);	//for stm32
   
   //digitalWrite(PA1, LOW);

}
	



void DMD::scanDisplayByDMA()
{
    //if PIN_OTHER_SPI_nCS is in use during a DMD scan request then scanDisplayBySPI() will exit without conflict! (and skip that scan)
    //if( digitalRead( PIN_OTHER_SPI_nCS ) == HIGH )
    //{
	    //digitalWrite(PA1, HIGH);
        //SPI transfer pixels to the display hardware shift registers
        int rowsize=DisplaysTotal<<2;
        int offset=rowsize * bDMDByte;
		//digitalWrite(SPI2_NSS_PIN, LOW); // manually take CSN low for SPI_1 transmission
        pwmWrite(pin_DMD_nOE, 0);

	    //uint8_t tt_buf[256];
        uint8_t* buf_ptr = dmd_dma_buf;
        
		/*memcpy(buf_ptr, bDMDScreenRAM +offset+row3, rowsize); buf_ptr += rowsize;
		memcpy(buf_ptr, bDMDScreenRAM +offset+row2, rowsize); buf_ptr += rowsize;
		memcpy(buf_ptr, bDMDScreenRAM +offset+row1, rowsize); buf_ptr += rowsize;
		memcpy(buf_ptr, bDMDScreenRAM +offset, rowsize); */
		 for (int i=0;i<rowsize;i++) {
        	//SPI_DMD.dmaSendAsync(bDMDScreenRAM, 16);
            *buf_ptr = (bDMDScreenRAM[offset+i+row3]);buf_ptr++;
            *buf_ptr = (bDMDScreenRAM[offset+i+row2]);buf_ptr++;
            *buf_ptr = (bDMDScreenRAM[offset+i+row1]);buf_ptr++;
            *buf_ptr = (bDMDScreenRAM[offset+i]);buf_ptr++;
        }
		
		//SPI_DMD.onReceive(tx_callback);
		//SPI_DMD.onTransmit(tx_callback);
		//SPI_DMD.dmaTransfer(dmd_dma_buf, tt_buf, rowsize*4);
		if (SPI_DMD.dev() == SPI1) {
			SPI_DMD.onTransmit(SPI1_DMA_callback);
	        dma_attach_interrupt(spiDmaDev, spiTxDmaChannel, SPI1_DMA_callback);
			}
        else if (SPI_DMD.dev() == SPI2) {
			SPI_DMD.onTransmit(SPI2_DMA_callback);
	        dma_attach_interrupt(spiDmaDev, spiTxDmaChannel, SPI2_DMA_callback);
			}
		//dma_attach_interrupt(DMA1, ccdma, tx_callback);
        //SPI_DMD.dmaTransferAsync(dmd_dma_buf,  rowsize*4, tx_callback);
        SPI_DMD.dmaSend(dmd_dma_buf,  rowsize*4, 1);
		//digitalWrite(PA1, LOW);
      
}


#endif	
/*--------------------------------------------------------------------------------------
 Scan the dot matrix LED panel display, from the RAM mirror out to the display hardware.
 Call 4 times to scan the whole display which is made up of 4 interleaved rows within the 16 total rows.
 Insert the calls to this function into the main loop for the highest call rate, or from a timer interrupt
--------------------------------------------------------------------------------------*/
//int i = 0;
void DMD::scanDisplayBySPI()
{
    //if PIN_OTHER_SPI_nCS is in use during a DMD scan request then scanDisplayBySPI() will exit without conflict! (and skip that scan)
    //if( digitalRead( PIN_OTHER_SPI_nCS ) == HIGH )
    //{
				
        //SPI transfer pixels to the display hardware shift registers
        int rowsize=DisplaysTotal<<2;
        int offset=rowsize * bDMDByte;
		//digitalWrite(SPI2_NSS_PIN, LOW); // manually take CSN low for SPI_1 transmission
        
#if defined(__STM32F1__)
	    pwmWrite(pin_DMD_nOE, 0);
        //SPI_DMD.setDataSize(DATA_SIZE_8BIT);
       // SPI_DMD.beginTransaction(SPISettings(DMD_SPI_CLOCK, MSBFIRST, SPI_MODE0));
        
#if defined(DMD_USE_DMA)
	    uint8_t* buf_ptr = dmd_dma_buf;
        for (int i=0;i<rowsize;i++) {
        	
            *buf_ptr = (bDMDScreenRAM[offset+i+row3]);buf_ptr++;
            *buf_ptr = (bDMDScreenRAM[offset+i+row2]);buf_ptr++;
            *buf_ptr = (bDMDScreenRAM[offset+i+row1]);buf_ptr++;
            *buf_ptr = (bDMDScreenRAM[offset+i]);buf_ptr++;
        }
	
	    SPI_DMD.dmaTransfer(dmd_dma_buf, rx_dma_buf, rowsize*4);
#else   //  not DMA

        for (int i=0;i<rowsize;i++) {
            SPI_DMD.write(bDMDScreenRAM[offset+i+row3]);
            SPI_DMD.write(bDMDScreenRAM[offset+i+row2]);
            SPI_DMD.write(bDMDScreenRAM[offset+i+row1]);
            SPI_DMD.write(bDMDScreenRAM[offset+i]);
        }
#endif  //   DMA
	
        //SPI_DMD.endTransaction(); 
       //pwmWrite(pin_DMD_nOE, 0);	//for stm32
#elif defined(__AVR_ATmega328P__)
       for (int i=0;i<rowsize;i++) {
            SPI.transfer(bDMDScreenRAM[offset+i+row3]);
            SPI.transfer(bDMDScreenRAM[offset+i+row2]);
            SPI.transfer(bDMDScreenRAM[offset+i+row1]);
            SPI.transfer(bDMDScreenRAM[offset+i]);
        }
		OE_DMD_ROWS_OFF();
#endif
       //digitalWrite(SPI2_NSS_PIN, HIGH); // manually take CSN high between spi transmissions
        //
		
        LATCH_DMD_SHIFT_REG_TO_OUTPUT();
        switch (bDMDByte) {
        case 0:			// row 1, 5, 9, 13 were clocked out
            LIGHT_DMD_ROW_01_05_09_13();
            bDMDByte=1;
            break;
        case 1:			// row 2, 6, 10, 14 were clocked out
            LIGHT_DMD_ROW_02_06_10_14();
            bDMDByte=2;
            break;
        case 2:			// row 3, 7, 11, 15 were clocked out
            LIGHT_DMD_ROW_03_07_11_15();
            bDMDByte=3;
            break;
        case 3:			// row 4, 8, 12, 16 were clocked out
            LIGHT_DMD_ROW_04_08_12_16();
            bDMDByte=0;
            break;
        }
        //OE_DMD_ROWS_ON();
		
		// Output enable pin is either fixed on, or PWMed for a variable brightness display
		 //if(brightness == 255)
			// {OE_DMD_ROWS_ON();}
		// else
			//analogWrite(PIN_DMD_nOE, brightness);	//for atmega
#if defined(__STM32F1__)
   pwmWrite(pin_DMD_nOE, brightness);	//for stm32
#elif defined(__AVR_ATmega328P__)
   OE_DMD_ROWS_ON();
#endif	

		
    //}
}
/*--------------------------------------------------------------------------------------
       Select current font
--------------------------------------------------------------------------------------*/
void DMD::selectFont(DMD_Font * font)
{
    this->Font = font;
	
}
/*--------------------------------------------------------------------------------------
  draw char with selected font at coordinates bX bY
--------------------------------------------------------------------------------------*/
int DMD::drawChar(const int bX, const int bY, const unsigned char letter, byte bGraphicsMode, byte orientation)
{
	
	if (orientation) {
		return drawCharV(bX, bY, letter, bGraphicsMode);
	}
	if (bX > (DMD_PIXELS_ACROSS*DisplaysWide) || bY > (DMD_PIXELS_DOWN*DisplaysHigh)) return -1;
	
	
	unsigned char c = letter;
	if (! Font->is_char_in(c)) return 0;

	uint8_t height = Font->get_height();

	if (c == ' ') { //CHANGED FROM ' '
		int charWide = Font->get_char_width(' ');
		this->drawFilledBox(bX, bY, bX + charWide , bY + height, GRAPHICS_INVERSE);
        return charWide;
	}
    

	
	if (Font->is_gfx_font()) {

		

		
		DMD_GFX_Font* ff = (DMD_GFX_Font *)Font;
		GFXfont * gfxFont_p = ff->get_font_by_char(c);
		c -= ff->get_first_by_char(c);
		//Serial.print("Char index ");Serial.println(c, HEX);
		
		GFXglyph *glyph = &(((GFXglyph *)pgm_read_pointer(&gfxFont_p->glyph))[c]);
		uint8_t  *bitmap = (uint8_t *)pgm_read_pointer(&gfxFont_p->bitmap);

		uint16_t bo = pgm_read_word(&glyph->bitmapOffset);
		//Serial.print("Bitmap offset ");Serial.println(bo);
		uint8_t  w = pgm_read_byte(&glyph->width),
			h = pgm_read_byte(&glyph->height);
		int8_t   xo = pgm_read_byte(&glyph->xOffset),
			yo = height + pgm_read_byte(&glyph->yOffset);
		uint8_t  ww = pgm_read_byte(&glyph->xAdvance);
		uint8_t  xx, yy, bits = 0, bit = 0;
		int16_t  xo16 = 0, yo16 = 0;

		this->drawFilledBox(bX, bY, bX + ww, bY + height, GRAPHICS_INVERSE);


		for (yy = 0; yy<h; yy++) {
			for (xx = 0; xx<w; xx++) {
				if (!(bit++ & 7)) {
					bits = pgm_read_byte(&bitmap[bo++]);
				}
				if (bits & 0x80) {
					writePixel(bX + xo + xx, bY + yo + yy, bGraphicsMode, true);
					//writePixel(x+xo+xx, y+yo+yy, color);
				}
				else {
					writePixel(bX + xo + xx, bY + yo + yy, bGraphicsMode, false);
					//writeFillRect(x+(xo16+xx)*size, y+(yo16+yy)*size,size, size, color);
				}
				bits <<= 1;
			}
		}
		return ww;
	}
	else {
		
		
		DMD_Standard_Font* ff = (DMD_Standard_Font *) Font;
		uint8_t width = ff->get_char_width(c);
		uint8_t bytes = (height + 7) / 8;
		uint16_t index = ff->get_bitmap_index(c);
		c -= ff->get_first();
		
		if (bX < -width || bY < -height) return width;

		

		// last but not least, draw the character
		for (uint8_t j = 0; j < width; j++) { // Width
			for (uint8_t i = bytes - 1; i < 254; i--) { // Vertical Bytes
				uint8_t data = pgm_read_byte(ff->font_ptr + index + j + (i * width));
				int offset = (i * 8);
				if ((i == bytes - 1) && bytes > 1) {
					offset = height - 8;
				}
				for (uint8_t k = 0; k < 8; k++) { // Vertical bits
					if ((offset + k >= i * 8) && (offset + k <= height)) {
						if (data & (1 << k)) {
							writePixel(bX + j, bY + offset + k, bGraphicsMode, true);
						}
						else {
							writePixel(bX + j, bY + offset + k, bGraphicsMode, false);
						}
					}
				}
			}
		}
		return width;
	}
}
 
/*--------------------------------------------------------------------------------------
  draw char vertically with selected font at coordinates bX bY
--------------------------------------------------------------------------------------*/
int DMD::drawCharV(const int bX, const int bY, const unsigned char letter, byte bGraphicsMode)
{
	// temp parameter for beta version
	uint8_t matrix_h =16;
	
	
	if (bX > (DMD_PIXELS_ACROSS*DisplaysWide) || bY > (DMD_PIXELS_DOWN*DisplaysHigh)) return -1;
	
	
	unsigned char c = letter;
	if (! Font->is_char_in(c)) return 0;

	uint8_t height = Font->get_height();

	if (c == ' ') { //CHANGED FROM ' '
		int charWide = Font->get_char_width(' ');
		this->drawFilledBox(bX, bY, bX + height , bY + matrix_h, GRAPHICS_INVERSE);
        return height;
	}
    

	
	if (Font->is_gfx_font()) {

		

		
		DMD_GFX_Font* ff = (DMD_GFX_Font *)Font;
		GFXfont * gfxFont_p = ff->get_font_by_char(c);
		c -= ff->get_first_by_char(c);
		//Serial.print("Char index ");Serial.println(c, HEX);
		
		GFXglyph *glyph = &(((GFXglyph *)pgm_read_pointer(&gfxFont_p->glyph))[c]);
		uint8_t  *bitmap = (uint8_t *)pgm_read_pointer(&gfxFont_p->bitmap);

		uint16_t bo = pgm_read_word(&glyph->bitmapOffset);
		//Serial.print("Bitmap offset ");Serial.println(bo);
		uint8_t  w = pgm_read_byte(&glyph->width),
			h = pgm_read_byte(&glyph->height);
		int8_t   yo = w + (matrix_h -w)/2,
			xo = height + pgm_read_byte(&glyph->yOffset);
		uint8_t  hh = xo + h;
		uint8_t  xx, yy, bits = 0, bit = 0;
		int16_t  xo16 = 0, yo16 = 0;

		this->drawFilledBox(bX, bY, bX + hh, bY + matrix_h, GRAPHICS_INVERSE);


		for (xx = 0; xx<h; xx++) {
			for (yy = 0; yy<w; yy++) {
				if (!(bit++ & 7)) {
					bits = pgm_read_byte(&bitmap[bo++]);
				}
				if (bits & 0x80) {
					writePixel(bX + xo + xx, bY + yo - yy, bGraphicsMode, true);
					//writePixel(x+xo+xx, y+yo+yy, color);
				}
				else {
					writePixel(bX + xo + xx, bY + yo - yy, bGraphicsMode, false);
					//writeFillRect(x+(xo16+xx)*size, y+(yo16+yy)*size,size, size, color);
				}
				bits <<= 1;
			}
		}
		return hh;
	}
	else {
	/*	
		
		DMD_Standard_Font* ff = (DMD_Standard_Font *) Font;
		uint8_t width = ff->get_char_width(c);
		uint8_t bytes = (height + 7) / 8;
		uint16_t index = ff->get_bitmap_index(c);
		c -= ff->get_first();
		
		if (bX < -width || bY < -height) return width;

		

		// last but not least, draw the character
		for (uint8_t j = 0; j < width; j++) { // Width
			for (uint8_t i = bytes - 1; i < 254; i--) { // Vertical Bytes
				uint8_t data = pgm_read_byte(ff->font_ptr + index + j + (i * width));
				int offset = (i * 8);
				if ((i == bytes - 1) && bytes > 1) {
					offset = height - 8;
				}
				for (uint8_t k = 0; k < 8; k++) { // Vertical bits
					if ((offset + k >= i * 8) && (offset + k <= height)) {
						if (data & (1 << k)) {
							writePixel(bX + j, bY + offset + k, bGraphicsMode, true);
						}
						else {
							writePixel(bX + j, bY + offset + k, bGraphicsMode, false);
						}
					}
				}
			}
		}
		return width; */
	} 
} 
 
/*--------------------------------------------------------------------------------------
  char width in pixels with selected font
     routine moved to DMD_Font classes
--------------------------------------------------------------------------------------*/

int DMD::charWidth(const unsigned char letter, byte orientation)
{
  return (uint8_t)Font->get_char_width(letter, orientation);
}

/// Next part is customly added by mozokevgen
///

/*--------------------------------------------------------------------------------------
 Draw the image
--------------------------------------------------------------------------------------*/
void
	DMD::drawImg(const int bX, const int bY, const uint8_t *img, byte length)
{
	if (bX > DMD_PIXELS_ACROSS*DisplaysWide)
	{
		return;
	}
	// if(flagFirst)
	// {
		// marqueeOffsetY = bY;
		// marqueeOffsetX = bX;
		// marqueeWidth = length;
		// marqueeHeight = 16;
		
		// // for (int i = 0; i < length*2; i++)
		// // {
			// // marqueeImg[i] = img[i];
		// // }
		
		// marqueeLength = length;
	// }

    uint8_t bytes = (DMD_PIXELS_DOWN + 7) / 8;
	
    // draw Image (copy from dmd.drawChar)
    for (uint8_t j = 0; j < length; j++) { // Width DMD_PIXELS_ACROSS
	    for (uint8_t i = bytes - 1; i < 254; i--) { // Vertical Bytes
	        uint8_t data = img[j + (i * length)];
		    int offset = (i * 8);
		    if ((i == bytes - 1) && bytes > 1) {
		        offset = DMD_PIXELS_DOWN - 8;
            }
	        for (uint8_t k = 0; k < 8; k++) { // Vertical bits
		        if ((offset+k >= i*8) && (offset+k <= DMD_PIXELS_DOWN)) {
					if(bX + j < DMD_PIXELS_ACROSS*DisplaysWide){
		            if (data & (1 << k)) {
			            writePixel(bX + j, bY + offset + k, GRAPHICS_NORMAL, true);
		            } else {
			            writePixel(bX + j, bY + offset + k, GRAPHICS_NORMAL, false);
		            }}
		        }
	        }
	    }
    }
}
/*--------------------------------------------------------------------------------------
 Scroll the image
--------------------------------------------------------------------------------------*/
boolean DMD::stepImg(int amountX, int amountY)
{
    boolean ret=false;
    // marqueeOffsetX += amountX;
    // marqueeOffsetY += amountY;
    // if (marqueeOffsetX < -marqueeWidth) {
	    // marqueeOffsetX = DMD_PIXELS_ACROSS * DisplaysWide;
	    // clearScreen(true);
        // ret=true;
    // } else if (marqueeOffsetX > DMD_PIXELS_ACROSS * DisplaysWide) {
	    // marqueeOffsetX = -marqueeWidth;
	    // clearScreen(true);
        // ret=true;
    // }
    
        
    // if (marqueeOffsetY < -marqueeHeight) {
	    // marqueeOffsetY = DMD_PIXELS_DOWN * DisplaysHigh;
	    // clearScreen(true);
        // ret=true;
    // } else if (marqueeOffsetY > DMD_PIXELS_DOWN * DisplaysHigh) {
	    // marqueeOffsetY = -marqueeHeight;
	    // clearScreen(true);
        // ret=true;
    // }

    // Special case horizontal scrolling to improve speed
    if (amountY==0 && amountX==-1) {
        // Shift entire screen one bit
		//byte buf[] = {bDMDScreenRAM[0]};
        for (int i=0; i<DMD_RAM_SIZE_BYTES*DisplaysTotal;i++) {
            if ((i%(DisplaysWide*4)) == (DisplaysWide*4) -1) {
                bDMDScreenRAM[i]=(bDMDScreenRAM[i]<<1)+1;
            } else {
                bDMDScreenRAM[i]=(bDMDScreenRAM[i]<<1) + ((bDMDScreenRAM[i+1] & 0x80) >>7);
            }
        }

        // Redraw last char on screen
        // int imgWidth=marqueeOffsetX;
        // for (byte i=0; i < marqueeLength; i++) {
            // int wide = 1;
            // if (imgWidth+wide >= DisplaysWide*DMD_PIXELS_ACROSS) {
				// uint8_t buf[] = {marqueeImg[i], marqueeImg[i+32]};
                // drawImg(imgWidth, marqueeOffsetY,buf, false);
                // return ret;
            // }
            // imgWidth += wide+1;
        // }
    } else if (amountY==0 && amountX==1) {
        // Shift entire screen one bit
        for (int i=(DMD_RAM_SIZE_BYTES*DisplaysTotal)-1; i>=0;i--) {
            if ((i%(DisplaysWide*4)) == 0) {
                bDMDScreenRAM[i]=(bDMDScreenRAM[i]>>1)+128;
            } else {
                bDMDScreenRAM[i]=(bDMDScreenRAM[i]>>1) + ((bDMDScreenRAM[i-1] & 1) <<7);
            }
        }

        // Redraw last line on screen
		// if (marqueeOffsetX + marqueeLength > DisplaysWide*DMD_PIXELS_ACROSS)
		// {
			// int overflow = DisplaysWide*DMD_PIXELS_ACROSS - marqueeOffsetX + marqueeLength;
			
		// }
        // int imgWidth=marqueeOffsetX;
        // for (byte i=0; i < marqueeLength; i++) {
            // int wide = 1;
            // if (imgWidth+wide >= 0) {
				// uint8_t buf[] = {marqueeImg[i], marqueeImg[i+32]};
                // drawImg(imgWidth, marqueeOffsetY, buf, false);
                // return ret;
            // }
            // imgWidth += wide+1;
        // }
    } else {
        // drawImg(marqueeOffsetX, marqueeOffsetY, marqueeImg,
	        // false);
    }

    return ret;
}

/*--------------------------------------------------------------------------------------
 Animation
--------------------------------------------------------------------------------------*/
void
	DMD::animation(const int bX, const int bY, const uint8_t *img1, byte length1, const uint8_t *img2, byte length2, bool beginFlag)
{
	static uint8_t blank[] = {0x00, 0x00};
	if(beginFlag)
	{
		marqueeOffsetY = bY;
		marqueeOffsetX = bX;
	}
	
	if (spriteFlag)
	{
		drawImg(marqueeOffsetX-1, marqueeOffsetY, blank, 1);
		drawImg(marqueeOffsetX, marqueeOffsetY, img1, length1);
		
		marqueeOffsetX += 1;
		spriteFlag = !spriteFlag;
	}
	else 
	{
		drawImg(marqueeOffsetX-1, marqueeOffsetY, blank, 1);
		drawImg(marqueeOffsetX, marqueeOffsetY, img2, length2);
		marqueeOffsetX += 1;
		spriteFlag = !spriteFlag;
	}
	
}
/*--------------------------------------------------------------------------------------
   string width in pixels
--------------------------------------------------------------------------------------*/

uint16_t DMD::stringWidth(const char *bChars, uint8_t length)
{
	// this->Font
	uint16_t width = 0;
	// char c;
	int idx;
	
	for(idx = 0; idx < length; idx++) {
    int cwidth = charWidth(bChars[idx]);
    if(cwidth > 0)
      width += cwidth + 1;
	}
	if(width) {
		width--;
	}
	return width;
}