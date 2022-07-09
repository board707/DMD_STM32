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

DMD::DMD(byte mux_cnt, uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, byte panelsWide, byte panelsHigh,
	uint8_t n_Rows, bool d_buf, byte dmd_pixel_x, byte dmd_pixel_y)
	:Adafruit_GFX(panelsWide* dmd_pixel_x, panelsHigh* dmd_pixel_y), mux_cnt(mux_cnt), nRows(n_Rows), pin_DMD_nOE(_pin_nOE), pin_DMD_SCLK(_pin_SCLK),
	DisplaysWide(panelsWide), DisplaysHigh(panelsHigh), dbuf(d_buf), DMD_PIXELS_ACROSS(dmd_pixel_x), DMD_PIXELS_DOWN(dmd_pixel_y)
{

	DisplaysTotal = DisplaysWide * DisplaysHigh;

	// Look up port registers and pin masks ahead of time,
	// avoids many slow digitalWrite() calls later.

	latsetreg = portSetRegister(pin_DMD_SCLK);
	latmask = digitalPinToBitMask(pin_DMD_SCLK);

	oemask = digitalPinToBitMask(pin_DMD_nOE);
	oesetreg = portSetRegister(pin_DMD_nOE);

	if (mux_list != NULL) {
		mux_pins = (uint8_t*)malloc(mux_cnt);
		memcpy(mux_pins, mux_list, mux_cnt);
	}
	muxsetreg = portSetRegister(mux_pins[0]);
	mux_mask2 = (uint32_t*)malloc((nRows + 1) * 4);
}
/*--------------------------------------------------------------------------------------*/
DMD::~DMD()
{
	free(mux_mask2);
#if defined(DEBUG2)
	free((uint16_t*)dd_ptr);
#endif
}
/*--------------------------------------------------------------------------------------*/
void DMD::set_pin_modes() {

	for (uint8_t i = 0; i < mux_cnt; i++) {
		digitalWrite(mux_pins[i], LOW);
		pinMode(mux_pins[i], OUTPUT);
	}

	digitalWrite(pin_DMD_SCLK, LOW);
	pinMode(pin_DMD_SCLK, OUTPUT);
#if defined(__STM32F1__) 
	oe_channel = PIN_MAP[pin_DMD_nOE].timer_channel;
#elif defined(__STM32F4__) 
	oe_channel = timer_map[pin_DMD_nOE].channel;
#endif
#if (defined(__STM32F1__) || defined(__STM32F4__))
	pinMode(pin_DMD_nOE, PWM);  // setup the pin as PWM
#elif defined(__AVR_ATmega328P__)
	pinMode(pin_DMD_nOE, OUTPUT);
	digitalWrite(pin_DMD_nOE, LOW);
#endif

}
/*--------------------------------------------------------------------------------------*/
void DMD::init(uint16_t scan_interval) {

	this->set_pin_modes();
	this->generate_muxmask();
#if (defined(__STM32F1__) || defined(__STM32F4__))
	timer_init(OE_TIMER);
	timer_pause(OE_TIMER);
	uint32 period_cyc = OE_PWM_PERIOD * CYCLES_PER_MICROSECOND;
	uint16 prescaler = (uint16)(period_cyc / TIM_MAX_RELOAD + 1);
	uint16 overflow = (uint16)((period_cyc + (prescaler / 2)) / prescaler);
	timer_set_prescaler(OE_TIMER, prescaler - 1);
	timer_oc_set_mode(OE_TIMER, oe_channel, TIMER_OC_MODE_PWM_1, 0);
	timer_set_reload(OE_TIMER, overflow);
	timer_cc_enable(OE_TIMER, oe_channel);
	timer_generate_update(OE_TIMER);
	timer_resume(OE_TIMER);
	brightrange = overflow;
#endif

	setBrightness(200);
	textcolor = 1;
	textbgcolor = 0;

#if defined(DEBUG2)
	if (!dd_ptr) dd_ptr = (uint16_t*)malloc(200);
#endif	
}
/*--------------------------------------------------------------------------------------*/
void DMD::setup_main_timer(uint32_t cycles, voidFuncPtr handler) {
	timer_init(MAIN_TIMER);
	timer_pause(MAIN_TIMER);
	uint16 prescaler = (uint16)(cycles / TIM_MAX_RELOAD + 1);
	uint16 overflow = (uint16)((cycles + (prescaler / 2)) / prescaler);
	timer_set_prescaler(MAIN_TIMER, prescaler - 1);
	timer_set_reload(MAIN_TIMER, overflow);
	timer_attach_interrupt(MAIN_TIMER, TIMER_UPDATE_INTERRUPT, handler);
	timer_generate_update(MAIN_TIMER);
	timer_resume(MAIN_TIMER);
}
/*--------------------------------------------------------------------------------------*/
void DMD::generate_muxmask() {
#define set_mux_ch_by_mask(x)  ((uint32_t) x)
#define clr_mux_ch_by_mask(x)  (((uint32_t)x) << 16)

	for (uint8_t i = 0; i < nRows; i++)
	{
		mux_mask2[i] = 0;
		if (mux_cnt == nRows)                // STRIGHT MUX
		{
			for (uint8_t j = 0; j < nRows; j++)
			{
				uint16_t mux_ch_mask = digitalPinToBitMask(mux_pins[j]);
				if (i == j)
				{
					mux_mask2[i] |= clr_mux_ch_by_mask(mux_ch_mask);    //low
				}
				else
				{
					mux_mask2[i] |= set_mux_ch_by_mask(mux_ch_mask);    //high
				}
			}
		}
		else {                             // BINARY MUX
			for (uint8_t j = 0; (1 << j) < nRows; j++)
			{
				uint16_t mux_ch_mask = digitalPinToBitMask(mux_pins[j]);
				if (i & (1 << j))
				{
					mux_mask2[i] |= set_mux_ch_by_mask(mux_ch_mask);
				}
				else
				{
					mux_mask2[i] |= clr_mux_ch_by_mask(mux_ch_mask);
				}
			}
		}
	}
	mux_mask2[nRows] = mux_mask2[0];

}
/*--------------------------------------------------------------------------------------*/
void DMD::set_mux(uint8_t curr_row) {

	*muxsetreg = mux_mask2[curr_row];
}
/*--------------------------------------------------------------------------------------*/
void DMD::switch_row() {
	// switch all LED OFF
	OE_DMD_ROWS_OFF();

	this->set_mux(bDMDByte);

	if (bDMDByte == 2) {
		if (swapflag == true) {    // Swap front/back buffers if requested
			backindex = 1 - backindex;
			swapflag = false;
			bDMDScreenRAM = matrixbuff[backindex]; // Back buffer
			front_buff = matrixbuff[1 - backindex]; // -> front buffer
		}
	}
	if (++bDMDByte > 3) bDMDByte = 0;

	*latsetreg = latmask; // Latch data loaded during *prior* interrupt
	*latsetreg = latmask << 16;// Latch down
	// reenable LEDs
	OE_DMD_ROWS_ON();
}
/*--------------------------------------------------------------------------------------*/

