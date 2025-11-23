#pragma once
#include "DMD_RGB.h"

#ifndef DMD_PANEL_TEMPLATES_H
#define DMD_PANEL_TEMPLATES_H
/*--------------------------------------------------------------------------------------
 This file is a part of the DMD_STM32 library

 DMD_STM32.h  - STM32 port of DMD.h library

 https://github.com/board707/DMD_STM32
 Dmitry Dmitriev (c) 2019-2023
 /--------------------------------------------------------------------------------------*/
 
// Pattern types for panels with multiplex = 2

#define PATTERN_UPS   0b0111
#define PATTERN_UPD   0b0110
#define PATTERN_UNS   0b0101
#define PATTERN_UND   0b0100
#define PATTERN_LPS   0b0011
#define PATTERN_LPD   0b0010
#define PATTERN_LNS   0b0001
#define PATTERN_LND   0b0000

// == MATRIX TYPES ==

/*--------------------------------------------------------------------------------------*/
//   == Syntax of panel define ==
//
//   #define NAME_OF_PANEL  MUX pins, Panel_width, Panel_height, scan, pattern_ID
//            
// example:
//   #define RGB80x40plainS20  5,80,40,20,0		// 5 mux pins(A B C D E), 80x40, scan 1/20, pattern 0
//
//             pattern_ID is unique number for pattern design
//			   pattern ID between 0 and 32 and after 100 are reserved for library use
//                       and from 33 to 99 - for user panels, added by author
//            for new panels added yourself use pattern_ID between 128 and 255
//
//   == Variadic template patterns == (since v1.1.5)
//   
//   #define NAME_OF_PANEL  MUX pins, Panel_width, Panel_height, scan, pattern_ID, Pixbase, Pattern_type
//
//            Variadic patterns:  101 - similar to patter pt1, siplicified, LPS/UPS type only
//								  102 - similar to patter pt2, siplicified, LPS/UPS type only	
//								  111 - similar to patter pt1, generalized, any type
//								  112 - similar to patter pt2, generalized, any type
/*--------------------------------------------------------------------------------------*/
// = matrices with plain pattern =

// single row scan (where scan = height /2 )
#define RGB32x16plainS8   3,32,16,8,0		// 32x16 1/8
#define RGB40x20plainS10  4,40,20,10,0		// 40x20 1/10
#define RGB32x32plainS16  4,32,32,16,0		// 32x32 1/16
#define RGB64x32plainS16  4,64,32,16,0		// 64x32 1/16
#define RGB80x40plainS20  5,80,40,20,0		// 80x40 1/20
#define RGB64x64plainS32  5,64,64,32,0		// 64x64 1/32
#define RGB128x64plainS32 5,128,64,32,0		// 128x64 1/32

// multirow outdoor, plain pattern
#define RGB32x16plainS4			2,32,16,4,1		// 32x16 1/4 BINARY Mux pattern 1
#define RGB32x16plainS4_pt2		2,32,16,4,2		// 32x16 1/4 BINARY Mux pattern 2
#define RGB32x16plainS4_DIRECT		4,32,16,4,1		// 32x16 1/4 DIRECT Mux pattern 1
#define RGB32x16plainS2			1,32,16,2,1		// 32x16 1/2 BINARY
#define RGB32x16plainS2_DIRECT		2,32,16,2,1		// 32x16 1/2 DIRECT
#define RGB32x32_S8_maxmurugan		3,32,32,8,3	// 32x32 1/8 BINARY from @maxmurugan
#define RGB64x32_S8_OKSingra 		3,64,32,8,3 	// 64x32 1/8 BINARY from @OKSingra


// multirow outdoor, complex pattern
#define RGB32x16_S4_variable		2,32,16,4,32	// 32x16 1/4 variable pattern for 3216_s4 example

