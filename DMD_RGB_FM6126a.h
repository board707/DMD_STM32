#pragma once
#ifndef DMD_RGB_FM6126_H
#define DMD_RGB_FM6126_H
/*--------------------------------------------------------------------------------------
 This file is a part of the DMD_STM32 library

 DMD_STM32.h  - STM32 port of DMD.h library

 https://github.com/board707/DMD_STM32
 Dmitry Dmitriev (c) 2019-2023
/--------------------------------------------------------------------------------------*/

// FM6126a/RUL6024 driver class

/*--------------------------------------------------------------------------------------*/
#include "DMD_RGB.h"

#if (defined(__STM32F1__) || defined(__STM32F4__))

// Option of set CLK signal (0 - CLK immediately with DATA, 1 - CLK one step after DATA)
#define CLOCK_SEPARATE 0
#if CLOCK_SEPARATE == 1
#if defined(DIRECT_OUTPUT)
#define pew                                  \
	*(this->datasetreg) = this->clk_clrmask; \
	*(this->datasetreg) = *ptr++;            \
	*(this->datasetreg) = this->clkmask;
#else
// Add narrowing the expand table index to 6 bits to reduce the table size in the future.
#define pew                                     \
	*(this->datasetreg) = this->clk_clrmask;    \
	*(this->datasetreg) = this->expand[(*ptr++) & 0x3F]; \
	*(this->datasetreg) = this->clkmask;
#endif
#elif CLOCK_SEPARATE == 0
#if defined(DIRECT_OUTPUT)
#define pew                                  \
	*(this->datasetreg) = this->clk_clrmask; \
	*(this->datasetreg) = *ptr++;
#else

#define pew                                  \
	*(this->datasetreg) = this->clk_clrmask; \
	*(this->datasetreg) = this->expand[(*ptr++) & 0x3F];

#endif
#endif
#endif


template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE, int COL_DEPTH>
class DMD_RGB_FM6126_BASE : public DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>
{
public:
	DMD_RGB_FM6126_BASE(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
						byte panelsWide, byte panelsHigh, bool d_buf = false) : DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>(mux_list, _pin_nOE, _pin_SCLK, pinlist,
																																				panelsWide, panelsHigh, d_buf)
	{}


	/* FM6126a config values (seems to be compatible with RUL6024 chip)*/

		// b12a = 0b0111111111111111;			 // from rpi lib
		// b12a = 0b0111100011111111;
		// b12a = 0b0000011111100000;			 // from ESP32-HUB75-MatrixPanel-I2S-DMA
		const uint16_t b12a = 0b1111111111000000; // from loganalyzer
		const uint16_t b13a = 0b0000000001000000;

#if (defined(__STM32F1__) || defined(__STM32F4__))

#if CLOCK_SEPARATE == 1
	void generate_rgbtable() override { DMD_RGB_BASE::generate_rgbtable_default(CLK_AFTER_DATA); }

	#elif CLOCK_SEPARATE == 0

	void generate_rgbtable() override { DMD_RGB_BASE::generate_rgbtable_default(CLK_WITH_DATA); }

#endif
/*-------------------------------------------------*/
	virtual void chip_init() override
	{

		*(this->oesetreg) = this->oemask; // Disable LED output during row/plane switchover

		this->Mux->set_mux(1);						  // A -> High
		*(this->latsetreg) = this->latmask << 16; // LAT - LOW
		*(this->datasetreg) = this->clk_clrmask;  // off all rgb channels

		this->send_to_allRGB(b13a, 12); // write 2nd config register
		delayMicroseconds(2);
		this->send_to_allRGB(b12a, 11); // write 1st config register
		delayMicroseconds(2);
		this->send_to_allRGB(0, 3); // send all 0's to all rgb

		this->Mux->set_mux(0); // Clear all mux channels
		*(this->oesetreg) = this->oemask << 16;
	}
/*-------------------------------------------------*/
	virtual void scan_dmd_p2() override
	{

		timer_set_count(this->MAIN_TIMER, 0);
		timer_set_count(this->OE_TIMER, 0);
		timer_oc_set_mode(this->OE_TIMER, this->oe_channel, (timer_oc_mode)this->OE_polarity, 0);
		timer_generate_update(this->MAIN_TIMER);
		timer_generate_update(this->OE_TIMER);
		timer_resume(this->OE_TIMER);
		timer_resume(this->MAIN_TIMER);
	}
#endif
/*--------------------------------------------------------------------------------------*/
#if (defined(ARDUINO_ARCH_RP2040))