#if defined(__STM32F1__) 
void DMD::OE_DMD_ROWS_OFF() { //pinMode( pin_DMD_nOE, INPUT  ); 
	gpio_set_mode(PIN_MAP[this->pin_DMD_nOE].gpio_device, PIN_MAP[this->pin_DMD_nOE].gpio_bit, GPIO_OUTPUT_PP);
	*oesetreg = oemask << 16;
}
void DMD::OE_DMD_ROWS_ON() { //pinMode( pin_DMD_nOE, OUTPUT  ); 

	gpio_set_mode(PIN_MAP[this->pin_DMD_nOE].gpio_device, PIN_MAP[this->pin_DMD_nOE].gpio_bit, GPIO_AF_OUTPUT_PP);
	timer_set_compare(OE_TIMER, oe_channel, brightness);
}
/*--------------------------------------------------------------------------------------*/
#elif defined(__STM32F4__)
void DMD::OE_DMD_ROWS_OFF() { //pinMode( pin_DMD_nOE, INPUT  ); 
	gpio_set_mode(this->pin_DMD_nOE, GPIO_OUTPUT_PP);
	*oesetreg = oemask << 16;
}
void DMD::OE_DMD_ROWS_ON() { //pinMode( pin_DMD_nOE, OUTPUT  ); 
	gpio_set_mode(this->pin_DMD_nOE, GPIO_AF_OUTPUT_PP);
	timer_set_compare(OE_TIMER, oe_channel, brightness);
}
/*--------------------------------------------------------------------------------------*/
#elif defined(__AVR_ATmega328P__)
void DMD::OE_DMD_ROWS_OFF() { digitalWrite(pin_DMD_nOE, LOW); }
void DMD::OE_DMD_ROWS_ON() { digitalWrite(pin_DMD_nOE, HIGH); }
#endif
/*--------------------------------------------------------------------------------------*/
void DMD::transform_XY(int16_t& bX, int16_t& bY) {

	switch (rotation) {
	case 1:
		_swap_int16_t(bX, bY);
		bX = WIDTH - 1 - bX;
		break;
	case 2:
		bX = WIDTH - 1 - bX;
		bY = HEIGHT - 1 - bY;
		break;
	case 3:
		_swap_int16_t(bX, bY);
		bY = HEIGHT - 1 - bY;
		break;
	}

	byte row = bY / DMD_PIXELS_DOWN;

	if ((connectScheme == CONNECT_ZIGZAG) && (row % 2))
	{
		bX = (WIDTH - 1) - bX;

		bY = bY % DMD_PIXELS_DOWN;
		bY = (DMD_PIXELS_DOWN - 1) - bY;
		bY = row * DMD_PIXELS_DOWN + bY;

	}
}
/*--------------------------------------------------------------------------------------
 Set or clear a pixel at the x and y location (0,0 is the top left corner)
 // Moved to child classes
--------------------------------------------------------------------------------------*/
//void DMD::writePixel(int16_t x, int16_t y, uint16_t color) 


