#pragma once
#include <Arduino.h>
#include "gfxfont.h"


#ifndef pgm_read_byte
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif
#ifndef pgm_read_word
#define pgm_read_word(addr) (*(const unsigned short *)(addr))
#endif
#ifndef pgm_read_dword
#define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#endif

// Pointers are a peculiar case...typically 16-bit on AVR boards,
// 32 bits elsewhere.  Try to accommodate both...

#if !defined(__INT_MAX__) || (__INT_MAX__ > 0xFFFF)
#define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
#else
#define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))
#endif 

// Font Indices
#define FONT_LENGTH             0
#define FONT_FIXED_WIDTH        2
#define FONT_HEIGHT             3
#define FONT_FIRST_CHAR         4
#define FONT_CHAR_COUNT         5
#define FONT_WIDTH_TABLE        6

class DMD_Font
{
public:
	DMD_Font(const uint8_t* ptr);
	~DMD_Font();
	const uint8_t* font_ptr;
	uint8_t firstChar =0;
	uint8_t lastChar =0 ;
	uint8_t fontHeight = 0 ;
	bool gfx_flag = false;

	bool is_gfx_font();
	uint8_t get_first();
	uint8_t get_last();
	uint8_t get_height();

	virtual bool is_char_in(unsigned char c) {} ;

	virtual uint8_t get_char_width(unsigned char c) {};
};
/******************************************************/
class DMD_Standard_Font : public DMD_Font {

public:
	
	DMD_Standard_Font(const uint8_t* ptr);
	bool is_char_in(unsigned char c);
	uint8_t get_char_width(unsigned char c);
	uint16_t get_bitmap_index(unsigned char c);
	bool is_mono_font();
};
/******************************************************/
class DMD_GFX_Font : public DMD_Font {

public:
	DMD_GFX_Font(const uint8_t* ptr, uint8_t h);
    DMD_GFX_Font(const uint8_t* ptr, const uint8_t* ptr2, uint8_t start_code, uint8_t h);
	
	const uint8_t* font_ptr2;
	GFXfont* gfxFont;
	GFXfont* gfxFont2;
	bool font2_flag = false;
	uint8_t firstChar2;
	uint8_t lastChar2;
	bool is_char_in(unsigned char c);
	uint8_t get_char_width(unsigned char c);
	void add_second_font(GFXfont* second, uint8_t start_code);
	uint8_t get_first_by_char(unsigned char c);
	GFXfont* get_font_by_char(unsigned char c);

};