//  *** User panels ***
#define RGB32x16_S4			2,32,16,4,112,8,PATTERN_LPD	// 32x16 1/4 ZIGGII pattern matrix, BINARY mux								
#define RGB32x16_S4_bilalibrir		4,32,16,4,112,8,PATTERN_UND		// 32x16 1/4 ZAGGIZ pattern, DIRECT mux
#define RGB32x16_S2			2,32,16,2,52    // 32x16 1/2 complex pattern, DIRECT mux
#define RGB32x16_S2_quangli		2,32,16,2,53	// 32x16 1/2 complex pattern, DIRECT mux
#define RGB32x16_S2_horro		1,32,16,2,54	// 32x16 1/2 complex pattern, BINARY mux from @horro
#define RGB32x16_S2_OKSingra		1,32,16,2,55	// 32x16 1/2 complex pattern, BINARY mux from @OKSingra
#define RGB40x20_S5_LNikon		3,40,20,5,102,4,PATTERN_LPS 	// 40x20 1/5 4pixels pattern, BINARY mux from @LNikon
#define RGB80x40_S10_LNikon     	4,80,40,10,102,4,PATTERN_UPS 	// 80x40 1/10 4pixels pattern, BINARY mux from @LNikon
#define RGB64x32_S8_Eu057 		3,64,32,8,102,32,PATTERN_LPS 	// 64x32 1/8 32pix pattern, SHIFT_REG mux from Eugene057
#define RGB104x52_S13_Craftish	 4,104,52,13,59   //104x52 s13 from Craftish, arduino.ru
#define RGB32x16_S4_VitaliyDKZ    	2,32,16,4,102,1,PATTERN_LPS 	// 32x16 1/4, BINARY mux
#define RGB32x16_S2_VitaliyDKZ		1,32,16,2,61	// 32x16 1/2, BINARY mux
#define RGB32_16_S4_DIRECT_LNikon	4,32,16,4,62	// 32x16 1/4 DIRECT
#define RGB32x16_s2_boba7			2,32,16,2,63	// 32x16 1/2 DIRECT, issue #83
#define RGB32x16_S4_saka2080 		2,32,16,4,102,8,PATTERN_LPS  // 32x16 s4 8pixbase, BINARY, from saka2080, issue #79
#define RGB40x20_S5_saka2080    	3,40,20,5,112,8,PATTERN_LND   // 40x20 s5 8pixbase, BINARY, from saka2080, issue #90
#define RGB80x40_S10_OKSingra     	4,80,40,10,102,16,PATTERN_LPS	// 80x40 s10 16pixbase, BINARY, from OKSingra, issue #88
#define RGB32x16_s4_miralay001     	2,32,16,4,102,8,PATTERN_UPS   // 32x16 s4 8pixbase, BINARY, from miralay001, issue #96
#define RGB80x40_S10_ShiPC123 		3,80,40,10,102,4,PATTERN_UPS	// 80x40 s10 4 pixbase, SHIFT_REG, from ShiPC123, issue #104
#define RGB80x40s10SR_digi55 		3,80,40,10,122,16,1             // 80x40 s10, pixbase 16, SHIFT_REG from @digi55, issue #121
#define RGB104x52_S13_funnymind   	4,104,52,13,64                 // 104x52 s13 pixbase 4, SHIFT_REG, from funnymind, issue #145


/*--------------------------------------------------------------------------------------*/
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE, int... Pars>

class DMD_RGB : public DMD_RGB_BASE2<Pars...>
{
public:
	DMD_RGB() = 0;
	
};

//--------------------------------------------------------------------------------------/
// Matrix types templates
//--------------------------------------------------------------------------------------/
// Plain panels with  Scan = P_Height / 2
//--------------------------------------------------------------------------------------/

template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int COL_DEPTH>
class DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, 0, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(MUX_CNT, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, SCAN, P_Width, P_Height)
	{}
};



//--------------------------------------------------------------------------------------
// "plain" type outdoor matrix, BINARY/DIRECT mux
// with consecutive bytes in consecutive horizontal lines 
// (0,1) (2,3)...
// left for testing
//--------------------------------------------------------------------------------------/
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int COL_DEPTH>
class DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, 1, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(MUX_CNT, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, SCAN, P_Width, P_Height)
	{}

protected:
	uint16_t get_base_addr(int16_t& x, int16_t& y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
		uint16_t base_addr = (pol_y / this->multiplex) * this->x_len +
			(x / this->DMD_PIXELS_ACROSS) * this->multiplex * this->DMD_PIXELS_ACROSS +
			(pol_y % this->multiplex) * this->DMD_PIXELS_ACROSS + x % this->DMD_PIXELS_ACROSS;
		return base_addr;
	}
};


//--------------------------------------------------------------------------------------
// "plain" type outdoor matrix, BINARY/DIRECT mux
// with consecutive bytes in horizontal lines 
// separated by nRows lines
// (0,nRows) (1, nRows+1)...
// left for testing
//--------------------------------------------------------------------------------------/
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int COL_DEPTH>
class DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, 2, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(MUX_CNT, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, SCAN, P_Width, P_Height)
	{}

protected:
	uint16_t get_base_addr(int16_t& x, int16_t& y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
		uint16_t base_addr = (pol_y % this->nRows) * this->x_len +
			(x / this->DMD_PIXELS_ACROSS) * this->multiplex * this->DMD_PIXELS_ACROSS +
			(pol_y / this->nRows) * this->DMD_PIXELS_ACROSS + x % this->DMD_PIXELS_ACROSS;
		return base_addr;
	}
};

//--------------------------------------------------------------------------------------
// "plain" type outdoor matrix, BINARY/DIRECT mux
// with consecutive bytes in horizontal lines 
// separated by nRows lines
// scan quarter of height (i.e 64x32 1/8), start scan from nRows line
// (nRows, 0) (nRows+1, 1)...
//
// s/n GKGD-P5-6432-2727-8S-v3.4
//--------------------------------------------------------------------------------------/
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int COL_DEPTH>
class DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, 3, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(MUX_CNT, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, SCAN, P_Width, P_Height)
	{
        this->fast_Hbyte = false;
        this->use_shift = false;
        }
    // Fast text shift is disabled for complex patterns, so we don't need the method
        void disableFastTextShift(bool shift) override {UNUSED1(shift);}