/*--------------------------------------------------------------------------------------*/
void DMD::drawStringX(int bX, int bY, const char* bChars,
	uint16_t color, byte orientation)
{
	int len = 0;
	while (bChars[len] && len < MAX_STRING_LEN) { len++; }
	this->drawString(bX, bY, bChars, len, color, orientation);
}
/*--------------------------------------------------------------------------------------*/
void DMD::drawString(int bX, int bY, const char* bChars, int length,
	uint16_t color, byte orientation)
{
	int16_t miny = 0, maxy = 0, w;
	stringBounds(bChars, length, &w, &miny, &maxy, orientation);
	drawString(bX, bY, bChars, length, color, miny, maxy, orientation);
}
/*--------------------------------------------------------------------------------------*/
void DMD::drawString(int bX, int bY, const char* bChars, int length,
	uint16_t color, int16_t miny, int16_t maxy, byte orientation)
{
	if ((bX >= (WIDTH) || bY >= (HEIGHT)))
		return;
	uint8_t height = Font->get_height();
	if (bY + height < 0) return;

	int strWidth = 0;
	this->drawLine(bX - 1, bY + miny, bX - 1, bY + maxy, inverse_color(color));

	for (int i = 0; i < length; i++) {

		int charWide = this->drawChar(bX + strWidth, bY, bChars[i], color, marqueeMarginH, marqueeMarginL, orientation);

		if (charWide > 0) {
			strWidth += charWide;
			this->drawLine(bX + strWidth, bY + miny, bX + strWidth, bY + maxy, inverse_color(color));
			strWidth++;
		}
		else if (charWide < 0) {
			return;
		}
		if ((bX + strWidth) >= WIDTH || bY >= HEIGHT) return;
	}

}
/*--------------------------------------------------------------------------------------*/
void DMD::drawMarqueeX(const char* bChars, int left, int top, byte orientation)
{
	int len = 0;
	while (bChars[len] && len < MAX_STRING_LEN) { len++; }
	this->drawMarquee(bChars, len, left, top, orientation);
}
/*--------------------------------------------------------------------------------------*/
void DMD::drawMarquee(const char* bChars, int length, int left, int top, byte orientation)
{
	// temp parameter for beta version
	uint8_t matrix_h = 16;

	stringBounds(bChars, length, &marqueeWidth, &marqueeMarginH, &marqueeMarginL, orientation);
	strcpy(marqueeText, bChars);

	if (orientation == 1) {
		marqueeHeight = matrix_h;
	}
	else {
		marqueeHeight = Font->get_height();
	}

	marqueeText[length] = '\0';
	marqueeOffsetY = top;
	marqueeOffsetX = left;
	marqueeLength = length;
	this->drawString(marqueeOffsetX, marqueeOffsetY, marqueeText, marqueeLength, textcolor,
		marqueeMarginH, marqueeMarginL, orientation);
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
	}
	else if (marqueeOffsetX > WIDTH) {
		marqueeOffsetX = -marqueeWidth;
		ret |= 1;
	}
	// Y axis
	if (marqueeOffsetY < -marqueeHeight) {
		marqueeOffsetY = HEIGHT;
		ret |= 1;
	}
	else if (marqueeOffsetY > HEIGHT) {
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
	if (amountY == 0 && use_shift &&
		((amountX == -1) || (amountX == 1))) {
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
		int strWidth = marqueeOffsetX;
		for (int i = 0; i < marqueeLength; i++) {
			int wide = charWidth(marqueeText[i], orientation);
			if (wide > 0) {
				if (strWidth + wide >= limit_X) {
					this->drawChar(strWidth, marqueeOffsetY, marqueeText[i], textcolor, marqueeMarginH, marqueeMarginL, orientation);
					return ret;
				}
				strWidth += wide + 1;
			}
		}

	}
	else {

		if (amountY > 0)	drawFilledBox(marqueeOffsetX, old_y + marqueeMarginH,
			marqueeOffsetX + marqueeWidth, marqueeOffsetY + marqueeMarginH,
			textbgcolor);

		else if (amountY < 0) drawFilledBox(marqueeOffsetX, marqueeOffsetY + marqueeMarginL,
			marqueeOffsetX + marqueeWidth, old_y + marqueeMarginL, textbgcolor);

		else if (amountX > 0) drawFilledBox(old_x, marqueeOffsetY + marqueeMarginH,
			marqueeOffsetX, marqueeOffsetY + marqueeMarginL, textbgcolor);

		else if (amountX < 0) drawFilledBox(marqueeOffsetX + marqueeWidth, marqueeOffsetY + marqueeMarginH,
			old_x + marqueeWidth, marqueeOffsetY + marqueeMarginL,
			textbgcolor);


		this->drawString(marqueeOffsetX, marqueeOffsetY, marqueeText, marqueeLength,
			textcolor, marqueeMarginH, marqueeMarginL, orientation);
	}

	return ret;
}

