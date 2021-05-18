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

#include "Arduino.h"
#include "DMD_STM32a.h"
/*--------------------------------------------------------------------------------------
 Setup and instantiation of DMD library
 Note this currently uses the SPI port for the fastest performance to the DMD, be
 careful of possible conflicts with other SPI port devices
--------------------------------------------------------------------------------------*/


DMD::DMD(byte _pin_A, byte _pin_B, byte _pin_nOE, byte _pin_SCLK, byte panelsWide, byte panelsHigh,
 bool d_buf, byte dmd_pixel_x, byte dmd_pixel_y)
:Adafruit_GFX(panelsWide * dmd_pixel_x, panelsHigh * dmd_pixel_y), pin_DMD_A(_pin_A), pin_DMD_B(_pin_B), pin_DMD_nOE(_pin_nOE), pin_DMD_SCLK(_pin_SCLK),
 DisplaysWide(panelsWide), DisplaysHigh(panelsHigh), dbuf(d_buf), DMD_PIXELS_ACROSS(dmd_pixel_x), DMD_PIXELS_DOWN(dmd_pixel_y)
{
	
	DisplaysTotal=DisplaysWide*DisplaysHigh;
    
	digitalWrite(pin_DMD_A, LOW);	
    digitalWrite(pin_DMD_B, LOW);	
    digitalWrite(pin_DMD_SCLK, LOW);	
    pinMode(pin_DMD_A, OUTPUT);	
    pinMode(pin_DMD_B, OUTPUT);	
    pinMode(pin_DMD_SCLK, OUTPUT);	

#if defined(__STM32F1__)
	pinMode(pin_DMD_nOE, PWM);  // setup the pin as PWM
#elif defined(__AVR_ATmega328P__)
	pinMode(pin_DMD_nOE, OUTPUT);
	digitalWrite(pin_DMD_nOE, LOW);
#endif
    
    bDMDByte = 0;
}


DMD::~DMD()
{
#if defined(DEBUG2)
	free((uint16_t*)dd_ptr);
#endif
}

/*--------------------------------------------------------------------------------------*/
void DMD::init(uint16_t scan_interval) {
	// Look up port registers and pin masks ahead of time,
    // avoids many slow digitalWrite() calls later.
	
	latport = portOutputRegister(digitalPinToPort(pin_DMD_SCLK));
	latmask = digitalPinToBitMask(pin_DMD_SCLK);
	addraport = portOutputRegister(digitalPinToPort(pin_DMD_A));
	addramask = digitalPinToBitMask(pin_DMD_A);
	addrbport = portOutputRegister(digitalPinToPort(pin_DMD_B));
	addrbmask = digitalPinToBitMask(pin_DMD_B);
	
#if defined(__STM32F1__)
    
	Timer3.pause();
	Timer3.setPeriod(30);
	Timer3.refresh();
	Timer3.resume();
	brightrange = Timer3.getOverflow();
	setBrightness(brightrange/3);
	
	textcolor = 1;
	textbgcolor = 0;
	
#endif
#if defined(DEBUG2)
	dd_ptr = (uint16_t*)malloc(200);
#endif	
}

/*--------------------------------------------------------------------------------------*/

void DMD::switch_row() {
	// switch all LED OFF
#if defined(__STM32F1__)
	pwmWrite(pin_DMD_nOE, 0);	//for stm32
#elif defined(__AVR_ATmega328P__)
	OE_DMD_ROWS_OFF();
#endif

	* latport |= latmask; // Latch data loaded during *prior* interrupt
	
	if (bDMDByte & 0x2) { *addrbport |= addrbmask; }
	else { *addrbport &= ~addrbmask; }
	if (bDMDByte & 0x1) { *addraport |= addramask; }
	else { *addraport &= ~addramask; }
	

	if (bDMDByte == 2) {
		if (swapflag == true) {    // Swap front/back buffers if requested
			backindex = 1 - backindex;
			swapflag = false;
			//bDMDByte = 0;
			bDMDScreenRAM = matrixbuff[backindex]; // Back buffer
			front_buff = matrixbuff[1 - backindex]; // -> front buffer
		}
	}
	if (++bDMDByte > 3) bDMDByte = 0;


	
	
	* latport &= ~latmask;
	// reenable LEDs
#if defined(__STM32F1__)
	pwmWrite(pin_DMD_nOE, brightness);	//for stm32
#elif defined(__AVR_ATmega328P__)
	OE_DMD_ROWS_ON();
#endif	
}

/*--------------------------------------------------------------------------------------*/

 #if defined(__STM32F1__)
    void DMD::OE_DMD_ROWS_OFF()                 { pinMode( pin_DMD_nOE, INPUT  ); }
	void DMD::OE_DMD_ROWS_ON()                 { pinMode( pin_DMD_nOE, OUTPUT  ); }
  #elif defined(__AVR_ATmega328P__)
    void DMD::OE_DMD_ROWS_OFF()                 { digitalWrite( pin_DMD_nOE, LOW  ); }
    void DMD::OE_DMD_ROWS_ON()                  { digitalWrite( pin_DMD_nOE, HIGH ); }
 #endif
 