protected:
	uint16_t get_base_addr(int16_t& x, int16_t& y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
		uint16_t base_addr = (pol_y % this->nRows) * this->x_len +
            (x / this->DMD_PIXELS_ACROSS) * this->multiplex * this->DMD_PIXELS_ACROSS +
            x % this->DMD_PIXELS_ACROSS;
            if (pol_y < this->nRows)  base_addr += this->DMD_PIXELS_ACROSS;
		return base_addr;
	}
};

//--------------------------------------------------------------------------------------
//  *** Variadic templates *** 
// outdoor matrix, BINARY/DIRECT mux
// with parametrized Pixbase consecutive bytes 
// 101 is analog to pattern 1 above, 102 is analog to 2
// scan quarter of height (i.e 64x32 1/8),
// The second parameter Pattern - will set UPS/LPS type  UPS = 7, LPS =3  
//--------------------------------------------------------------------------------------/
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int Pixbase, int Pattern, int COL_DEPTH>
class DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, 101, Pixbase, Pattern, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(MUX_CNT, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, SCAN, P_Width, P_Height)
	{
        this->fast_Hbyte = false;
        this->use_shift = false;
        }
    // Fast text shift is disabled for complex patterns, so we don't need the method
		void disableFastTextShift(bool shift) override {UNUSED1(shift);}

protected:
	
	uint16_t get_base_addr(int16_t& x, int16_t& y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
		uint16_t base_addr = (pol_y / this->multiplex) * this->x_len +
            (x / Pixbase) * this->multiplex * Pixbase + x % Pixbase;
            if (Pattern == 3) { if ( ! (pol_y % this->multiplex)) base_addr += Pixbase; }      // LPS
			else if (Pattern == 7) { if (pol_y % this->multiplex)  base_addr += Pixbase; }     // UPS
			else { base_addr += (pol_y % this->multiplex) * Pixbase; } 
		return base_addr;
	}
	
};

template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int Pixbase, int Pattern, int COL_DEPTH>
class DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, 102, Pixbase, Pattern, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(MUX_CNT, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, SCAN, P_Width, P_Height)
	{
        this->fast_Hbyte = false;
        this->use_shift = false;
        }
    // Fast text shift is disabled for complex patterns, so we don't need the method
        void disableFastTextShift(bool shift) override {UNUSED1(shift);}

protected:
	
	uint16_t get_base_addr(int16_t& x, int16_t& y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
		uint16_t base_addr = (pol_y % this->nRows) * this->x_len +
            (x / Pixbase) * this->multiplex * Pixbase + x % Pixbase;
            if (Pattern == 3) { if (pol_y < this->nRows)  base_addr += Pixbase; }          // LPS
			else if (Pattern == 7) { if (pol_y >= this->nRows)  base_addr += Pixbase; }    // UPS
			else { base_addr += (pol_y / this->nRows) * Pixbase; } 
		return base_addr;
	}
	
};

//--------------------------------------------------------------------------------------
//  *** Variadic templates *** 
// outdoor matrix, BINARY/DIRECT mux
// with parametrized Pixbase consecutive byte, generalized
// 111 is analog to pattern 1 above, 112 is analog to 2
// scan quarter of height (i.e 64x32 1/8),
// The second parameter Pattern constructed with three bits (high to low)
//   U/L - ether the first oktet (8 pixs) is lighten Upper than second or vise versa
//   P/N - ether the first octet goes to Positive X direction ( left to right) or Negative
//   S/D - ether the second octet goes to the Same direction as first or not
//--------------------------------------------------------------------------------------/

//--------------------------------------------------------------------------------------/
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int Pixbase, int Pattern, int COL_DEPTH>
class DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, 111, Pixbase, Pattern, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(MUX_CNT, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, SCAN, P_Width, P_Height)
	{
        this->fast_Hbyte = false;
        this->use_shift = false;
        }
    // Fast text shift is disabled for complex patterns, so we don't need the method
        void disableFastTextShift(bool shift) override {UNUSED1(shift);}

protected:
	
	uint16_t get_base_addr(int16_t& x, int16_t& y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;

		constexpr bool Upper = (Pattern & 0xf) & 0b0100;
        constexpr bool Pos =   (Pattern & 0xf) & 0b0010;
        constexpr bool Same =  (Pattern & 0xf) & 0b0001;

		uint16_t base_addr = (pol_y / this->multiplex) * this->x_len +
            (x / Pixbase) * this->multiplex * Pixbase;
		
		bool B = (( ! (pol_y % this->multiplex))^ Upper);  // number of current line in multiplex, 0/1
      
      if (B) // B=1  (second line)
      {
        base_addr += Pixbase;
		if (!(Pos ^ Same)) base_addr += x % Pixbase;
        else base_addr += (Pixbase - x % Pixbase -1);

      }
      else   // first line
      {
        if (Pos) base_addr += x % Pixbase;
        else base_addr += (Pixbase - x % Pixbase -1);
      }

		return base_addr;
	}
	
};