/*--------------------------------------------------------------------------------------
 Clear the screen in DMD RAM
--------------------------------------------------------------------------------------*/
void DMD::fillScreen(uint16_t color)
{
	this->clearScreen(inverse_color(color));
}
/*--------------------------------------------------------------------------------------*/
void DMD::clearScreen(byte bNormal)
{
	if (bNormal ^ inverse_ALL_flag) // clear all pixels
		memset(bDMDScreenRAM, 0xFF, mem_Buffer_Size);
	else // set all pixels
		memset(bDMDScreenRAM, 0x00, mem_Buffer_Size);
}

/*--------------------------------------------------------------------------------------
 Draw or clear a filled box(rectangle) with a single pixel border
--------------------------------------------------------------------------------------*/
void DMD::drawFilledBox(int x1, int y1, int x2, int y2,
	uint16_t color)
{
	if ((x2 < x1) || (y2 < y1)) return;

	for (int b = y1; b <= y2; b++) {

		//if (use_FastHLine) drawFastHLine(x1, b, (x2 - x1), color);
		//else writeLine(x1, b, x2, b, color);
		drawFastHLine(x1, b, (x2 - x1) + 1, color);
	}
}

/*--------------------------------------------------------------------------------------
	   Select current font
--------------------------------------------------------------------------------------*/
void DMD::selectFont(DMD_Font* font)
{
	this->Font = font;
}