/*--------------------------------------------------------------------------------------
 Set or clear a pixel at the x and y location (0,0 is the top left corner)
 // Moved to child classes
--------------------------------------------------------------------------------------*/
//void DMD::writePixel(int16_t x, int16_t y, uint16_t color) 


/*--------------------------------------------------------------------------------------*/
 void DMD::drawStringX(int bX, int bY, const char *bChars,
	 uint16_t color, byte orientation)
{
	int len =0;
	while (bChars[len] && len < MAX_STRING_LEN) {len++;}
	DMD::drawString(bX, bY, bChars, len, color, orientation);
}
/*--------------------------------------------------------------------------------------*/
void DMD::drawString(int bX, int bY, const char *bChars, int length,
		     uint16_t color, byte orientation)
{
    if ((bX >= (WIDTH) || bY >= (HEIGHT)))
	return;
    uint8_t height = Font->get_height(); 
    if (bY+height<0) return;

    int strWidth = 0;
	this->drawLine(bX -1 , bY, bX -1 , bY + height, inverse_color(color));

    for (int i = 0; i < length; i++) {
        
		int charWide = DMD::drawChar(bX+strWidth, bY, bChars[i], color, orientation);
		
		
	    if (charWide > 0) {
	        strWidth += charWide ;
	        this->drawLine(bX + strWidth , bY, bX + strWidth , bY + height, inverse_color(color));
            strWidth++;
        } else if (charWide < 0) {
            return;
        }
        if ((bX + strWidth) >= WIDTH || bY >= HEIGHT) return;
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
	uint8_t matrix_h = 16;
	
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
	
    //drawString(marqueeOffsetX, marqueeOffsetY, marqueeText, marqueeLength, GRAPHICS_NORMAL, orientation);
	DMD::drawString(marqueeOffsetX, marqueeOffsetY, marqueeText, marqueeLength, textcolor, orientation);
}
 /*--------------------------------------------------------------------------------------*/


uint8_t DMD::stepMarquee(int amountX, int amountY, byte orientation)
{
	uint8_t ret = 0;
	int16_t old_x = marqueeOffsetX;
	int16_t old_y = marqueeOffsetY;
    marqueeOffsetX += amountX;
    marqueeOffsetY += amountY;

	// check if marquee reached to the limits of matrix panel
	// X axis
    if (marqueeOffsetX < -marqueeWidth) {
	    marqueeOffsetX = WIDTH;
	    ret |= 1;
    } else if (marqueeOffsetX > WIDTH) {
	    marqueeOffsetX = -marqueeWidth;
		ret |= 1;
    }
    // Y axis
    if (marqueeOffsetY < -marqueeHeight) {
	    marqueeOffsetY = HEIGHT;
	    ret |= 1;
    } else if (marqueeOffsetY > HEIGHT) {
	    marqueeOffsetY = -marqueeHeight;
	    ret |= 1;
    }
	if (ret) {
		//clearScreen(true);
		fillScreen(textbgcolor);
	}
// if text left justify at screen
	if (marqueeOffsetX == 0) {
		ret |= 2;
	}
	// if text right justify at screen
	if ((marqueeOffsetX + marqueeWidth) == DMD_PIXELS_ACROSS * DisplaysWide) {
		ret |= 4;
	}
    // Special case horizontal scrolling to improve speed
    if (amountY==0 && 
		  ((amountX==-1) || (amountX == 1))) {
        // Shift entire screen one pixel
		shiftScreen(amountX);
		
		uint16_t limit_X = 0;                 // if (amountX == 1)
		if (amountX == -1) {  // if (amountX == -1)
			limit_X = WIDTH;
			if (marqueeOffsetX < (WIDTH - marqueeWidth)) return ret;
		}
		else {
			if (marqueeOffsetX > 0) return ret;
		}
		// Redraw last char on screen
        int strWidth=marqueeOffsetX;
        for (int i=0; i < marqueeLength; i++) {
            int wide = charWidth(marqueeText[i], orientation);
            if (strWidth+wide >= limit_X) {
                DMD::drawChar(strWidth, marqueeOffsetY,marqueeText[i], textcolor, orientation);
                return ret;
            }
            strWidth += wide+1;
        }
   
    } else {
	set_graph_mode(GRAPHICS_NOR);
		DMD::drawString(old_x, old_y, marqueeText, marqueeLength,
			textcolor, orientation);
		set_graph_mode(GRAPHICS_NORMAL);
		DMD::drawString(marqueeOffsetX, marqueeOffsetY, marqueeText, marqueeLength,
			textcolor, orientation);
    }

    return ret;
}


/*--------------------------------------------------------------------------------------
 Clear the screen in DMD RAM
--------------------------------------------------------------------------------------*/
void DMD::fillScreen(uint16_t color)
{
	DMD::clearScreen(inverse_color(color));
}

void DMD::clearScreen(byte bNormal)
{
    if (bNormal^inverse_ALL_flag) // clear all pixels
        memset(bDMDScreenRAM,0xFF, mem_Buffer_Size);
    else // set all pixels
        memset(bDMDScreenRAM,0x00, mem_Buffer_Size);
}





/*--------------------------------------------------------------------------------------
 Draw or clear a filled box(rectangle) with a single pixel border
--------------------------------------------------------------------------------------*/
void DMD::drawFilledBox(int x1, int y1, int x2, int y2,
			uint16_t color)
{
	if ((x2 < x1) || (y2 < y1)) return;

    for (int b = x1; b <= x2; b++) {
	    drawLine(b, y1, b, y2, color);
    }
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
int DMD::drawChar(const int bX, const int bY, const unsigned char letter, uint16_t color, byte orientation)
{
	
	if (orientation) {
		return drawCharV(bX, bY, letter, color);
	}
	if (bX > (WIDTH) || bY > (HEIGHT)) return -1;
	
	
	unsigned char c = letter;
	if (! Font->is_char_in(c)) return 0;

	uint8_t height = Font->get_height();

	if (c == ' ') { //CHANGED FROM ' '
		int charWide = Font->get_char_width(' ');
		this->drawFilledBox(bX, bY, bX + charWide , bY + height, inverse_color(color));
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

		this->drawFilledBox(bX, bY, bX + ww, bY + height, inverse_color(color));


		for (yy = 0; yy<h; yy++) {
			for (xx = 0; xx<w; xx++) {
				if (!(bit++ & 7)) {
					bits = pgm_read_byte(&bitmap[bo++]);
				}
				if (bits & 0x80) {
					writePixel(bX + xo + xx, bY + yo + yy, color);
					//writePixel(x+xo+xx, y+yo+yy, color);
				}
				else {
					writePixel(bX + xo + xx, bY + yo + yy, inverse_color(color));
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
							writePixel(bX + j, bY + offset + k, color);
						}
						else {
							writePixel(bX + j, bY + offset + k, inverse_color(color));
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
int DMD::drawCharV(const int bX, const int bY, const unsigned char letter, uint16_t color)
{
	// temp parameter for beta version
	uint8_t matrix_h =16;
	
	
	if (bX > (WIDTH) || bY > (HEIGHT)) return -1;
	
	
	unsigned char c = letter;
	if (! Font->is_char_in(c)) return 0;

	uint8_t height = Font->get_height();

	if (c == ' ') { //CHANGED FROM ' '
		int charWide = Font->get_char_width(' ');
		this->drawFilledBox(bX, bY, bX + height , bY + matrix_h, inverse_color(color));
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

		this->drawFilledBox(bX, bY, bX + hh, bY + matrix_h, inverse_color(color));


		for (xx = 0; xx<h; xx++) {
			for (yy = 0; yy<w; yy++) {
				if (!(bit++ & 7)) {
					bits = pgm_read_byte(&bitmap[bo++]);
				}
				if (bits & 0x80) {
					writePixel(bX + xo + xx, bY + yo - yy, color);
					//writePixel(x+xo+xx, y+yo+yy, color);
				}
				else {
					writePixel(bX + xo + xx, bY + yo - yy, inverse_color(color));
					//writeFillRect(x+(xo16+xx)*size, y+(yo16+yy)*size,size, size, color);
				}
				bits <<= 1;
			}
		}
		return hh;
	}
	else {
	/*	
		// *****  Standard font vertical chars not implemented  *****
	
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

/*--------------------------------------------------------------------------------------
   string width in pixels
--------------------------------------------------------------------------------------*/

uint16_t DMD::stringWidth(const char* bChars, uint8_t length, byte orientation)
{
	// this->Font
	uint16_t width = 0;
	if (length == 0) {
		
		while (bChars[length] && length < MAX_STRING_LEN) { length++; }
	}
	// char c;
	int idx;
	
	for(idx = 0; idx < length; idx++) {
    int cwidth = charWidth(bChars[idx], orientation);
    if(cwidth > 0)
      width += cwidth + 1;
	}
	if(width) {
		width--;
	}
	return width;
}
#if defined(DEBUG2)

void DMD::dumpDDbuf(void) {

	uint16_t i, buffsize = 100;

	Serial.begin(115200);
	Serial.print("Prescaler: ");
	Serial.println(Timer4.getPrescaleFactor());

	for (i = 0; i < buffsize; i++) {


		Serial.print(dd_ptr[i]);
		if (i < (buffsize - 1)) {
			if ((i & 7) == 7) Serial.print(F(",\n  "));
			else             Serial.write(',');
		}
	}
	Serial.println(F("\n};"));
}

#endif	
void DMD::swapBuffers(boolean copy) {
	if (matrixbuff[0] != matrixbuff[1]) {
		// To avoid 'tearing' display, actual swap takes place in the interrupt
		// handler, at the end of a complete screen refresh cycle.
		swapflag = true;                  // Set flag here, then...
		while (swapflag == true) delay(1); // wait for interrupt to clear it
		bDMDScreenRAM = matrixbuff[backindex]; // Back buffer
		front_buff = matrixbuff[1 - backindex]; // -> front buffer
		if (copy == true)
			memcpy(matrixbuff[backindex], matrixbuff[1 - backindex], mem_Buffer_Size);
	}
}