template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int Pixbase, int Pattern, int COL_DEPTH>
class DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, 112, Pixbase, Pattern, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(MUX_CNT, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, SCAN, P_Width, P_Height)
	{
        this->fast_Hbyte = false;
        this->use_shift = false;
        }
    // Fast text shift is disabled for complex patterns, so we don't need the method
        void disableFastTextShift(bool shift) override {UNUSED1(shift);}

protected:
	
	uint16_t get_base_addr(int16_t& x, int16_t& y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;

		constexpr bool Upper = (Pattern & 0xf) & 0b0100;
        constexpr bool Pos =   (Pattern & 0xf) & 0b0010;
        constexpr bool Same =  (Pattern & 0xf) & 0b0001;

		uint16_t base_addr = (pol_y % this->nRows) * this->x_len +
            (x / Pixbase) * this->multiplex * Pixbase;

			 bool B = (((pol_y < this->nRows) ^ Upper));
       if (B) // B=1  (second line)
      {
        base_addr += Pixbase;
		if (!(Pos ^ Same)) base_addr += x % Pixbase;
        else base_addr += (Pixbase - x % Pixbase -1);

      }
      else   // first line
      {
        if (Pos) base_addr += x % Pixbase;
        else base_addr += (Pixbase - x % Pixbase -1);
      }

		return base_addr;
	}
	
};
//--------------------------------------------------------------------------------------
//  *** Variadic templates *** 
// outdoor matrix, BINARY/DIRECT mux
// with parametrized Pixbase consecutive byte, generalized
// 121 is analog to pattern 1 above, 122 is analog to 2
// scan quarter of height (i.e 64x32 1/8),
// 
//   Pattern with LPS/UPS switched every pixbase pixels
//   Pattern = 0 - start from upper line
//   Pattern = 1 - start from lower line
//
// used for @digi55 80x40 s10 panel issue 121
//--------------------------------------------------------------------------------------/

template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int Pixbase, int Pattern, int COL_DEPTH>
class DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, 122, Pixbase, Pattern, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
  DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
    byte panelsWide, byte panelsHigh, bool d_buf = false) :
    DMD_RGB_BASE2<COL_DEPTH>(MUX_CNT, mux_list, _pin_nOE, _pin_SCLK, pinlist,
      panelsWide, panelsHigh, d_buf, COL_DEPTH, SCAN, P_Width, P_Height)
  {
        this->fast_Hbyte = false;
        this->use_shift = false;
        }
    // Fast text shift is disabled for complex patterns, so we don't need the method
        void disableFastTextShift(bool shift) override {UNUSED1(shift);}

protected:
  
  uint16_t get_base_addr(int16_t& x, int16_t& y) override {
    this->transform_XY(x, y);
    uint8_t pol_y = y % this->pol_displ;
    x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
    uint16_t base_addr = (pol_y % this->nRows) * this->x_len +
            (x / Pixbase) * this->multiplex * Pixbase + x % Pixbase;
    if ((Pattern + (x % P_Width)/Pixbase)%2)  { if (pol_y < this->nRows)  base_addr += Pixbase; }         
    else { if (pol_y >=  this->nRows)  base_addr += Pixbase; }
     
    return base_addr;
  }
  
};
//--------------------------------------------------------------------------------------
// Non-plain outdoor matrices
// Each such matrix is not like the others, so each needs an individual template.

//--------------------------------------------------------------------------------------
//
// !!!!!!!!!!!!!  Removed, the same as pattern 3  !!!!!!!!!!!!!!!!!!!
//
// p6 32x32 scan 8 matrix from @maxmurugan 
// plain pattern with consecutive bytes in horizontal lines
// lower row first
// RGB32x32_S8_maxmurugan
// #define RGB32x32_S8_maxmurugan		3,32,32,8,3	// 32x32 1/8 BINARY from @maxmurugan
//--------------------------------------------------------------------------------------/

//--------------------------------------------------------------------------------------
// 1/4 matrix I have
//
// with pattern   [1H|1L] [3H|3L] 
//                   |   *   |             
//                [0L|0H] [2L|2H]   
// and BINARY mux
//
// 8-pixel pixbase, LPD type
// s/n S10-(3535)-4S-3216-A3
//
// #define RGB32x16_S4			2,32,16,4,50
// !!!!!!!!!! Replaced with 112, 8, LPD
//--------------------------------------------------------------------------------------/

//--------------------------------------------------------------------------------------
// 1/4 matrix from Bilal Ibrir
//
// with pattern   [0H|0L] [2H|2L] 
//                   |   /   |   /           
//                [1L|1H] [3L|3H]   
// and DIRECT mux
// 8-pixel pixbase, UND type
//
// RGB32x16_S4_bilalibrir -- replaced with 112, 8, UND
//--------------------------------------------------------------------------------------/

