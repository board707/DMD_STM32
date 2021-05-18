#pragma once
#include "DMD_STM32a.h"
// MATRIX TYPES
#define RGB64x64plainS32 1
#define RGB80x40plainS20 2
#define RGB64x32plainS16 3
#define RGB32x16plainS8 4
class DMD_RGB_BASE :
	public DMD
{
public:
/*	DMD_RGB_BASE(byte _pin_A, byte _pin_B, byte _pin_C, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false);
	DMD_RGB_BASE(byte _pin_A, byte _pin_B, byte _pin_C, byte _pin_D, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false);
	DMD_RGB_BASE(byte _pin_A, byte _pin_B, byte _pin_C, byte _pin_D, byte _pin_E, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false);
	*/
	DMD_RGB_BASE(byte mux_cnt, uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf, uint8_t n_Rows, byte dmd_pixel_x, byte dmd_pixel_y);

	void init(uint16_t scan_interval = 700);
	virtual void drawPixel(int16_t x, int16_t y, uint16_t color);
	void scan_dmd();
	void oe_disable();
	virtual void clearScreen(byte bNormal);
	virtual void shiftScreen(int8_t step);
	void fillScreen(uint16_t color);
	void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
	void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
	uint16_t
		Color333(uint8_t r, uint8_t g, uint8_t b),
		Color444(uint8_t r, uint8_t g, uint8_t b),
		Color888(uint8_t r, uint8_t g, uint8_t b);
	void dumpMatrix(void);
	void dumpMask(void);
	
	
	~DMD_RGB_BASE();
protected:
	byte pin_DMD_C;
	byte pin_DMD_D;
	byte pin_DMD_E;
	byte rgbpins[6];
	// Pin bitmasks
	PortType clk_clrmask, clkmask;
	
	// PORT register pointers 
	volatile PortType  *dataclrreg, *datasetreg, *dataport, *muxclrreg, *muxsetreg;
	volatile PortType *latsetreg, *latclrreg, *oesetreg, *oeclrreg;
	uint16_t           expand[256];           // 6-to-32 bit converter table
	uint16_t           *mux_mask;         // muxmask 

	// Counters/pointers for interrupt handler:
	volatile uint8_t row, plane;
	volatile uint8_t *buffptr;

	uint8_t          nRows = 0;
	uint8_t         nPlanes =4;
	
};

template <int MATRIX_TYPE>
class DMD_RGB : public DMD_RGB_BASE
{
public:
	DMD_RGB() {}
};
// Matrix types templates
template<>
class DMD_RGB<RGB64x64plainS32> : public DMD_RGB_BASE
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false):
		DMD_RGB_BASE(5, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, 32, 64, 64)
	{}
};
template<>
class DMD_RGB<RGB80x40plainS20> : public DMD_RGB_BASE
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE(5, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, 20, 80, 40)
	{}
};
template<>
class DMD_RGB<RGB64x32plainS16> : public DMD_RGB_BASE
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE(4, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, 16, 64, 32)
	{}
};

template<>
class DMD_RGB<RGB32x16plainS8> : public DMD_RGB_BASE
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE(3, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, 8, 32, 16)
	{}
};
