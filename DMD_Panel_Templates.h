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
 
// == MATRIX TYPES ==

/*--------------------------------------------------------------------------------------*/
//   == Syntax of panel define ==
//
//   #define NAME_OF_PANEL  MUX pins, Panel_width, Panel_height, scan, pattern ID
//            
// example:
//   #define RGB80x40plainS20  5,80,40,20,0		// 5 mux pins(A B C D E), 80x40, scan 1/20, pattern 0
//
//             pattern_ID is unique number for pattern design
//			   pattern ID between 0 and 31 and after 255 are reserved for library use
//                       and from 32 to 127 - for user panels, added by author
//            for new panels added yourself use pattern_ID between 128 and 255
//
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
#define RGB32x32_S8_maxmurugan		3,32,32,8,33	// 32x32 1/8 BINARY from @maxmurugan
#define RGB64x32_S8_OKSingra 		3,64,32,8,3 	// 64x32 1/8 BINARY from @OKSingra


// multirow outdoor, complex pattern
#define RGB32x16_S4_variable		2,32,16,4,32	// 32x16 1/4 variable pattern for 3216_s4 example

//  *** User panels ***
#define RGB32x16_S4			2,32,16,4,50	// 32x16 1/4 ZIGGII pattern matrix, BINARY mux								
#define RGB32x16_S4_bilalibrir		4,32,16,4,51	// 32x16 1/4 ZAGGIZ pattern, DIRECT mux
#define RGB32x16_S2			2,32,16,2,52    // 32x16 1/2 complex pattern, DIRECT mux
#define RGB32x16_S2_quangli		2,32,16,2,53	// 32x16 1/2 complex pattern, DIRECT mux
#define RGB32x16_S2_horro		1,32,16,2,54	// 32x16 1/2 complex pattern, BINARY mux from @horro
#define RGB32x16_S2_OKSingra		1,32,16,2,55	// 32x16 1/2 complex pattern, BINARY mux from @OKSingra
#define RGB40x20_S5_LNikon		3,40,20,5,56	// 40x20 1/5 4pixels pattern, BINARY mux from @LNikon
#define RGB80x40_S10_LNikon     	4,80,40,10,57	// 80x40 1/10 4pixels pattern, BINARY mux from @LNikon
#define RGB64x32_S8_Eu057 		3,64,32,8,58 	// 64x32 1/8 32pix pattern, SHIFT_REG mux from Eugene057
#define RGB104x52_S13_Craftish	 4,104,52,13,59   //104x52 s13 from Craftish, arduino.ru
#define RGB32x16_S4_VitaliyDKZ    	2,32,16,4,60	// 32x16 1/4, BINARY mux
#define RGB32x16_S2_VitaliyDKZ		1,32,16,2,61	// 32x16 1/2, BINARY mux
#define RGB32_16_S4_DIRECT_LNikon	4,32,16,4,62	// 32x16 1/4 DIRECT





/*--------------------------------------------------------------------------------------*/
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE, int COL_DEPTH>

class DMD_RGB : public DMD_RGB_BASE2<COL_DEPTH>
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
        void disableFastTextShift(bool shift) override {}

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
// Non-plain outdoor matrices
// Each such matrix is not like the others, so each needs an individual template.

//--------------------------------------------------------------------------------------
// p6 32x32 scan 8 matrix from @maxmurugan 
// plain pattern with consecutive bytes in horizontal lines
// lower row first
// RGB32x32_S8_maxmurugan
//--------------------------------------------------------------------------------------/
template<int COL_DEPTH>
class DMD_RGB<RGB32x32_S8_maxmurugan, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(3, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 8, 32, 32)
		{
		this->fast_Hbyte = false;
		this->use_shift = false;
		}
	
	// Fast text shift is disabled for complex patterns, so we don't need the method
	void disableFastTextShift(bool shift) override {}

protected:
	uint16_t get_base_addr(int16_t &x, int16_t &y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;

		static const uint8_t A_tbl[16] = { 0,1,2,3,4,5,6,7,
												   0,1,2,3,4,5,6,7 };
		static const uint8_t B_tbl[16] = { 1,1,1,1,1,1,1,1,
													0,0,0,0,0,0,0,0 };
		static const uint8_t C_tbl[8] = { 0,1,2,3,4,5,6,7 };
		static const uint8_t Pan_Okt_cnt = this->DMD_PIXELS_ACROSS / 8;
		uint8_t Oktet_m = B_tbl[pol_y] * Pan_Okt_cnt + (x / 8) % Pan_Okt_cnt;

		uint16_t base_addr = this->x_len * A_tbl[pol_y] + (x / this->DMD_PIXELS_ACROSS) * this->DMD_PIXELS_ACROSS * this->multiplex + C_tbl[Oktet_m] * 8;
		base_addr += x % 8;
		return base_addr;
		}

};