//--------------------------------------------------------------------------------------
// 40x20 1/5 matrix from LNikon 
// BINARY mux
// 138 mux, SN16207 driver
//
// 4-pixel pixbase, lower line first (LPS type)
// Qiang li Q8S5V3H BQWZ-ZP
//
// RGB40x20_S5_LNikon  -- replaced with 102, 4, LPS
//--------------------------------------------------------------------------------------/

//--------------------------------------------------------------------------------------
// 80x40 1/10 matrix from LNikon 
// BINARY mux
// SM5166P mux, SM16227S driver
//
// 4-pixel pixbase, upper line first (UPS type)
// Qiang li Q4Y10V5H
//
// RGB80x40_S10_LNikon -- replaced with 102, 4, UPS
//--------------------------------------------------------------------------------------/


//--------------------------------------------------------------------------------------
// 1/2 matrix I have
//
// with pattern   [0H|0L]     [4H|4L] 
//                   |       /   |              
//                [1L|1H]   / [5L|5H]   
//                   |     /     |
//                [2H|2L] /   [6H|6L] 
//                   |   /       |   /           
//                [3L|3H]     [7L|7H]   
// and DIRECT mux
// 8-pixel pixbase
// s/n P10(3535)16X32-2S-V1.3
//--------------------------------------------------------------------------------------/

template<int COL_DEPTH>
class DMD_RGB<RGB32x16_S2, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(2, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 2, 32, 16)
	{
		this->fast_Hbyte = false;
		this->use_shift = false;
	}
	// Fast text shift is disabled for complex patterns, so we don't need the method
	void disableFastTextShift(bool shift) override {UNUSED1(shift);}

protected:
	uint16_t get_base_addr(int16_t& x, int16_t& y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
		uint16_t base_addr = (pol_y % this->nRows) * this->x_len + (x / 8) * this->multiplex * 8 + (pol_y / this->nRows) * 8;
		if (((pol_y / this->nRows) % 2) == 0) { base_addr += (7 - x % 8); }
		else base_addr += x % 8;
		return base_addr;
	}

};

/*--------------------------------------------------------------------------------------*/
// 32x16 1/2 matrix from horro
// Binary mux
// 8-pixel pixbase
// s/n P10(3535)16X32-2S-M1
//--------------------------------------------------------------------------------------/
template<int COL_DEPTH>
class DMD_RGB<RGB32x16_S2_horro, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(1, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 2, 32, 16)
	{
		this->fast_Hbyte = false;
		this->use_shift = false;
	}
	// Fast text shift is disabled for complex patterns, so we don't need the method
	void disableFastTextShift(bool shift) override {UNUSED1(shift);}

protected:
	uint16_t get_base_addr(int16_t& x, int16_t& y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;

		static const uint8_t A_tbl[8] = { 0,1,0,1,0,1,0,1 };
		static const uint8_t B_tbl[8] = { 2,2,3,3,0,0,1,1 };
		static const uint8_t C_tbl[16] = { 0,2,4,6,
								   1,3,5,7,
								   8,10,12,14,
								   9,11,13,15 };
		static const uint8_t Pan_Okt_cnt = this->DMD_PIXELS_ACROSS / 8;
		uint8_t Oktet_m = B_tbl[pol_y] * Pan_Okt_cnt + (x / 8) % Pan_Okt_cnt;

		uint16_t base_addr = this->x_len * A_tbl[pol_y] + (x / this->DMD_PIXELS_ACROSS) * this->DMD_PIXELS_ACROSS * this->multiplex + C_tbl[Oktet_m] * 8;
		if (!(B_tbl[pol_y] % 2)) { base_addr += (7 - x % 8); }
		else base_addr += x % 8;
		
		return base_addr;
	}

};

/*--------------------------------------------------------------------------------------*/
// 32x16 1/2 matrix from OKSingra
// Binary mux
// !! Non-standard !!  3rd quarter pattern is different from 1st, 2nd and 4th
//
// s/n GKGD-P10-3216-2727-2S-v1.4
//--------------------------------------------------------------------------------------/
template<int COL_DEPTH>
class DMD_RGB<RGB32x16_S2_OKSingra, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(1, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 2, 32, 16)
	{
		this->fast_Hbyte = false;
		this->use_shift = false;
	}
	// Fast text shift is disabled for complex patterns, so we don't need the method
	void disableFastTextShift(bool shift) override {UNUSED1(shift);}

