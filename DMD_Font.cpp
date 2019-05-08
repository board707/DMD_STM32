#include "DMD_Font.h"



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

bool DMD_Font::is_char_in(unsigned char c) {
	if (c < get_first() || c > get_last()) return false;
	else return true;
}



DMD_Standard_Font::DMD_Standard_Font(const uint8_t* ptr) :DMD_Font(ptr) {

	gfx_flag = false;
	firstChar = pgm_read_byte(font_ptr + FONT_FIRST_CHAR);
	lastChar = firstChar + pgm_read_byte(font_ptr + FONT_CHAR_COUNT);
	fontHeight = pgm_read_byte(font_ptr + FONT_HEIGHT);
}

bool DMD_Standard_Font::is_mono_font() {
	// zero length is flag indicating fixed width font (array does not contain width data entries)
	return (pgm_read_byte(this->font_ptr + FONT_LENGTH) == 0
		    && pgm_read_byte(this->font_ptr + FONT_LENGTH + 1) == 0);
}
uint8_t DMD_Standard_Font::get_char_width(unsigned char c) {
	uint8_t width = 0;
	if (this->is_char_in(c)) {
		if (c == ' ') c = 'n';
		c -= this->firstChar;
		// code from DMDSTM
		if (this->is_mono_font()) {
			// fixed width font
			width = pgm_read_byte(this->font_ptr + FONT_FIXED_WIDTH);
		}
		else {
			// variable width font, read width data
			width = pgm_read_byte(this->font_ptr + FONT_WIDTH_TABLE + c);
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
DMD_GFX_Font::DMD_GFX_Font(const uint8_t* ptr, uint8_t font_h) :DMD_Font(ptr) {

	gfx_flag = true;
	gfxFont = (GFXfont*)font_ptr;

	firstChar = (uint8_t)pgm_read_word(&gfxFont->first);
	lastChar = (uint8_t) pgm_read_word(&gfxFont->last);
	fontHeight = font_h;
	
}

uint8_t DMD_GFX_Font::get_char_width(unsigned char c) {
	if (this->is_char_in(c)) {
		c -= this->firstChar;
		GFXglyph *glyph = &(((GFXglyph *)pgm_read_pointer(&gfxFont->glyph))[c]);
		return (uint8_t)pgm_read_byte(&glyph->xAdvance);
	}
	else return 0;
}