//--------------------------------------------------------------------------------------
// 1/4 matrix I have
//
// with pattern   [1H|1L] [3H|3L] 
//                   |   *   |             
//                [0L|0H] [2L|2H]   
// and BINARY mux
//
// s/n S10-(3535)-4S-3216-A3
//--------------------------------------------------------------------------------------/

template<int COL_DEPTH>
class DMD_RGB<RGB32x16_S4, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(2, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 4, 32, 16)
	{
		this->fast_Hbyte = false;
		this->use_shift = false;
	}
	// Fast text shift is disabled for complex patterns, so we don't need the method
	void disableFastTextShift(bool shift) override {}

protected:
	uint16_t get_base_addr(int16_t& x, int16_t& y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
		uint16_t base_addr = (pol_y % this->nRows) * this->x_len + (x / 8) * this->multiplex * 8;
		if (pol_y / this->nRows) base_addr += x % 8;
		else base_addr += (15 - x % 8);
		return base_addr;
	}
};
//--------------------------------------------------------------------------------------
// 40x20 1/5 matrix from LNikon 
// BINARY mux
// 138 mux, SN16207 driver
//
// 4-pixel pattern, lower line first (LPS type)
// Qiang li Q8S5V3H BQWZ-ZP
//--------------------------------------------------------------------------------------/
template<int COL_DEPTH>
class DMD_RGB<RGB40x20_S5_LNikon, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
	{
	public:
		DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB_BASE2<COL_DEPTH>(3, mux_list, _pin_nOE, _pin_SCLK, pinlist,
				panelsWide, panelsHigh, d_buf, COL_DEPTH, 5, 40, 20)
			{
			this->fast_Hbyte = false;
			this->use_shift = false;
			}
		// Fast text shift is disabled for complex patterns, so we don't need the method
		void disableFastTextShift(bool shift) override {}

	protected:
		uint16_t get_base_addr(int16_t& x, int16_t& y) override {
			this->transform_XY(x, y);
			uint8_t pol_y = y % this->pol_displ;
			x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
			uint16_t base_addr = (pol_y % this->nRows) * this->x_len + (x / 4) * this->multiplex * 4;
			if (pol_y / this->nRows) base_addr += x % 4;
			else base_addr += (4 + x % 4);
			return base_addr;
			}
	};

//--------------------------------------------------------------------------------------
// 80x40 1/10 matrix from LNikon 
// BINARY mux
// SM5166P mux, SM16227S driver
//
// 4-pixel pattern, upper line first (UPS type)
// Qiang li Q4Y10V5H
//--------------------------------------------------------------------------------------/
template<int COL_DEPTH>
class DMD_RGB< RGB80x40_S10_LNikon, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
	{
	public:
		DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB_BASE2<COL_DEPTH>(4, mux_list, _pin_nOE, _pin_SCLK, pinlist,
				panelsWide, panelsHigh, d_buf, COL_DEPTH, 10, 80, 40)
			{
			this->fast_Hbyte = false;
			this->use_shift = false;
			}

		// Fast text shift is disabled for complex patterns, so we don't need the method
		void disableFastTextShift(bool shift) override {}

	protected:

		uint16_t get_base_addr(int16_t& x, int16_t& y) override {
			this->transform_XY(x, y);
			uint8_t pol_y = y % this->pol_displ;
			x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
			uint16_t base_addr = (pol_y % this->nRows) * this->x_len + (x / 4) * this->multiplex * 4;
			if (pol_y / this->nRows) base_addr += (4 + x % 4);
			else  base_addr += x % 4;
			return base_addr;
			}
	};
//--------------------------------------------------------------------------------------
// 1/4 matrix from Bilal Ibrir
//
// with pattern   [0H|0L] [2H|2L] 
//                   |   /   |   /           
//                [1L|1H] [3L|3H]   
// and DIRECT mux
//--------------------------------------------------------------------------------------/

template<int COL_DEPTH>
class DMD_RGB< RGB32x16_S4_bilalibrir, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(4, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 4, 32, 16)
	{
		this->fast_Hbyte = false;
		this->use_shift = false;
	}
	// Fast text shift is disabled for complex patterns, so we don't need the method
	void disableFastTextShift(bool shift) override {}