protected:
	uint16_t get_base_addr(int16_t& x, int16_t& y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;

		static const uint8_t A_tbl[8] = { 0,1,0,1,0,1,0,1 };
		static const uint8_t B_tbl[8] = { 3,3,2,2,1,1,0,0 };
		static const uint8_t C_tbl[16] = { 0,4,10,12,
								           1,5,11,13,
								           2,6,8,14,
								           3,7,9,15 };
		static const uint8_t Pan_Okt_cnt = this->DMD_PIXELS_ACROSS / 8;
		uint8_t Oktet_m = B_tbl[pol_y] * Pan_Okt_cnt + (x / 8) % Pan_Okt_cnt;

		uint16_t base_addr = this->x_len * A_tbl[pol_y] + (x / this->DMD_PIXELS_ACROSS) * this->DMD_PIXELS_ACROSS * this->multiplex + C_tbl[Oktet_m] * 8;
		if ((B_tbl[pol_y] % 2)) { base_addr += (7 - x % 8); }
		else base_addr += x % 8;
		
		return base_addr;
	}

};
//--------------------------------------------------------------------------------------
// 1/2 matrix from quangli with two-byte pattern
// DIRECT mux
//
// Qiang li Q10C2V5.2H BQWZ-ZP
//--------------------------------------------------------------------------------------/
template<int COL_DEPTH>
class DMD_RGB<RGB32x16_S2_quangli, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(2, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 2, 32, 16)
	{
		this->fast_Hbyte = false;
		this->use_shift = false;
	}
	// Fast text shift is disabled for complex patterns, so we don't need the method
	void disableFastTextShift(bool shift) override {UNUSED1(shift);}

protected:
	uint16_t get_base_addr(int16_t& x, int16_t& y) override {
		this->transform_XY(x, y);

		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
		
		static const uint8_t A_tbl[8] = { 0,1,0,1,0,1,0,1 };
		static const uint8_t B_tbl[8] = { 2,2,3,3,0,0,1,1 };
		static const uint8_t C_tbl[16] = { 0,2,8,10,
											1,3,9,11,
										   4,6,12,14,
										   5,7,13,15 };
		static const uint8_t Pan_Okt_cnt = this->DMD_PIXELS_ACROSS / 8;
		uint8_t Oktet_m = B_tbl[pol_y] * Pan_Okt_cnt + (x / 8) % Pan_Okt_cnt;

		uint16_t base_addr = this->x_len * A_tbl[pol_y] + (x / this->DMD_PIXELS_ACROSS) * this->DMD_PIXELS_ACROSS * this->multiplex + C_tbl[Oktet_m] * 8;
		base_addr += x % 8;
		return base_addr;
	}

};
//--------------------------------------------------------------------------------------
// 64x32 1/8 matrix from Eugene057
// 595 (SHIFT_REG) mux
// DP32020A mux, SM16208SJ driver
//
// 32-pixel pixbase, lower line first, LPS type
// Emulator tables:
// A = {8,0,9,1,10,2,11,3,12,4,13,5,14,6,15,7};
// B = {0, 2, 1, 3};
// Qiangli Q5H19B8V1-64x32
//
// RGB64x32_S8_Eu057  -- replaced with 102,32,LPS
//--------------------------------------------------------------------------------------/

//--------------------------------------------------------------------------------------
// 104x52 S13 panel from Craftish
// icn2013 (138) mux
// sm16306 driver
//
// Very weird panel. Each row has a 7 x 16bit drivers, which gives 112 pixels.
// Since the panel is only 104 pixels wide, the 8 pins in the middle of the driver chain 
// are not connected to anything. When loading data, you have to insert zeros into each row.
// 
// STM32 only!
// For STM32F4 you must comment RGB_DMA define in DMD_config.h line 26
//--------------------------------------------------------------------------------------/
template<int COL_DEPTH>
class DMD_RGB<RGB104x52_S13_Craftish, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
  public:
    DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
            byte panelsWide, byte panelsHigh, bool d_buf = false) :
      DMD_RGB_BASE2<COL_DEPTH>(4, mux_list, _pin_nOE, _pin_SCLK, pinlist,
                               panelsWide, panelsHigh, d_buf, COL_DEPTH, 13, 104, 52)
    {
      this->fast_Hbyte = false;
      this->use_shift = false;
    }
    // Fast text shift is disabled for complex patterns, so we don't need the method
    void disableFastTextShift(bool shift) override {UNUSED1(shift);}

  protected:
    uint16_t get_base_addr(int16_t& x, int16_t& y) override {
      this->transform_XY(x, y);
      uint8_t pol_y = y % this->pol_displ;
      x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
      uint16_t base_addr = (pol_y % this->nRows) * this->x_len +
                           (x / this->DMD_PIXELS_ACROSS) * this->multiplex * this->DMD_PIXELS_ACROSS +
                           x % this->DMD_PIXELS_ACROSS;
      if (pol_y < this->nRows)  base_addr += this->DMD_PIXELS_ACROSS;
      return base_addr;
    }

    void scan_dmd_p3() {

      volatile static uint8_t* ptr;
      ptr = this->buffptr;

#define PEE                    \
    *this->datasetreg = this->clkmask << 16;     \
    *this->datasetreg = this->clkmask;

#if defined (DIRECT_OUTPUT)
#define pew                    \
    *this->datasetreg = this->clk_clrmask;     \
    *this->datasetreg = *ptr++;
#else
#define pew                    \
    *this->datasetreg = this->clk_clrmask;     \
    *this->datasetreg = this->expand[*ptr++];
#endif

      for (uint16_t uu = 0; uu < this->x_len; uu += 104)
      {

        pew pew pew pew pew pew pew pew
        pew pew pew pew pew pew pew pew

        pew pew pew pew pew pew pew pew
        pew pew pew pew pew pew pew pew

        pew pew pew pew pew pew pew pew
        pew pew pew pew pew pew pew pew

        PEE PEE PEE PEE pew pew pew pew
        pew pew pew pew PEE PEE PEE PEE

        pew pew pew pew pew pew pew pew
        pew pew pew pew pew pew pew pew

        pew pew pew pew pew pew pew pew
        pew pew pew pew pew pew pew pew

        pew pew pew pew pew pew pew pew
        pew pew pew pew pew pew pew pew

      }

      *this->datasetreg = this->clkmask << 16; // Set clock low
      this->buffptr += this->displ_len;

#undef pew

    }
};
//--------------------------------------------------------------------------------------
// 32x16 1/4 matrix from VitaliyDKZ  (issue #57)
//
// with pattern   [1] [3] 
//                   |   /   |   /           
//                [0] [2]   
// Pixbase 1, BINARY mux, LPS type
//
// RGB32x16_S4_VitaliyDKZ -- replaced with 102,1,LPS
//--------------------------------------------------------------------------------------/