	virtual void chip_init() override
	{

		pinMode(this->pin_DMD_nOE, OUTPUT);
		digitalWrite(this->pin_DMD_nOE, HIGH);  // Disable LED output during row/plane switchover
		
		// At that moment a generate_muxmask() method has already been completed and set_mux() is ready for use
		this->Mux->set_mux(1);	 // A -> High

		this->send_to_allRGB(b13a, 12); // write 2nd config register
		delayMicroseconds(2);
		this->send_to_allRGB(b12a, 11); // write 1st config register
		delayMicroseconds(2);
		this->send_to_allRGB(0, 3); // send all 0's to all rgb
		delayMicroseconds(2);
		
		this->Mux->set_mux(0);	 // Clear all mux channels
						 
		digitalWrite(this->pin_DMD_nOE, LOW);
	}
/*-------------------------------------------------*/
	virtual void pio_dma_init() override
	{
		// pio configs

		// try increase this in case of ghostings on the panel
		this->pio_clkdiv = this->pio_clkdiv + 1;

		// setup a PIO machine to output data to RGB pins
		this->sm_data = pio_claim_unused_sm(this->pio, true);
		this->data_prog_offs = pio_add_dmd_lat_program(this->pio);
		this->pio_config = dmd_lat_program_get_default_config(this->data_prog_offs);
		dmd_out_program_init(this->pio, this->sm_data, this->data_prog_offs, &(this->pio_config), this->pio_clkdiv,
							 this->data_pins[0], this->data_pins_cnt, this->pin_DMD_SCLK, this->pin_DMD_CLK);

		// DMA config
		this->dma_chan = dma_claim_unused_channel(true);
		dma_channel_config dma_c = dma_channel_get_default_config(this->dma_chan);
		channel_config_set_transfer_data_size(&dma_c, DMA_SIZE_8); // read by one byte
		channel_config_set_read_increment(&dma_c, true);  		 
		channel_config_set_dreq(&dma_c, this->sm_data + DREQ_PIO0_TX0); // requested by PIO
		channel_config_set_ring(&dma_c, false, 4);	// (1 << 4) = wrap data by 16 bytes to write a config registers repeatedly

		dma_channel_configure(
			this->dma_chan,
			&dma_c,
			&pio0_hw->txf[this->sm_data], // Write address (only need to set this once)
			NULL,						  // Don't provide a read address yet
			this->x_len,				  // Write x_len bytes than stop
			false						  // Don't start yet
		);

		chip_init();											// upload config values to the driver chips
		channel_config_set_ring(&dma_c, false, 0); 				// cancel wrapping data by 16 bytes
		dma_channel_set_config(this->dma_chan, &dma_c, false);  // reload DMA config after wrap change
	}
/*-------------------------------------------------*/	
	virtual void scan_dmd_p2() override
	{
		// RGB data transfer by PIO machine controlled by parameter below
		// Upper 16 bits is a number of LATCHES at the end of data (complement to 16)
		// Lower 16 bits is a number of 16 pixels blocks in a single transfer ( substract 2 )
		uint32_t control_par = ((uint32_t)(16 - 3) << 16) | ((this->x_len >> 4) - 2);
		
		// Wait to finishing of previous transfer
		dma_channel_wait_for_finish_blocking(this->dma_chan);
		dmd_out_program_reinit(this->pio, this->sm_data, this->data_prog_offs, &(this->pio_config));
		
		// Put a `control_par' parameter
		pio_sm_put_blocking(this->pio, this->sm_data, control_par);
		// Start DMA transfer from `buffptr` buffer
		dma_channel_set_read_addr(this->dma_chan, this->buffptr, true);

		// Restart MAIN and OE timers
		pwm_set_counter(this->MAIN_slice_num, 0);
		pwm_set_counter(this->OE_slice_num, 0);
		pwm_set_enabled(this->MAIN_slice_num, true);
		pwm_set_enabled(this->OE_slice_num, true);

		// increment a buffer pointer for the next transfer
		this->buffptr += this->displ_len;
	}
#endif
};