protected:
	uint16_t get_base_addr(int16_t& x, int16_t& y) override {
		this->transform_XY(x, y);

		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
		uint16_t base_addr = (pol_y % this->nRows) * this->x_len + (x / 8) * this->multiplex * 8;
		if (pol_y / this->nRows) base_addr += 8 + x % 8;
		else base_addr += (7 - x % 8);
		return base_addr;
	}

};

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
//
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
	void disableFastTextShift(bool shift) override {}

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
//
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
	void disableFastTextShift(bool shift) override {}

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
	void disableFastTextShift(bool shift) override {}

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
	void disableFastTextShift(bool shift) override {}

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
// 32-pixel pattern, lower line first 
// Emulator tables:
// A = {8,0,9,1,10,2,11,3,12,4,13,5,14,6,15,7};
// B = {0, 2, 1, 3};
// Qiangli Q5H19B8V1-64x32
//--------------------------------------------------------------------------------------/
template<int COL_DEPTH>
class DMD_RGB<RGB64x32_S8_Eu057, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
	{
	public:
		DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB_BASE2<COL_DEPTH>(3, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 8, 64, 32)
			{
			this->fast_Hbyte = false;
			this->use_shift = false;
			}
		// Fast text shift is disabled for complex patterns, so we don't need the method
		void disableFastTextShift(bool shift) override {}

	protected:
		uint16_t get_base_addr(int16_t& x, int16_t& y) override {
			this->transform_XY(x, y);
			uint8_t pol_y = y % this->pol_displ;
			x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
			uint16_t base_addr = (pol_y % this->nRows) * this->x_len + (x / 32) * this->multiplex * 32 + x % 32;
                        if (pol_y < this->nRows) base_addr+= 32;
			return base_addr;
			}
	};
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
    void disableFastTextShift(bool shift) override {}

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
    *this->datasetreg = expand[*ptr++];
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
// Pixbase 1, BINARY mux
//--------------------------------------------------------------------------------------/
template<int COL_DEPTH>
class DMD_RGB<RGB32x16_S4_VitaliyDKZ, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
	{
	public:
		DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB_BASE2<COL_DEPTH>(2, mux_list, _pin_nOE, _pin_SCLK, pinlist,
				panelsWide, panelsHigh, d_buf, COL_DEPTH, 4, 32, 16)
			{
			this->fast_Hbyte = false;
			this->use_shift = false;
			}
		// Fast text shift is disabled for complex patterns, so we don't need the method
		void disableFastTextShift(bool shift) override {}

	protected:
		uint16_t get_base_addr(int16_t& x, int16_t& y) override {
			this->transform_XY(x, y);
			uint8_t pol_y = y % this->pol_displ;
			x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
			uint16_t base_addr = (pol_y % this->nRows) * this->x_len + x * this->multiplex;
			if (pol_y < this->nRows) base_addr += 1;
			return base_addr;
			}
	};
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
		void disableFastTextShift(bool shift) override {}

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
			void disableFastTextShift(bool shift) override {}

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
/*template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE, int COL_DEPTH>
class DMD_RGB_SHIFTREG_ABC : public DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE,  COL_DEPTH>
{
public:
	DMD_RGB_SHIFTREG_ABC() = 0;
};*/
//--------------------------------------------------------------------------------------
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE, int COL_DEPTH>
class DMD_RGB_SHIFTREG_ABC : public DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>
	
{
public:
	DMD_RGB_SHIFTREG_ABC(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>(mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf)
	{}

protected:
	void generate_muxmask() override
		{
		pinMode(this->mux_pins[0], OUTPUT);
	    pinMode(this->mux_pins[1], OUTPUT);
	    pinMode(this->mux_pins[2], OUTPUT);
		}

	void set_mux(uint8_t curr_row) override {
		byte pin_DMD_A = this->mux_pins[0];
		byte pin_DMD_B = this->mux_pins[1];
		byte pin_DMD_C = this->mux_pins[2];
		// Just shift the row mux by one for incremental access
		digitalWrite(pin_DMD_B, HIGH);
		digitalWrite(pin_DMD_C, (curr_row == 0)); // Shift out 1 for line 0, 0 otherwise
		digitalWrite(pin_DMD_A, HIGH); // Clock out this bit
		digitalWrite(pin_DMD_A, LOW);
		digitalWrite(pin_DMD_B, LOW);
	}

};
#endif