//--------------------------------------------------------------------------------------
// 32x16 1/2 matrix from VitaliyDKZ  (issue #60)
//
// Pixbase 1, BINARY mux
// 
// One pixel by line, from low to upper rows
// Model: P10-2S-3535-16x32-V2.3
//--------------------------------------------------------------------------------------/
template<int COL_DEPTH>
class DMD_RGB<RGB32x16_S2_VitaliyDKZ, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
	{
	public:
		DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB_BASE2<COL_DEPTH>(1, mux_list, _pin_nOE, _pin_SCLK, pinlist,
				panelsWide, panelsHigh, d_buf, COL_DEPTH, 2, 32, 16)
			{
			this->fast_Hbyte = false;
			this->use_shift = false;
			}
		// Fast text shift is disabled for complex patterns, so we don't need the method
		void disableFastTextShift(bool shift) override {UNUSED1(shift);}

	protected:
		uint16_t get_base_addr(int16_t& x, int16_t& y) override {
			this->transform_XY(x, y);
			uint8_t pol_y = y % this->pol_displ;
			x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
			uint16_t base_addr = (pol_y % this->nRows) * this->x_len + x * this->multiplex;
			base_addr += this->multiplex - pol_y / this->nRows - 1;
			return base_addr;
			}
};
//--------------------------------------------------------------------------------------
// 32x16 1/4 matrix from LNikon 
// DIRECT mux
//
// 4-pixel pattern
//			1	4 - 5
//			|	|	|
//			2 - 3	6 -
// EVOSSON P10-4S-3535-3216
//--------------------------------------------------------------------------------------/
template<int COL_DEPTH>
class DMD_RGB<RGB32_16_S4_DIRECT_LNikon, COL_DEPTH> : public
	DMD_RGB_BASE2<COL_DEPTH>
	{
	public:
		DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t*
			pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB_BASE2<COL_DEPTH>(4, mux_list, _pin_nOE, _pin_SCLK, pinlist,
				panelsWide, panelsHigh, d_buf, COL_DEPTH, 4, 32, 16)
			{
			this->fast_Hbyte = false;
			this->use_shift = false;
			}
		// Fast text shift is disabled for complex patterns, so we don't 
		// need the method
			void disableFastTextShift(bool shift) override {UNUSED1(shift);}

	protected:
		uint16_t get_base_addr(int16_t& x, int16_t& y) override {
			this->transform_XY(x, y);
			uint8_t pol_y = y % this->pol_displ;
			x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;

			static const uint8_t A_tbl[8] = { 0,1,2,3,0,1,2,3 };
			static const uint8_t B_tbl[8] = { 0,0,0,0,1,1,1,1 };
			static const uint8_t C_tbl[16] = { 0,3,4,7,8,11,12,15,
											  1,2,5,6,9,10,13,14 };
			static const uint8_t Pan_Okt_cnt = this->DMD_PIXELS_ACROSS / 4;
			uint8_t Oktet_m = B_tbl[pol_y] * Pan_Okt_cnt + (x / 4) %
				Pan_Okt_cnt;

			uint16_t base_addr = this->x_len * A_tbl[pol_y] + (x /
				this->DMD_PIXELS_ACROSS) * this->DMD_PIXELS_ACROSS * this->multiplex +
				C_tbl[Oktet_m] * 4;
			base_addr += x % 4;

			return base_addr;
			}

	};