/*--------------------------------------------------------------------------------------
  draw char with selected font at coordinates bX bY
--------------------------------------------------------------------------------------*/
int DMD::drawChar(const int bX, const int bY, const unsigned char letter, uint16_t color, byte orientation)
{
	uint8_t height = Font->get_height();
	return drawChar(bX, bY, letter, color, 0, height, orientation);
}

/*--------------------------------------------------------------------------------------*/
int DMD::drawChar(const int bX, const int bY, const unsigned char letter, uint16_t color, int16_t miny, int16_t maxy, byte orientation)
{
	
	if (bX >= (WIDTH) || bY >= (HEIGHT)) return -1;

	unsigned char c = letter;
	if (!Font->is_char_in(c)) return 0;

	uint8_t fg_col_bytes[3];
	uint8_t bg_col_bytes[3];
	uint16_t bg_color = inverse_color(color);
	uint8_t height = Font->get_height();
	// temp parameter for beta version
	uint8_t matrix_h = 16;

	if (c == ' ') { //CHANGED FROM ' '
		if (orientation) { // vertical scroll
			this->drawFilledBox(bX, bY, bX + height, bY + matrix_h, bg_color);
			return height;
		}
		else {   // normal scroll
			int charWide = Font->get_char_width(' ');
			this->drawFilledBox(bX, bY + miny, bX + charWide, bY + maxy, bg_color);
			return charWide;
		}
	}

	if (Font->is_gfx_font()) {

		DMD_GFX_Font* ff = (DMD_GFX_Font*)Font;
		GFXfont* gfxFont_p = ff->get_font_by_char(c);
		c -= ff->get_first_by_char(c);

#if (defined(__STM32F1__) || defined(__STM32F4__))
		GFXglyph* glyph = &((gfxFont_p->glyph)[c]);
		uint8_t* bitmap = gfxFont_p->bitmap;
#else
		GFXglyph* glyph = &(((GFXglyph*)pgm_read_pointer(&gfxFont_p->glyph))[c]);
		uint8_t* bitmap = (uint8_t*)pgm_read_pointer(&gfxFont_p->bitmap);
#endif		
	
		uint16_t bo = pgm_read_word(&glyph->bitmapOffset);
		uint8_t  w = pgm_read_byte(&glyph->width);
		uint8_t	 h = pgm_read_byte(&glyph->height);
		int8_t  yo = height + (int8_t)pgm_read_byte(&glyph->yOffset);
		uint8_t  xx, yy, bits = 0, bit = 0, bsize, hh;
		int8_t   xo = (int8_t)pgm_read_byte(&glyph->xOffset);
		uint8_t  ww = pgm_read_byte(&glyph->xAdvance);
		if (orientation) {   // vertical scroll
			xo = yo;
			yo = w + (matrix_h - w) / 2;
			hh = xo + h;
			ww = hh;
			this->drawFilledBox(bX, bY, bX + hh, bY + matrix_h, bg_color);
		}
		else {
			if (fast_Hbyte) {
				getColorBytes(fg_col_bytes, color);
				getColorBytes(bg_col_bytes, bg_color);
			}
			this->drawFilledBox(bX, bY + miny, bX + ww, bY + maxy, bg_color);
		}



		for (yy = 0; yy < h; yy++) {
			for (xx = 0; xx < w; xx++) {
				if (!(bit++ & 7)) {
					bits = pgm_read_byte(&bitmap[bo++]);
				}

				if ((!orientation) && (fast_Hbyte)) {
					bsize = ((w - xx) > 8) ? 8 : (w - xx);
					uint8_t bbit = (bit - 1) & 7;
					if (bsize > (8 - bbit)) bsize = 8 - bbit;
					drawHByte(bX + xo + xx, bY + yo + yy, bits, bsize, fg_col_bytes, bg_col_bytes);
					bit += bsize - 1;
					xx += bsize - 1;
					bits <<= bsize;
				}
				else {
					uint16_t col;
					if (bits & 0x80) { col = color; }
					else { col = bg_color; }
					if (orientation) { // vertical scroll
						writePixel(bX + xo + yy, bY + yo - xx, col);
					}
					else {
						writePixel(bX + xo + xx, bY + yo + yy, col);
					}
					bits <<= 1;
				}

			}
		}

		return ww;
	}
	else {


		DMD_Standard_Font* ff = (DMD_Standard_Font*)Font;
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
							writePixel(bX + j, bY + offset + k, bg_color);
						}
					}
				}
			}
		}
		return width;
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
   string bounds