//--------------------------------------------------------------------------------------
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE, int COL_DEPTH>
class DMD_RGB_FM6126 : public DMD_RGB_FM6126_BASE<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>
{

public:
	DMD_RGB_FM6126(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
				   byte panelsWide, byte panelsHigh, bool d_buf = false) : DMD_RGB_FM6126_BASE<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>(mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
	{
	}
#if (defined(__STM32F1__) || defined(__STM32F4__))
	virtual void scan_dmd_p3() override
	{

		// buffptr, being 'volatile' type, doesn't take well to optimization.
		// A local register copy can speed some things up:
		volatile uint8_t *ptr = this->buffptr;

		for (uint16_t uu = 0; uu < this->x_len - 8; uu += 8)
		{
			// Loop is unrolled for speed:
			pew pew pew pew pew pew pew pew
		}

		pew pew pew pew pew

		*(this->datasetreg) = this->clkmask << 16; // Set clock low
		
		// Latch up on last 3 clocks
		*(this->latsetreg) = this->latmask;			   

		pew pew pew

		*(this->datasetreg) = this->clkmask << 16; // Set clock low
		*(this->latsetreg) = this->latmask << 16;	   // Latch down
		*(this->datasetreg) = this->clk_clrmask;
		this->buffptr += this->displ_len;
	}
#endif
#undef pew
};

//--------------------------------------------------------------------------------------
#if (defined(__STM32F1__) || defined(__STM32F4__))
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE>
class DMD_RGB_FM6126<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COLOR_4BITS_Packed>
	: public DMD_RGB_FM6126_BASE<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COLOR_4BITS_Packed>
{
public:
	DMD_RGB_FM6126(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
				   byte panelsWide, byte panelsHigh, bool d_buf = false) : DMD_RGB_FM6126_BASE<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COLOR_4BITS_Packed>(mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
	{
	}

	// Using of expand[] table is a default for Color_4Bits_Packed mode.
	// Add narrowing the table index to 6 bits to reduce the table size in the future.
	#if CLOCK_SEPARATE == 1
	#define pew                              \
		*(this->datasetreg) = this->clk_clrmask;    \
		*(this->datasetreg) = this->expand[(*ptr++) & 0x3F]; \
		*(this->datasetreg) = this->clkmask;
	
	#elif CLOCK_SEPARATE == 0
	#define pew                            \
		*(this->datasetreg) = this->clk_clrmask; \
		*(this->datasetreg) = this->expand[(*ptr++) & 0x3F];
	
	#endif
	

	virtual void scan_dmd_p3() override
	{

		// buffptr, being 'volatile' type, doesn't take well to optimization.
		// A local register copy can speed some things up:
		volatile uint8_t *ptr = this->buffptr;

		if (this->plane > 0)
		{

			for (uint16_t uu = 0; uu < this->x_len - 8; uu += 8)
			{
				// Loop is unrolled for speed:
				pew pew pew pew pew pew pew pew
			}

			pew pew pew pew pew

			*(this->datasetreg) = this->clkmask << 16; // Set clock low
			
			// Latch up on last 3 clocks
			*(this->latsetreg) = this->latmask;			

			pew pew pew
			
			*(this->datasetreg) = this->clkmask << 16; 	// Set clock low
			*(this->latsetreg) = this->latmask << 16;	// Latch down
			this->buffptr += this->displ_len;
		}
		else
		{ // 920 ticks from TCNT1=0 (above) to end of function

			for (int i = 0; i < this->x_len; i++)
			{
				byte b =
					((ptr[i] >> 2) & 0x30) |
					((ptr[i + this->displ_len] >> 4) & 0x0C) |
					((ptr[i + this->displ_len * 2] >> 6) & 0x03);

				*(this->datasetreg) = this->clk_clrmask; // Clear all data and clock bits together
				
				// Latch up on last 3 clocks
				if (i == (this->x_len - 3)) {
					*(this->latsetreg) = this->latmask;
				}
					
				*(this->datasetreg) = this->expand[b]; // Set new data bits
				*(this->datasetreg) = this->clkmask;
			}
			*(this->datasetreg) = this->clkmask << 16; // Set clock low
			*(this->latsetreg) = this->latmask << 16;  // Latch down
		}
	}
};

#undef pew
#endif
#endif