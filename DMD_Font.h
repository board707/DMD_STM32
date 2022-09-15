/*--------------------------------------------------------------------------------------

 DMD_Font.h  - this file is part of DMD_STM32 library
 
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
#pragma once
#include <Arduino.h>
#include "gfxfont.h"

#if (defined(__STM32F1__)|| defined(__STM32F4__)) 
#include "stm_int.h"
#ifndef pgm_read_byte
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif
#ifndef pgm_read_word
#define pgm_read_word(addr) (*(const unsigned short *)(addr))
#endif
#ifndef pgm_read_dword
#define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#endif
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

	virtual bool is_char_in(unsigned char c) = 0;

	virtual uint8_t get_char_width(unsigned char c, byte orientation = 0) = 0;
	
};
/******************************************************/
class DMD_Standard_Font : public DMD_Font {

public:
	
	DMD_Standard_Font(const uint8_t* ptr);
	bool is_char_in(unsigned char c);
	uint8_t get_char_width(unsigned char c, byte orientation =0 );
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
	uint8_t get_char_width(unsigned char c, byte orientation = 0);

	void add_second_font(GFXfont* second, uint8_t start_code);
	uint8_t get_first_by_char(unsigned char c);
	GFXfont* get_font_by_char(unsigned char c);

};