//--------------------------------------------------------------------------------------
// 32x16 1/2 matrix from boba7 (issue 83)
//
// Pixbase 8, DIRECT mux
//
// MB5124 driver
/* with pattern   [3H|3L]     [7H|7L] 
//                   |   \       |   \         
//                [2L|2H] \   [6L|6H]   
//                   |     \     |
//                [1H|1L]   \ [5H|5L] 
//                   |       \   |        
//                [0L|0H]     [4L|4H]   
*/
//--------------------------------------------------------------------------------------/

template<int COL_DEPTH>
class DMD_RGB<RGB32x16_s2_boba7, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
	{
	public:
		DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB_BASE2<COL_DEPTH>(2, mux_list, _pin_nOE, _pin_SCLK, pinlist,
				panelsWide, panelsHigh, d_buf, COL_DEPTH, 2, 32, 16)
			{
			this->fast_Hbyte = false;
			this->use_shift = false;
			}
		// Fast text shift is disabled for complex patterns, so we don't need the method
		void disableFastTextShift(bool shift) override {UNUSED1(shift);}

	protected:
		uint16_t get_base_addr(int16_t& x, int16_t& y) override {
			this->transform_XY(x, y);
			uint8_t pol_y = y % this->pol_displ;
			x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;

			static const uint8_t px_base = 8;
			static const uint8_t D_tbl[4] = { 3, 2, 1, 0 };
			static const uint8_t C_tbl[4] = { 1, 0, 1, 0 };

			uint16_t base_addr = (pol_y % this->nRows) * this->x_len + (x / px_base) * this->multiplex * px_base;
			uint8_t Oktet_m = pol_y / this->nRows;
			base_addr += D_tbl[Oktet_m] * px_base;
			if (C_tbl[Oktet_m] == 1) {
				base_addr += (px_base - 1) - x % px_base;
				}
			else
				{
				base_addr += x % px_base;
				}
			return base_addr;

			}

	};

//--------------------------------------------------------------------------------------
// 104x52 s13 panel from funnymind (issue 145)
//
// Drivers DP5135 + RUL5158c
//
// Pixbase 4, 595 mux
//
/* Very weird pattern
//
// Two pixbase sections from the left are switching (like 122 pattern)
// all other pixels to the right are in continious lines.
*/
//--------------------------------------------------------------------------------------/
template<int COL_DEPTH>
class DMD_RGB<RGB104x52_S13_funnymind, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
	{
	public:
		DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB_BASE2<COL_DEPTH>(4, mux_list, _pin_nOE, _pin_SCLK, pinlist,
				panelsWide, panelsHigh, d_buf, COL_DEPTH, 13, 104, 52)
			{
			this->fast_Hbyte = false;
			this->use_shift = false;
			}
		// Fast text shift is disabled for complex patterns, so we don't 
		// need the method
			void disableFastTextShift(bool shift) override {UNUSED1(shift);}

	protected:
		uint16_t get_base_addr(int16_t& x, int16_t& y) override {
			this->transform_XY(x, y);
			uint8_t pol_y = y % this->pol_displ;
			x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
                        
            static const uint8_t px_base = 4; 
			static const uint8_t C_tbl[52] = 
			      { 0,3,28,29,30, 31,32,33,34,35, 36,37,38,39,40, 41,42,43,44,45, 46,47,48,49,50, 51,
                    1,2,4,5,6, 7,8,9,10,11, 12,13,14,15,16, 17,18,19,20,21, 22,23,24,25,26,27 };
			
			static const uint8_t Pan_Okt_cnt = this->DMD_PIXELS_ACROSS / px_base;
			uint8_t Oktet_m = (pol_y / this->nRows) * Pan_Okt_cnt + (x / px_base) % Pan_Okt_cnt;

			uint16_t base_addr = (pol_y % this->nRows) * this->x_len  +
                       (x /this->DMD_PIXELS_ACROSS) * this->DMD_PIXELS_ACROSS * this->multiplex +
						C_tbl[Oktet_m] * px_base;
			base_addr += x % px_base;

			return base_addr;
			}

	};
//--------------------------------------------------------------------------------------
/*template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE, int COL_DEPTH>
class DMD_RGB_SHIFTREG_ABC : public DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE,  COL_DEPTH>
{
public:
	DMD_RGB_SHIFTREG_ABC() = 0;
};*/
//--------------------------------------------------------------------------------------
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE, int... Pars>
class [[deprecated("Use dmd.configure_multiplexer() instead")]]
DMD_RGB_SHIFTREG_ABC : public DMD_RGB<33, P_Width, P_Height, SCAN, SCAN_TYPE, Pars... >
	
{
public:
	DMD_RGB_SHIFTREG_ABC(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB<33, P_Width, P_Height, SCAN, SCAN_TYPE, Pars... >(mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf)
	{}

protected:
	
};
#endif