--------------------------------------------------------------------------------------*/
void DMD::stringBounds(const char* bChars, uint8_t length,
	int16_t* w, int16_t* min_y, int16_t* max_y, byte orientation) {

	uint8_t height = Font->get_height();

	if (length == 0) {
		while (bChars[length] && length < MAX_STRING_LEN) { length++; }
	}

	if (Font->is_gfx_font()) {

		DMD_GFX_Font* ff = (DMD_GFX_Font*)Font;
		uint16_t width = 0;
		int16_t minx = _width, miny = _height, maxx = -1, maxy = -1;
		for (int i = 0; i < length; i++) {

			char c = bChars[i];

			if (ff->is_char_in(c)) {

				gfxFont = ff->get_font_by_char(c);
				if (gfxFont == ff->gfxFont2) {
					c += pgm_read_byte(&gfxFont->first) - ff->get_first_by_char(c);
				}
				int16_t x = 0, y = 0;
				if (orientation) {
					miny = _height; maxy = -1;
					charBounds(c, &x, &y, &minx, &miny, &maxx, &maxy);
					width += height + maxy + 2;
				}
				else {
					charBounds(c, &x, &y, &minx, &miny, &maxx, &maxy);
					if (x > 0) width += x + 1;
				}
			}
		}
		if (width) width--;
		*w = width;
		if (orientation) {
			*min_y = 0;
			*max_y = height;
		}
		else {
			*min_y = miny + height;
			*max_y = maxy + height + 1;
		}
	}
	else {
		*w = stringWidth(bChars, length, orientation);
		*min_y = 0;
		*max_y = height - 1;
	}
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

	for (idx = 0; idx < length; idx++) {
		int cwidth = charWidth(bChars[idx], orientation);
		if (cwidth > 0)
			width += cwidth + 1;
	}
	if (width) {
		width--;
	}
	return width;

}

#if defined(DEBUG2)
void DMD::dumpMatrix(void) {

	int i, buffsize = mem_Buffer_Size;

	Serial.print(F("\n\n"
		"#include <avr/pgmspace.h>\n\n"
		"static const uint8_t PROGMEM img[] = {\n  "));

	for (i = 0; i < buffsize; i++) {
		Serial.print(F("0x"));
		if (matrixbuff[backindex][i] < 0x10) Serial.write('0');
		Serial.print(matrixbuff[backindex][i], HEX);
		if (i < (buffsize - 1)) {
			if ((i & 7) == 7) Serial.print(F(",\n  "));
			else             Serial.write(',');
		}
	}
	Serial.println(F("\n};"));
}
void DMD::dumpDDbuf(void) {

	uint16_t i, buffsize = 100;

	Serial.begin(115200);
	Serial.print("Prescaler: ");
	Serial.println(timer_get_prescaler(OE_TIMER));

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
/*--------------------------------------------------------------------------------------*/
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