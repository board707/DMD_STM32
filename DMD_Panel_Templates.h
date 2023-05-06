#pragma once
#include "DMD_RGB.h"

#ifndef DMD_PANEL_TEMPLATES_H
#define DMD_PANEL_TEMPLATES_H
/*--------------------------------------------------------------------------------------
 This file is a part of the library DMD_STM32

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
#define RGB32x16_S4				2,32,16,4,50	// 32x16 1/4 ZIGGII pattern matrix, BINARY mux								
#define RGB32x16_S4_bilalibrir		4,32,16,4,51	// 32x16 1/4 ZAGGIZ pattern, DIRECT mux
#define RGB32x16_S2					2,32,16,2,52    // 32x16 1/2 complex pattern, DIRECT mux
#define RGB32x16_S2_quangli		2,32,16,2,53	// 32x16 1/2 complex pattern, DIRECT mux
#define RGB32x16_S2_horro		1,32,16,2,54	// 32x16 1/2 complex pattern, BINARY mux from @horro
#define RGB32x16_S2_OKSingra	1,32,16,2,55	// 32x16 1/2 complex pattern, BINARY mux from @OKSingra




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
	{}
protected:
	uint16_t get_base_addr(int16_t& x, int16_t& y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
		uint16_t base_addr = (pol_y % this->nRows) * this->x_len +
			(x / this->DMD_PIXELS_ACROSS) * this->multiplex * this->DMD_PIXELS_ACROSS;
		if (pol_y / this->nRows)  base_addr += x % this->DMD_PIXELS_ACROSS;
		else   base_addr += x % this->DMD_PIXELS_ACROSS + this->DMD_PIXELS_ACROSS;
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
		/*uint16_t base_addr = (pol_y % this->nRows) * this->x_len + (x / 16) * this->multiplex * 16;
		switch (pol_y / this->nRows) {
		case 0: base_addr += 32; break;
		case 1: base_addr += 40; break;
		case 2:  break;
		case 3: base_addr += 8; break;
		}

		if (x % 16 > 7) base_addr += 16 + x % 8;
		else base_addr += x % 8;
		*/
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
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE, int COL_DEPTH>
class DMD_RGB_SHIFTREG_ABC : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB_SHIFTREG_ABC() = 0;
};
//--------------------------------------------------------------------------------------
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int COL_DEPTH>
class DMD_RGB_SHIFTREG_ABC<MUX_CNT, P_Width, P_Height, SCAN, 0, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB_SHIFTREG_ABC(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(3, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, false, COL_DEPTH, SCAN, P_Width, P_Height)
	{}

protected:
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
