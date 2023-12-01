#pragma once
#ifndef DMD_RGB_FM6126_H
#define DMD_RGB_FM6126_H
/*--------------------------------------------------------------------------------------
 This file is a part of the DMD_STM32 library

 DMD_STM32.h  - STM32 port of DMD.h library

 https://github.com/board707/DMD_STM32
 Dmitry Dmitriev (c) 2019-2023
/--------------------------------------------------------------------------------------*/

// FM6126a driver class 

// (supported for STM32 boards only)
/*--------------------------------------------------------------------------------------*/
#if (defined(__STM32F1__) || defined(__STM32F4__))
#include "DMD_RGB.h"

// Moment of set CLK signal (0 - CLK immediately with DATA, 1 - CLK one step after DATA)
#define CLOCK_SEPARATE 0
#if CLOCK_SEPARATE == 1
#if defined (DIRECT_OUTPUT)
#define pew                    \
      *(this->datasetreg) = this->clk_clrmask;     \
      *(this->datasetreg) = *ptr++;                \
	  *(this->datasetreg) = this->clkmask;
#else
#define pew                    \
      *(this->datasetreg) = this->clk_clrmask;     \
      *(this->datasetreg) = this->expand[*ptr++];   \
	  *(this->datasetreg) = this->clkmask; 
#endif
#elif  CLOCK_SEPARATE == 0
#if defined (DIRECT_OUTPUT)
#define pew                    \
      *(this->datasetreg) = this->clk_clrmask;     \
      *(this->datasetreg) = *ptr++;
#else

#define pew                    \
      *(this->datasetreg) = this->clk_clrmask;     \
      *(this->datasetreg) = this->expand[*ptr++];   

#endif
#endif
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE, int COL_DEPTH>
class DMD_RGB_FM6126_BASE : public DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>
	{
	public:
		DMD_RGB_FM6126_BASE(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>
			(mux_list, _pin_nOE, _pin_SCLK, pinlist,
				panelsWide, panelsHigh, d_buf)
			{}

#if CLOCK_SEPARATE == 1
		void generate_rgbtable()  override { DMD_RGB_BASE::generate_rgbtable_default(CLK_AFTER_DATA); }

#elif  CLOCK_SEPARATE == 0

		void generate_rgbtable()  override { DMD_RGB_BASE::generate_rgbtable_default(CLK_WITH_DATA); }

#endif
		virtual void chip_init()  override {

			uint16_t b12a;
			//b12a = 0b0111111111111111;			 // from rpi lib
			//b12a = 0b0111100011111111;
			//b12a = 0b0000011111100000;			 // from ESP32-HUB75-MatrixPanel-I2S-DMA
			b12a = 0b1111111111000000;				 // from loganalyzer
			uint16_t b13a = 0b0000000001000000;

			*(this->oesetreg) = this->oemask;         // Disable LED output during row/plane switchover

			this->set_mux(1);				// A -> High
			*(this->latsetreg) = this->latmask << 16;					// LAT - LOW
			*(this->datasetreg) = this->clk_clrmask;			// off all rgb channels

			this->send_to_allRGB(b13a, 12);   // write 2nd config register
			delayMicroseconds(2);
			this->send_to_allRGB(b12a, 11);   // write 1st config register
			delayMicroseconds(2);
			this->send_to_allRGB(0, 3);      // send all 0's to all rgb

			//*muxclrreg = mux_clrmask;  
			this->set_mux(0);					// Clear all mux channels
			*(this->oesetreg) = this->oemask << 16;

			}

#if (defined(__STM32F1__) || defined(__STM32F4__))

		virtual void scan_dmd_p2() override {

			timer_set_count(this->MAIN_TIMER, 0);
			timer_set_count(this->OE_TIMER, 0);
			timer_generate_update(this->MAIN_TIMER);
			timer_generate_update(this->OE_TIMER);
			timer_resume(this->OE_TIMER);
			timer_resume(this->MAIN_TIMER);

			}
#endif


	};

template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE, int COL_DEPTH>
class DMD_RGB_FM6126 : public DMD_RGB_FM6126_BASE<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>
	{

	public:
		DMD_RGB_FM6126(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB_FM6126_BASE <MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>
			(mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
			{}

		virtual void scan_dmd_p3() override {

			// buffptr, being 'volatile' type, doesn't take well to optimization.
			// A local register copy can speed some things up:
			volatile uint8_t* ptr = this->buffptr;

			for (uint16_t uu = 0; uu < this->x_len - 8; uu += 8)
				{
				// Loop is unrolled for speed:
				pew pew pew pew pew pew pew pew
				}

			pew pew pew pew pew

				* (this->datasetreg) = this->clkmask << 16; // Set clock low
			*(this->latsetreg) = this->latmask; // Latch data loaded during *prior* interrupt

			pew pew pew

				* (this->datasetreg) = this->clkmask << 16; // Set clock low
			*(this->latsetreg) = this->latmask << 16;// Latch down
			*(this->datasetreg) = this->clk_clrmask;
			this->buffptr += this->displ_len;

			}

	};

//--------------------------------------------------------------------------------------
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE>
class DMD_RGB_FM6126 <MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COLOR_4BITS_Packed>
	: public DMD_RGB_FM6126_BASE<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COLOR_4BITS_Packed>
	{
	public:
		DMD_RGB_FM6126(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB_FM6126_BASE <MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COLOR_4BITS_Packed>
			(mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
			{}

		virtual void scan_dmd_p3() override {

			// buffptr, being 'volatile' type, doesn't take well to optimization.
			// A local register copy can speed some things up:
			volatile uint8_t* ptr = this->buffptr;

			if (this->plane > 0) {


				for (uint16_t uu = 0; uu < this->x_len - 8; uu += 8)
					{
					// Loop is unrolled for speed:
					pew pew pew pew pew pew pew pew
					}

				pew pew pew pew pew

					* (this->datasetreg) = this->clkmask << 16; // Set clock low
				*(this->latsetreg) = this->latmask; // Latch data loaded during *prior* interrupt

				pew pew pew
					* (this->datasetreg) = this->clkmask << 16; // Set clock low
				*(this->latsetreg) = this->latmask << 16;// Latch down
				this->buffptr += this->displ_len;
				}
			else { // 920 ticks from TCNT1=0 (above) to end of function

				for (int i = 0; i < this->x_len; i++) {
					byte b =
						((ptr[i] >> 2) & 0x30) |
						((ptr[i + this->displ_len] >> 4) & 0x0C) |
						((ptr[i + this->displ_len * 2] >> 6) & 0x03);

					*(this->datasetreg) = this->clk_clrmask; // Clear all data and clock bits together
					if (i == (this->x_len - 3)) *(this->latsetreg) = this->latmask;
					*(this->datasetreg) = this->expand[b];  // Set new data bits
					*(this->datasetreg) = this->clkmask;
					}
				*(this->datasetreg) = this->clkmask << 16;      // Set clock low
				*(this->latsetreg) = this->latmask << 16;// Latch down

				}

			}

	};

#undef pew
#endif
#endif