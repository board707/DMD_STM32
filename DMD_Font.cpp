/*--------------------------------------------------------------------------------------

 DMD_Font.cpp  - this file is part of DMD_STM32 library
 
   by Dmitry Dmitriev (c) 2019
 
 

 ---

 This program is free software: you can redistribute it and/or modify it under the terms
 of the version 3 GNU General Public License as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with this program.
 If not, see <http://www.gnu.org/licenses/>.

--------------------------------------------------------------------------------------*/
#include "DMD_Font.h"


/* ------------------------- DMD_Font -------------------------*/
DMD_Font::DMD_Font(const uint8_t* ptr):font_ptr(ptr)
{
}


DMD_Font::~DMD_Font()
{
}

bool DMD_Font::is_gfx_font() { return gfx_flag; }
uint8_t DMD_Font::get_first() { return firstChar; }
uint8_t DMD_Font::get_last() { return lastChar; }
uint8_t DMD_Font::get_height() { return fontHeight; }



/* -------------------- DMD_Standard_Font -------------------------*/

DMD_Standard_Font::DMD_Standard_Font(const uint8_t* ptr) :DMD_Font(ptr) {

	gfx_flag = false;
	firstChar = pgm_read_byte(font_ptr + FONT_FIRST_CHAR);
	lastChar = firstChar + pgm_read_byte(font_ptr + FONT_CHAR_COUNT);
	fontHeight = pgm_read_byte(font_ptr + FONT_HEIGHT);
}

bool DMD_Standard_Font::is_char_in(unsigned char c) {
	if (c < get_first() || c > get_last()) return false;
	else return true;
}
bool DMD_Standard_Font::is_mono_font() {
	// zero length is flag indicating fixed width font (array does not contain width data entries)
	return (pgm_read_byte(this->font_ptr + FONT_LENGTH) == 0
		    && pgm_read_byte(this->font_ptr + FONT_LENGTH + 1) == 0);
}
uint8_t DMD_Standard_Font::get_char_width(unsigned char c, byte orientation) {
	uint8_t width = 0;
	
	if (this->is_char_in(c)) {
		// code from DMDSTM
		if (this->is_mono_font()) {
			// fixed width font
			width = pgm_read_byte(this->font_ptr + FONT_FIXED_WIDTH);
		}
		else {
			// variable width font, read width data
			unsigned char ind = c - this->firstChar;
			width = pgm_read_byte(this->font_ptr + FONT_WIDTH_TABLE + ind);
			if ((c == ' ') && (width == 0)) {      // if width of SPACE == 0
				if (this->is_char_in('n')) {       // and font contain letter n
					ind = 'n' - this->firstChar;   // set width for SPASE as 'n'
					width = pgm_read_byte(this->font_ptr + FONT_WIDTH_TABLE + ind);
				}
				else { width = 5; }                // else set width SPACE = 5
			}
		}
		
	}
	return width;
}


uint16_t DMD_Standard_Font::get_bitmap_index(unsigned char c) {
	uint8_t bytes = (fontHeight + 7) / 8;
	uint16_t index = 0;
	uint8_t w = this->get_char_width(c);
	c -= this->firstChar;
	if (this->is_mono_font()) {
		// fixed width font
		index = c * bytes * w + FONT_WIDTH_TABLE;
	}
	else {
		for (uint8_t i = 0; i < c; i++) {
			index += pgm_read_byte(this->font_ptr + FONT_WIDTH_TABLE + i);
		}
		index = index * bytes + pgm_read_byte(font_ptr + FONT_CHAR_COUNT) + FONT_WIDTH_TABLE;
	}
	return index;
}


/* ------------------ DMD_GFX_Font -------------------------*/

DMD_GFX_Font::DMD_GFX_Font(const uint8_t* ptr, const uint8_t* ptr2, uint8_t start_code, uint8_t font_h)
: DMD_Font(ptr) , font_ptr2(ptr2) 
{
	gfx_flag = true;
	gfxFont = (GFXfont*)font_ptr;

	firstChar = pgm_read_byte(&gfxFont->first);
	lastChar =  pgm_read_byte(&gfxFont->last);
	fontHeight = font_h;
	if (font_ptr2 != NULL) {
		gfxFont2 = (GFXfont*)font_ptr2;
		font2_flag = true;
		firstChar2 = start_code;
		lastChar2 = start_code + pgm_read_byte(&gfxFont2->last) - pgm_read_byte(&gfxFont2->first);
	}
}	


DMD_GFX_Font::DMD_GFX_Font(const uint8_t* ptr, uint8_t font_h) :DMD_GFX_Font(ptr, NULL, 0, font_h) {

	font2_flag = false;
}



bool DMD_GFX_Font::is_char_in(unsigned char c) {
	if (c >= get_first() && c <= get_last()) return true;
	if (font2_flag && (c >= firstChar2 && c <= lastChar2)) return true;
	else return false;
}

uint8_t DMD_GFX_Font::get_char_width(unsigned char c, byte orientation) {
	if (this->is_char_in(c)) {
		GFXfont* gfxFont_ptr;
		if (font2_flag && (c > get_last() )) {
			c -= firstChar2;
			gfxFont_ptr = gfxFont2;
		}
		else {
			c -= firstChar;
			gfxFont_ptr = gfxFont;
		}
#if (defined(__STM32F1__) || defined(__STM32F4__))
		GFXglyph* glyph = &((gfxFont_ptr->glyph)[c]);
#else
		GFXglyph* glyph = &(((GFXglyph*)pgm_read_pointer(&(gfxFont_ptr->glyph)))[c]);
#endif
	
		if (orientation) {
			   int8_t char_w = fontHeight + (int8_t)pgm_read_byte(&glyph->yOffset) + pgm_read_byte(&glyph->height) ;
			   if (char_w < 0) return 0;
			   else return (uint8_t)char_w;
		}	
		else { return (uint8_t)pgm_read_byte(&glyph->xAdvance);}
	}
	else return 0;
}

void DMD_GFX_Font::add_second_font(GFXfont* second, uint8_t start_code) {
	gfxFont2 = second;
	font2_flag = true;
	firstChar2 = start_code;
	lastChar2 = start_code + pgm_read_byte(&gfxFont2->last) - pgm_read_byte(&gfxFont2->first);
}

uint8_t DMD_GFX_Font::get_first_by_char(unsigned char c) {
	if (font2_flag && (c > get_last() )) return firstChar2;
	else return firstChar;
}

GFXfont* DMD_GFX_Font::get_font_by_char(unsigned char c) {
	if (font2_flag && (c > get_last() )) {return this->gfxFont2;}
	else return this->gfxFont;
}