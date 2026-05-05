#pragma once

#ifndef DMD_RGB_SPWM_DRIVER_H
#define DMD_RGB_SPWM_DRIVER_H
/*--------------------------------------------------------------------------------------
 This file is a part of the DMD_STM32 library.

 DMD_STM32  - STM32 port of DMD.h library

 This module is an attempt to provide an experimental support
 of the new generation HUB75 LED panel drivers - so-called PWM/SPWM type.

 The file includes a three base classes for three groups of drivers -
 which can be roughly systematized by the indices of the FM63xx drivers -
 the first type is compatible with FM6353, the second - FM6363, the
 third - FM6373.

The chips supported:
	* FM6353 type
		+ FM6353
		+ ICN2153

	* FM6363 type
		+ FM6363

	* FM6373 type
		+ FM6373
		+ ICN2055
		+ ICN1065
		+ DP3264
		+ SM16380SH


 https://github.com/board707/DMD_STM32
 Dmitry Dmitriev (c) 2019-2025

 (for STM32 boards only)
/--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------*/
#if (defined(__STM32F1__) || defined(__STM32F4__))

#define CLOCK_SETTINGS  CLK_AFTER_DATA   // options: CLK_WITH_DATA / CLK_AFTER_DATA

#if defined(__STM32F1__)
#define DUAL_CLK_PULSE  false           // options: true / false
#elif defined(__STM32F4__)
#define DUAL_CLK_PULSE  true            // options: true / false
#endif


#include "DMD_RGB.h"

#if (CLOCK_SETTINGS  == CLK_WITH_DATA)
#define pew_6353_2(x)          \
	*(this->datasetreg) = (x); \
	*(this->datasetreg) = this->clk_clrmask;

#define pew_6353_4(x)                        \
	*(this->datasetreg) = (x);               \
	*(this->datasetreg) = (x);               \
	*(this->datasetreg) = this->clk_clrmask; \
	*(this->datasetreg) = this->clk_clrmask;

#else   // CLK_AFTER_DATA

#define pew_6353_2(x)          \
	*(this->datasetreg) = (x); \
	*(this->datasetreg) = this->clkmask; \
	*(this->datasetreg) = this->clk_clrmask;

#define pew_6353_4(x)                        \
	*(this->datasetreg) = (x);               \
	*(this->datasetreg) = this->clkmask;     \
	*(this->datasetreg) = this->clkmask;	 \
	*(this->datasetreg) = this->clk_clrmask;
#endif

#if (DUAL_CLK_PULSE)
#define pew_SPWM(x) pew_6353_4(x)
#else
#define pew_SPWM(x) pew_6353_2(x) 
#endif

#define ADD_CONFIG_REGS(arr) this->add_config_regs((arr), sizeof(arr) / sizeof((arr)[0]))

/*--------------------------------------------------------------------------------------*/
/*
 * Base class for all SPWM drivers  ( specialized as ICN2153 / FM6353 type)
 *
 * Key features: The clock source for the internal driver PWM is the GCLK (OE) signal.
 * 		Row switching is synchronized based on a specified number of GCLK pulses (138 for FM6353 ).
 *		The CLK is used only with SDI when loading data and is not synchronized with the PWM generation.
 */
/*--------------------------------------------------------------------------------------*/
template <int... Pars>
class DMD_RGB_SPWM_DRIVER_BASE : public DMD_RGB<Pars...>
{
public:
	DMD_RGB_SPWM_DRIVER_BASE(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
							 byte panelsWide, byte panelsHigh, bool d_buf = false) : 
							 DMD_RGB<Pars...>
							 (mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, false)
	{
	}

	~DMD_RGB_SPWM_DRIVER_BASE()
	{
		if (this->config_registers != NULL)
		{
			free(this->config_registers);
		}
	}

	virtual void init(uint16_t scan_interval = 200) override
	{
		this->oe_scan_flag = false;
		DMD_RGB_BASE::init(scan_interval);
		pinMode(this->pin_DMD_nOE, PWM);
	}

	// load user data buffer to matrix
	void swapBuffers(boolean copy) override
	{

		this->refresh_greyscale_data();
	}
	
	uint8_t shiftColorBrightnessDown(uint8_t shift) {
		if (shift > this->gclk_bits - min_gclk) {
			dimming_factor = this->gclk_bits - min_gclk;
		}
		else dimming_factor = shift;
		return dimming_factor;
	}

protected:
	volatile bool oe_scan_flag = false;
	volatile bool oe_scan_res = false;

	 // Most driver chips only receives the lower 14 bits of 16 bits transmitted data.
	// Some drivers needs 13 bits.
	uint8_t gclk_bits = 14;
	uint8_t dimming_factor = 0;
	const uint8_t min_gclk = 8;


	uint8_t TIM3_PERIOD, GCLK_NUM, ADD_NUM;

	uint16_t *config_registers;
	uint8_t conf_reg_cnt;

	

	uint32_t MAIN_TIMER_reload, MAIN_TIMER_cc1, MAIN_TIMER_cc2;
	uint32_t OE_TIMER_reload, OE_TIMER_cc;

	void generate_rgbtable() override { DMD_RGB_BASE::generate_rgbtable_default(CLOCK_SETTINGS); }

	

	// placeholder for color mode specialization
	virtual uint16_t expand_planes(volatile uint8_t *ptr3) = 0;

	void add_config_regs(uint16_t *cfg_regs, uint16_t regs_cnt)
	{

		if (this->config_registers != NULL)
		{
			free(this->config_registers);
		}
		this->conf_reg_cnt = regs_cnt;
		this->config_registers = (uint16_t *)malloc(this->conf_reg_cnt * sizeof(uint16_t));
		memcpy(this->config_registers, cfg_regs, (this->conf_reg_cnt * sizeof(uint16_t)));
	}

	// Hold LAT line HIGH for given number of CLK pulses
	void send_latches(uint16_t latches)
	{
		*(this->datasetreg) = this->clk_clrmask; // off all rgb channels
		*(this->latsetreg) = this->latmask;		 // switch LE ON
		while (latches)
		{
			*(this->datasetreg) = this->clkmask;
			*(this->datasetreg) = this->clkmask << 16;
			latches--;
		}
		*(this->latsetreg) = this->latmask << 16; // LAT - LOW
	}

	// Just send a given number of CLK pulses
	void send_clocks(uint16_t clocks)
	{
		*(this->datasetreg) = this->clk_clrmask; // off all rgb channels

		while (clocks)
		{
			*(this->datasetreg) = this->clkmask;
			*(this->datasetreg) = this->clkmask << 16;
			clocks--;
		}
	}

	// Timer config:
	// • GCLK pulse packets are generated by the PWM‑1 mode of OE_TIMER on its output pin.
	// • To guarantee an exact number of GCLK pulses per packet, OE_TIMER counting is
	//   controlled by the high level of MAIN_TIMER CH1 (master mode).
	// • Line switching is handled by the MAIN_TIMER CH2 compare‑match interrupt.
	void initialize_timers(voidFuncPtr handler) override
	{

		timer_init(this->MAIN_TIMER);
		timer_pause(this->MAIN_TIMER);
		timer_set_prescaler(this->MAIN_TIMER, 0);
		(this->MAIN_TIMER->regs).gen->SMCR = TIMER_SMCR_MSM; // Master mode

		timer_set_reload(this->MAIN_TIMER, MAIN_TIMER_reload);
		(this->MAIN_TIMER->regs).gen->CR2 = TIMER_CR2_MMS_COMPARE_OC1REF; // Master/slave : use CC1 as trigger output
		timer_set_compare(this->MAIN_TIMER, 1, MAIN_TIMER_cc1);			  // CH1: control OE_TIMER counting
		timer_oc_set_mode(this->MAIN_TIMER, 1, TIMER_OC_MODE_PWM_1, 0);	  // set output active before CC match
		timer_set_compare(this->MAIN_TIMER, 2, MAIN_TIMER_cc2);			  // CH2: line switching interrupt

		// Not use DMA because in STM32F4 MCU only DMA2 has access to GPIOs
		timer_attach_interrupt(this->MAIN_TIMER, TIMER_CC2_INTERRUPT, handler);

		timer_init(this->OE_TIMER);
		timer_pause(this->OE_TIMER);
		timer_set_prescaler(this->OE_TIMER, 0);

		// connect slave OE_TIMER to Master
#if defined(ALTERNATIVE_DMD_TIMERS)
		(this->OE_TIMER->regs).gen->SMCR = TIMER_SMCR_TS_ITR2 | TIMER_SMCR_SMS_GATED;
#else
		(this->OE_TIMER->regs).gen->SMCR = TIMER_SMCR_TS_ITR3 | TIMER_SMCR_SMS_GATED;
#endif
		// OE_TIMER setup
		timer_oc_set_mode(this->OE_TIMER, this->oe_channel, TIMER_OC_MODE_PWM_1, 0); // set output active before CC match
		timer_set_reload(this->OE_TIMER, OE_TIMER_reload);
		timer_cc_enable(this->OE_TIMER, this->oe_channel);	   // PWM enable
		timer_cc_set_pol(this->OE_TIMER, this->oe_channel, 1); // set PWM output active LOW
		timer_set_compare(this->OE_TIMER, this->oe_channel, OE_TIMER_cc);
	}

	// VSYNC = 3 clocks LAT pulse
	virtual void send_vsync()
	{
		*(this->datasetreg) = this->clk_clrmask;
		*(this->datasetreg) = this->clkmask;
		this->send_latches(3);
	}

	// initialization pulse train
	virtual void load_config_regs(uint16_t *conf_reg)
	{

		this->send_latches(14); // pre-active command, 14 clks LAT pulse
		this->send_latches(12); // enable all output, 12 clks LAT
		this->send_vsync();		// vsync, 3 clks LAT
		for (uint8_t r = 0; r < conf_reg_cnt; r++)
		{
			delayMicroseconds(1);
			this->send_latches(14);						  // pre-active command
			this->send_to_allRGB(conf_reg[r], r * 2 + 2); // send config registers
		}
	}

	// Interrupt handler
	// • Fired by MAIN_TIMER CH2 compare match
	// • Used to select the row and increment current row number
	// • In case of new data available for upload - waits until 0th row and
	//   then stops the GCLK generation.
	//
	// Flags: set <oe_scan_flag == false> to stop GCLK
	// 		Result: <oe_scan_res> became false when the GCLK is stopped.
	void scan_dmd() override
	{

		this->Mux->set_mux(this->row);
        timer_set_count(this->OE_TIMER, 0); // synchronize OE timer with MAIN timer on next start
		if (this->row == 0)
		{
			if (this->oe_scan_flag == false)
			{
				// switch off master timer trigger
				// and disable GCLK generation
				timer_set_compare(this->MAIN_TIMER, 1, 0); // OE generator off
				this->oe_scan_res = false;
				return;
			}
		}
		
		this->row++;
		if (this->row >= this->nRows)
			this->row = 0;
	}

	// Stop GCLK generation
	// Set the <oe_scan_flag> to false and wait the interrupt stops timers
	// and changes <oe_scan_res> to false.
	virtual void stop_GCLK()
	{
		// if timer is running
		if (this->oe_scan_flag)
		{
			noInterrupts();
			// set stopping GCLK (OE) flag
			this->oe_scan_flag = false;
			this->oe_scan_res = true;

			interrupts();
			// wait for GCLK stop flag change
			while (this->oe_scan_res)
			{
			};
			delayMicroseconds(5);
		}

		timer_pause(this->MAIN_TIMER);

		// switch to row 0
		this->row = 0;
		this->Mux->set_mux(this->row);
		this->row++;
		delayMicroseconds(10);
		this->oe_scan_flag = true;
	}

	// Restart GCLK generation
	virtual void start_GCLK()
	{

		timer_pause(this->OE_TIMER);
		timer_set_compare(this->MAIN_TIMER, 1, this->MAIN_TIMER_cc1);

		timer_set_count(this->MAIN_TIMER, 0);
		timer_set_count(this->OE_TIMER, 0);
		timer_resume(this->OE_TIMER);
		timer_resume(this->MAIN_TIMER);
	}

	// Load new greyscale data
	// Driver expext 16 bits per pixel = 14 bits grayscale + 2 dummy bits
	// Since the library used only 4 bits per color, we load them to MSB driver bits
	// and filled the others by our data LSB bit
	virtual void data_transfer()
	{
		this->buffptr = this->matrixbuff[1 - this->backindex];
		volatile uint8_t *ptr = this->buffptr;
		volatile uint8_t *ptr2 = this->buffptr;
		const uint8_t num_sect = this->x_len / 16;
		// iterate each scan line
		for (uint8_t y = 0; y < this->nRows; y++)
		{
			// data pointer to next scan line data
			ptr = this->buffptr + y * (this->x_len);

			// each driver controls 16 leds
			// so the data should be loaded by 16 pixels

			for (uint8_t x = 0; x < 16; x++)
			{

				ptr2 = ptr + x;

				for (uint8_t sect = 0; sect < num_sect; sect++)
				{
					// Load 16 greyscale bits for each pixel MSB first
					// 14,13 or 12 bits are used by driver, 
					// 2 - 4 MSB bits MUST be leave empty

					// 12 MSB bits are loaded from buffer
					// 0{2}-data{4}-data_lsb{2}  (for 14bit frame)
					uint16_t b = this->expand_planes(ptr2);

					// unused lower bits are filled by zeros
					
					// on STM32F1 unroll the loop for speed
					pew_SPWM(b) pew_SPWM(b) pew_SPWM(b)
					
					// The last bit in serie must latched
					if (sect < num_sect - 1)
					{
						pew_SPWM(b)
						ptr2 += 16;
					}
					else
					{
						*(this->latsetreg) = this->latmask;			// LAT - HIGH
						pew_SPWM(b)
						* (this->latsetreg) = this->latmask << 16;   // LAT - LOW
					}
				}
			}
		}
	}

	// the main greyscale upload function
	virtual void refresh_greyscale_data()
	{
		// wait for 0-th row and stop the timers
		this->stop_GCLK();
		// clear all RGB & CLK lines
		*(this->datasetreg) = this->clk_clrmask;
		delayMicroseconds(2);
		// load config registers
		this->load_config_regs(config_registers);
		// restart the timers
		this->start_GCLK();
		// load new grayscale data
		this->data_transfer();
	}
};
/*--------------------------------------------------------------------------------------*/
// Virtual methods to read color pixel data from internal buffer and send it to the panel
/*--------------------------------------------------------------------------------------*/
// Color template for COLOR_1BIT and COLOR_4BITS modes
/*--------------------------------------------------------------------------------------*/
template <int... Pars>
class DMD_RGB_SPWM_DRIVER : public DMD_RGB_SPWM_DRIVER_BASE<Pars...>
{
public:
	DMD_RGB_SPWM_DRIVER(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
						byte panelsWide, byte panelsHigh, bool d_buf = false)
	       : DMD_RGB_SPWM_DRIVER_BASE<Pars...>
			   (mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
	{
	}

protected:
    // Extract color bits from bitplanes buffer
	// and fill 12 MSB grayscale bits  
	uint16_t expand_planes(volatile uint8_t *ptr3) override
	{
		uint16_t b = 0;
		uint8_t bit_ptr = 16;
		uint8_t bits[4] = {0};
		// The postion of greyscale MSB can varied from 14 to 12th depending of chip
		// You can additionally shift it down as low as 8th bit by <dimming_factor>
		// to adjust color and brightness
		uint8_t gclk_msb = this->gclk_bits - this->dimming_factor;

		// Zerofill upper bits above greyscale MSB (14-12th ) 
		while (bit_ptr != gclk_msb)
		{
			pew_SPWM(b)
			bit_ptr--;
		}
		// Exctract pixel data from bitplanes buffer
        // Since the bitplanes are stored from LSB to MSB, we first read them into the array
		int8_t i = 0;
		for (i = 0; i < this->nPlanes; i++)
		{
		    bits[i] = *ptr3;
			ptr3 += this->displ_len;
		}
        
		// and than load it in reverse order - MSB to LSB
		i = this->nPlanes;
		do 
		{
			b = this->expand[bits[i-1]];
			pew_SPWM(b)
			bit_ptr--;
			i--;
		} 
		while (i > 0);
		
		// zerofill the remaining bits to make a total of 12
		b = 0;
		while (bit_ptr != (this-> min_gclk - 4 ))
		{
			pew_SPWM(b)
			bit_ptr--;
		}
		return b;
	}
};
/*--------------------------------------------------------------------------------------*/
// Color templates for COLOR_4BITS_Packed mode
//
// Extended pattern
/*--------------------------------------------------------------------------------------*/
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE, int Pixbase, int Pattern>
class DMD_RGB_SPWM_DRIVER<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, Pixbase, Pattern, COLOR_4BITS_Packed> : 
public DMD_RGB_SPWM_DRIVER_BASE<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, Pixbase, Pattern, COLOR_4BITS_Packed>
{
public:
	DMD_RGB_SPWM_DRIVER(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
						byte panelsWide, byte panelsHigh, bool d_buf = false) : 
				DMD_RGB_SPWM_DRIVER_BASE<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, Pixbase, Pattern, COLOR_4BITS_Packed>
				(mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)

	{
	}

protected:
 	// Extract color bits from bitplanes buffer
	// and fill 12 MSB grayscale bits  
	uint16_t expand_planes(volatile uint8_t *ptr2) override
	{

		uint16_t factor_l = this->displ_len;
		

		// The postion of greyscale MSB can varied from 14 to 12th depending of chip
		// You can additionally shift it down as low as 8th bit by <dimming_factor>
		// to adjust color and brightness
		uint8_t gclk_msb = this->gclk_bits - this->dimming_factor;

		// Exctract pixel data from bitplanes buffer
		// bitplanes 1 - 3
		uint16_t b1 = this->expand[*ptr2]; 
		uint16_t b2 = this->expand[*(ptr2 + factor_l)];
		uint16_t b3 = this->expand[*(ptr2 + factor_l * 2)];
		byte b0 =		// plane 0
			(((*ptr2) >> 2) & 0x30) |
			((*(ptr2 + factor_l)) & 0x0C) |
			(((*(ptr2 + factor_l * 2)) >> 6) & 0x03);
		uint16_t b = this->expand[b0];
		uint8_t bit_ptr = 16;
		
		// Zerofill upper bits above greyscale MSB (14-12th ) 
		while (bit_ptr != gclk_msb)
		{
			pew_SPWM(0)
			bit_ptr--;
		}

		// load 4 color bits
        bit_ptr-=4;
		pew_SPWM(b3) pew_SPWM(b2) pew_SPWM(b1) pew_SPWM(b)
		
		// zerofill the remaining bits to make a total of 12
		b = 0;
		while (bit_ptr != (this-> min_gclk - 4 ))
		{
			pew_SPWM(b)
			bit_ptr--;
		}
		return b;
	}
};
/*--------------------------------------------------------------------------------------*/
// Color templates for COLOR_4BITS_Packed mode
//
// Standard pattern
/*--------------------------------------------------------------------------------------*/
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE>
class DMD_RGB_SPWM_DRIVER<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COLOR_4BITS_Packed> : 
public DMD_RGB_SPWM_DRIVER_BASE<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COLOR_4BITS_Packed>
{
public:
	DMD_RGB_SPWM_DRIVER(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
						byte panelsWide, byte panelsHigh, bool d_buf = false) : 
				DMD_RGB_SPWM_DRIVER_BASE<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COLOR_4BITS_Packed>
				(mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)

	{
	}

protected:
 	// Extract color bits from bitplanes buffer
	// and fill 12 MSB grayscale bits  
	uint16_t expand_planes(volatile uint8_t *ptr2) override
	{

		uint16_t factor_l = this->displ_len;
		

		// The postion of greyscale MSB can varied from 14 to 12th depending of chip
		// You can additionally shift it down as low as 8th bit by <dimming_factor>
		// to adjust color and brightness
		uint8_t gclk_msb = this->gclk_bits - this->dimming_factor;

		// Exctract pixel data from bitplanes buffer
		// bitplanes 1 - 3
		uint16_t b1 = this->expand[*ptr2]; 
		uint16_t b2 = this->expand[*(ptr2 + factor_l)];
		uint16_t b3 = this->expand[*(ptr2 + factor_l * 2)];
		byte b0 =		// plane 0
			(((*ptr2) >> 2) & 0x30) |
			((*(ptr2 + factor_l)) & 0x0C) |
			(((*(ptr2 + factor_l * 2)) >> 6) & 0x03);
		uint16_t b = this->expand[b0];
		uint8_t bit_ptr = 16;
		
		// Zerofill upper bits above greyscale MSB (14-12th ) 
		while (bit_ptr != gclk_msb)
		{
			pew_SPWM(0)
			bit_ptr--;
		}

		// load 4 color bits
        bit_ptr-=4;
		pew_SPWM(b3) pew_SPWM(b2) pew_SPWM(b1) pew_SPWM(b)
		
		// zerofill the remaining bits to make a total of 12
		b = 0;
		while (bit_ptr != (this-> min_gclk - 4 ))
		{
			pew_SPWM(b)
			bit_ptr--;
		}
		return b;
	}
};

/*--------------------------------------------------------------------------------------*/
/*
 * Base class for FM6363 driver type
 *
 * As in the 6353, row switching is synchronized by the specified number of GCLK pulses (74 for 6363).
 * However, in contrast with 6353 the PWM generation is controlled by a constantly
 * generated CLK pulses.
 * Therefore, this driver requires using a third timer to generate the clock.
 */
/*--------------------------------------------------------------------------------------*/

template <int... Pars>
class DMD_RGB_FM6363_BASE : public DMD_RGB_SPWM_DRIVER<Pars...>
{
public:
	DMD_RGB_FM6363_BASE(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
						byte panelsWide, byte panelsHigh, bool d_buf = false) : 
						DMD_RGB_SPWM_DRIVER<Pars...>
						(mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, false)

	{
	}

	void init(uint16_t scan_interval = 200) override
	{
		// generate levels for CLK DMA table
		this->dclk_strobe[0] = this->clkmask;		  // CLK high
		this->dclk_strobe[1] = (this->clkmask) << 16; // CLK low

		DMD_RGB_SPWM_DRIVER<Pars...>::init(scan_interval);
	}

protected:
	// CLK levels table for DMA (see "Timer setup" below)
	uint32_t dclk_strobe[2] = {0};
	uint8_t CLK_PERIOD;
	// uint32_t CLK_TIMER_reload, CLK_TIMER_cc;

#if defined(__STM32F1__)
	timer_dev *CLK_TIMER = TIMER2;
	dma_dev *rgbDmaDev = DMA1;
	dma_channel DmaClkChannel = DMA_CH1;

#elif defined(__STM32F4__)
	const timer_dev *CLK_TIMER = TIMER1;
	const dma_dev *rgbDmaDev = DMA2;

	dma_channel DmaClkChannel = DMA_CH6;
	dma_stream ClkDmaStream = DMA_STREAM6; // TIM1 CH3 */

#endif

	// Timer setup :
	// In addition to initialize_timers() in parent class we have to add continuous CLK generation.
	// For this, we use a CLK_TIMER. The timer is configured to fire a DMA request on CLK_TIMER CH3
	// to cyclically change the level of the CLK pin. Using a DMA allows you to use any pin, even one
	// not associated with a timer outputs.
	//
	// Note that on STM32F4 only Timer1 can be used for DMA memory to gpio transfer
	virtual void initialize_timers(voidFuncPtr handler) override
	{

		DMD_RGB_SPWM_DRIVER<Pars...>::initialize_timers(handler);

		timer_init(this->CLK_TIMER);
		timer_pause(this->CLK_TIMER);
		timer_set_prescaler(this->CLK_TIMER, 0);

		timer_dma_enable_req(this->CLK_TIMER, 3); 					// CH3 DMA request enable
		timer_set_reload(this->CLK_TIMER, this->CLK_PERIOD - 1);
		timer_set_compare(this->CLK_TIMER, 3, this->CLK_PERIOD / 2); // toogle CLK once in period

		// DMA setup:
		// transfer a single uint32_t value from CLK level table to datasetreg register
		// loops by 2 memory addresses
#if defined(__STM32F1__)
		dma_init(this->rgbDmaDev);
		dma_setup_transfer(this->rgbDmaDev, this->DmaClkChannel, (uint32_t *)(this->datasetreg), DMA_SIZE_32BITS, (uint32_t *)this->dclk_strobe, DMA_SIZE_32BITS, (DMA_MINC_MODE | DMA_CIRC_MODE | DMA_FROM_MEM));
		dma_set_num_transfers(this->rgbDmaDev, this->DmaClkChannel, 2);
		dma_enable(this->rgbDmaDev, this->DmaClkChannel);

#elif defined(__STM32F4__)
		dma_init(rgbDmaDev);
		dma_disable(this->rgbDmaDev, this->ClkDmaStream);
		dma_clear_isr_bits(this->rgbDmaDev, this->ClkDmaStream);
		dma_setup_transfer(this->rgbDmaDev, this->ClkDmaStream, this->DmaClkChannel, DMA_SIZE_32BITS, (uint32_t *)(this->datasetreg), (uint32_t *)this->dclk_strobe, NULL, (DMA_CIRC_MODE | DMA_MINC_MODE | DMA_FROM_MEM));
		dma_set_num_transfers(this->rgbDmaDev, this->ClkDmaStream, 2);
		dma_enable(this->rgbDmaDev, this->ClkDmaStream);

#endif
	}

	// (re)start CLK_TIMER
	virtual void start_DCLK()
	{
		timer_set_count(this->CLK_TIMER, 0);
		timer_resume(this->CLK_TIMER);
	}

	// override the main greyscale upload function
	virtual void refresh_greyscale_data() override
	{

		// wait for 0-th row and stop the OE & MAIN timers
		this->stop_GCLK();

		// stop the CLK and disable DMA
		timer_pause(this->CLK_TIMER);
#if defined(__STM32F1__)
		dma_disable(this->rgbDmaDev, this->DmaClkChannel);
#elif defined(__STM32F4__)
		dma_disable(this->rgbDmaDev, this->ClkDmaStream);
#endif

		// clear all RGB & CLK lines
		*(this->datasetreg) = this->clk_clrmask;
		delayMicroseconds(2);

		// load config registers
		this->load_config_regs(this->config_registers);

		// restart the MAIN & OE timers
		this->start_GCLK();
		// load new grayscale data
		this->data_transfer();

		// reenable DMA and start the CLK
#if defined(__STM32F1__)
		dma_enable(this->rgbDmaDev, this->DmaClkChannel);
#elif defined(__STM32F4__)
		dma_enable(this->rgbDmaDev, this->ClkDmaStream);
#endif
		this->start_DCLK();
	}

	void stop_GCLK() override
	{
		// if timer is running
		if (this->oe_scan_flag)
		{
			noInterrupts();
			// set stopping GCLK (OE) flag
			this->oe_scan_flag = false;
			this->oe_scan_res = true;

			interrupts();
			// wait for GCLK stop flag change
			while (this->oe_scan_res)
			{
			};
			//delayMicroseconds(5);
		}

		timer_pause(this->MAIN_TIMER);
		timer_pause(this->CLK_TIMER);
        // clear all RGB & CLK lines
		*(this->datasetreg) = this->clk_clrmask;
		// switch to row 0
		this->row = 0;
		this->Mux->set_mux(this->row);
		this->row++;
		delayMicroseconds(10);
		this->oe_scan_flag = true;
	}
};

/*--------------------------------------------------------------------------------------*/
/*
 * Base class for DP3264 driver type
 *
 * In this driver type, the PWM pulse source and the row switching are separated.
 * The PWM is uses a CLK, and the minimum number of pulses must be generated for each row
 * specified by the configuration registers.
 * Row switching signal for driver is generated by a single OE pulse.
 * Hardware row switching is achieved by selecting ABCDE lines in interrupt routine.
 * While using a CLK signal during the data loading, it is necessary to supply an OE pulses and
 * switch the rows accordingly to avoid image flickering.
 * So we need to rewrite of the <data_transfer> method.
 */
/*--------------------------------------------------------------------------------------*/
template <int... Pars>
class DMD_RGB_DP3264_BASE : public DMD_RGB_FM6363_BASE<Pars...>
{

public:
	DMD_RGB_DP3264_BASE(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
						byte panelsWide, byte panelsHigh, bool d_buf = false) : 
						DMD_RGB_FM6363_BASE<Pars...>
						(mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
	{
	}

	void init(uint16_t scan_interval = 200) override
	{

		DMD_RGB_FM6363_BASE<Pars...>::init(scan_interval);
	}

protected:

    virtual void spwm_chip_init() 
	{
		 this->clearScreen(true);
         for (uint8_t i = 0; i < this->conf_reg_cnt; i++) 
		 { 
			this->refresh_greyscale_data();
			delay(30);
		}
	}
	// part of greyscale loading process  -  restart GCLK generation
	void start_GCLK() override
	{
		timer_pause(this->OE_TIMER);
		timer_generate_update(this->MAIN_TIMER);
		timer_generate_update(this->OE_TIMER);
		//timer_set_count(this->MAIN_TIMER, this->MAIN_TIMER_reload - 2); // set counter just before update to be sure CC1 output is inactive
		timer_set_count(this->MAIN_TIMER, this->MAIN_TIMER_cc1+ 2); // set counter just after CC1 to start first loop right after 12x CLK OE pulse
		timer_set_compare(this->MAIN_TIMER, 1, this->MAIN_TIMER_cc1);	// restore OC1 compare value
	}

	// restart all timers
	void start_DCLK() override
	{
		pinMode(this->pin_DMD_nOE, PWM);
		timer_set_count(this->CLK_TIMER, 0);
		timer_resume(this->OE_TIMER);	// enable OE timer (waiting for MAIN_TIMER)
		timer_resume(this->MAIN_TIMER); // start MAIN_TIMER

		timer_resume(this->CLK_TIMER);
	}

	// Load new greyscale data
	// Driver expext 16 bits per pixel = 12-14 bits grayscale + 2-4 dummy bits
	// Since the library used only 4 bits per color, we load them to 4 MSB driver bits
	// and filled the others by copy of our data LSB bit
	//
	// In order not to interrupt the PWM generation during data loading, an OE pulse
	// is sent every 128 clocks and the panel row is switched.
	void data_transfer() override
	{
		this->buffptr = this->matrixbuff[1 - this->backindex];
		volatile uint8_t *ptr = this->buffptr;
		volatile uint8_t *ptr2 = this->buffptr;

		// each driver controls 16 leds
		// calculate a number of chips in one row
		const uint8_t num_sect = this->x_len / 16;
		

		pinMode(this->pin_DMD_nOE, OUTPUT);

		// generate 12 clocks OE pulse to start the data group (see the datasheet)
		*(this->oesetreg) = this->oemask;
		this->send_clocks(12);
		*(this->oesetreg) = this->oemask << 16;
		
		uint16_t clk_count = 16;
		//  iterate each scan line
		for (uint8_t y = 0; y < this->nRows; y++)
		{
			// data pointer to next scan line data
			ptr = this->buffptr + y * (this->x_len);

			// each driver controls 16 leds
			// so the data should be loaded by 16 pixels

			for (uint8_t x = 0; x < 16; x++)
			{

				ptr2 = ptr + x;

				// loop each driver in the row
				for (uint8_t sect = 0; sect < num_sect; sect++)
				{
					

					// switch the row at 112 clocks
					if (clk_count == 112)
					{
						this->Mux->set_mux(this->row);
						this->row++;
						if (this->row >= this->nRows)
							this->row = 0;
					}

					// Load 16 greyscale bits for each pixel MSB first
					// 14,13 or 12 bits are used by driver, 
					// 2 - 4 MSB bits MUST be leave empty

					// 4 of 12 MSB bits are loaded from buffer
					// the others filled by zero
					// 0{2..4}-data{4}-0{up to 12}  (for 14bit frame)
					uint16_t b = this->expand_planes(ptr2);

					

					// switch OE on to generate 4 clocks OE pulse every 128 clocks
					if (clk_count == 128)
					{
						*(this->oesetreg) = this->oemask;
					}

					pew_SPWM(b) pew_SPWM(b) pew_SPWM(b)

					// The last bit in serie must latched
					if (sect < num_sect - 1)
					{
						pew_SPWM(b)
						ptr2 += 16;
					}
					else
					{
						*(this->latsetreg) = this->latmask;			// LAT - HIGH
						pew_SPWM(b)
						* (this->latsetreg) = this->latmask << 16; // LAT - LOW
					}
                    
					// switch OE off finishing generating 4 clocks OE pulse
					if (clk_count == 128)
					{

						*(this->oesetreg) = this->oemask << 16;
						clk_count = 0;
					}
					 // yes, we increment clk counter just after clearing it
					 // it make it consistent to 128 bits loading process
						clk_count += 16;
					
					
				}
			}
		}
	}
};

/*--------------------------------------------------------------------------------------*/
// 					*** Driver-specific classes ***
// Chips included:
//	* FM6353 (compatible with ICN2153)
//	* FM6363
//	* DP3264
//	* ICN2055
//	* FM6373
//  * SM16380sh
/*--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------*/
// FM6353 driver class  (also compatible with ICN2153 chips)
/*--------------------------------------------------------------------------------------*/
template <int... Pars>
class DMD_RGB_FM6353 : public DMD_RGB_SPWM_DRIVER<Pars...>
{
public:
	DMD_RGB_FM6353(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
				   byte panelsWide, byte panelsHigh, bool d_buf = false) : 
				   DMD_RGB_SPWM_DRIVER<Pars...>
				   (mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, false)

	{
	}

	virtual void init(uint16_t scan_interval = 200) override
	{

		
		this->TIM3_PERIOD = 8;
		this->GCLK_NUM = 138; // GCLK pulses in packet, 6353 - 138, 6363 - 74
#if defined(__STM32F1__)
		this->ADD_NUM = 40; // Dummy timer ticks to finish the lines switching, can cause glitches if too short
#elif defined(__STM32F4__)
		this->ADD_NUM = 22;
#endif
        // MAIN loop duration = (GCLK_NUM) x OE pulses + additional delay (ADD_NUM) for line switching
		this->MAIN_TIMER_reload = this->GCLK_NUM * this->TIM3_PERIOD + 8 * this->ADD_NUM - 1;

		this->MAIN_TIMER_cc1 = this->GCLK_NUM * this->TIM3_PERIOD;	   // CH1: control OE_TIMER counting
		this->MAIN_TIMER_cc2 = this->GCLK_NUM * this->TIM3_PERIOD + 2; // CH2: line switching interrupt
		this->OE_TIMER_reload = this->TIM3_PERIOD - 1;
		this->OE_TIMER_cc = this->TIM3_PERIOD / 2;
		DMD_RGB_SPWM_DRIVER_BASE<Pars...>::init(scan_interval);

		uint16_t conf_6353[] = {0x0008, 0x1f70, 0x6707, 0x40f7, 0x0040};

		// Config value for 4 latches depends on number of scans
		conf_6353[1] = ((this->nRows - 1) << 8) | (conf_6353[1] & 0xFF);
		ADD_CONFIG_REGS(conf_6353);
	}
};
/*--------------------------------------------------------------------------------------*/
// FM6363 driver class
/*--------------------------------------------------------------------------------------*/
template <int... Pars>
class DMD_RGB_FM6363 : public DMD_RGB_FM6363_BASE<Pars...>
{

public:
	DMD_RGB_FM6363(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
				   byte panelsWide, byte panelsHigh, bool d_buf = false) : 
				   DMD_RGB_FM6363_BASE<Pars...>
				   (mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)

	{
	}

	virtual void init(uint16_t scan_interval = 200) override
	{
        // MSB greyscale position for color bits
		this->gclk_bits = 13;
		
		this->CLK_PERIOD = 8;
		this->TIM3_PERIOD = 8;
		this->GCLK_NUM = 74; // GCLK pulses in packet, 6353 - 138, 6363 - 74
#if defined(__STM32F1__)
		this->ADD_NUM = 32; // Dummy timer ticks to finish the lines switching, can cause glitches if too short
#elif defined(__STM32F4__)
		this->ADD_NUM = 32;
#endif
		 // MAIN loop duration = (GCLK_NUM) x OE pulses + additional delay (ADD_NUM) for line switching
		this->MAIN_TIMER_reload = this->GCLK_NUM * this->TIM3_PERIOD + 8 * this->ADD_NUM - 1;
		this->MAIN_TIMER_cc1 = this->GCLK_NUM * this->TIM3_PERIOD; 		// CH1: control OE_TIMER counting
		this->MAIN_TIMER_cc2 = this->GCLK_NUM * this->TIM3_PERIOD + 2;	// CH2: line switching interrupt
		this->OE_TIMER_reload = this->TIM3_PERIOD - 1;
		this->OE_TIMER_cc = this->TIM3_PERIOD / 2;
		DMD_RGB_FM6363_BASE<Pars...>::init(scan_interval);

		uint16_t conf_6363[] = {0x7e08, 0x0fb0, 0xe6fc, 0x60b6, 0x5a70};

		// Config value for 4 latches depends on number of scans
		conf_6363[1] = ((this->nRows - 1) << 8) | (conf_6363[1] & 0xFF);
		ADD_CONFIG_REGS(conf_6363);
	}
};
/*--------------------------------------------------------------------------------------*/
// DP3264 driver class
/*--------------------------------------------------------------------------------------*/
template <int... Pars>
class DMD_RGB_DP3264 : public DMD_RGB_DP3264_BASE<Pars...>
{

public:
	DMD_RGB_DP3264(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
				   byte panelsWide, byte panelsHigh, bool d_buf = false)
		: DMD_RGB_DP3264_BASE<Pars...>
		(mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
	{
	}

	void init(uint16_t scan_interval = 200) override
	{
		// MSB greyscale position for color bits
		this->gclk_bits = 13;
		
		this->GCLK_NUM = 1; // GCLK pulses in packet, 6353 - 138, 6363 - 74
#if defined(__STM32F1__)
		this->ADD_NUM = 235; // Dummy timer ticks to finish the lines switching, can cause glitches if too short
		this->CLK_PERIOD = 12;
		this->TIM3_PERIOD = 12;
#elif defined(__STM32F4__)
		this->ADD_NUM = 232;
		this->CLK_PERIOD = 8;
		this->TIM3_PERIOD = 8;
#endif
		 // MAIN loop duration = (1) x OE pulse + 96 CLK pulses + delay for line switching
		 // Experimental: minimum loop duration about 112 - 116 CLK pulses
		this->MAIN_TIMER_reload = this->GCLK_NUM * this->TIM3_PERIOD + this->TIM3_PERIOD * this->ADD_NUM + 4;
		// switch off OE timer to make 4x CLK OE pulse
		this->MAIN_TIMER_cc1 = 12 * this->GCLK_NUM * this->TIM3_PERIOD;   
		// CH2 interrupt for line switching (about 95-105 CLK from OE)
		this->MAIN_TIMER_cc2 = this->GCLK_NUM * this->TIM3_PERIOD + this->TIM3_PERIOD * (this->ADD_NUM - 40);
		// 4x CLK OE pulse
		this->OE_TIMER_reload = 12 * this->TIM3_PERIOD - 1;
		this->OE_TIMER_cc = 4 * this->TIM3_PERIOD;
		DMD_RGB_DP3264_BASE<Pars...>::init(scan_interval);

		uint16_t conf_3264[] = {0x1100, 0x020f, 0x033f, 0x043f, 0x0504, 0x0642, 0x0700, 0x08BF, 0x0960, 0x0ABE, 0x0B8B, 0x0C88, 0x0D12};

		conf_3264[1] = 0x0200 | (this->nRows - 1); /// panel scan
		ADD_CONFIG_REGS(conf_3264);
		this->spwm_chip_init();
	}

protected:
	void load_config_regs(uint16_t *conf_reg) override
	{
		static uint8_t r = this->conf_reg_cnt;
		r++;
		if (r >= this->conf_reg_cnt)
		{

			r = 0;
		}

		this->send_vsync(); // vsync
		this->send_clocks(16);

		//*(this->oesetreg) = this->oemask;
		this->send_latches(14); // pre-active command
		//*(this->oesetreg) = this->oemask << 16;
		this->send_clocks(8);
		// this->start_GCLK();
		this->send_to_allRGB(conf_reg[r], 5); // send config registers
		this->send_clocks(8);
	}
};

/*--------------------------------------------------------------------------------------*/
// ICN2055 driver class
/*--------------------------------------------------------------------------------------*/
template <int... Pars>
class DMD_RGB_ICN2055 : public DMD_RGB_DP3264_BASE<Pars...>
{

public:
	DMD_RGB_ICN2055(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
					byte panelsWide, byte panelsHigh, bool d_buf = false) : 
					DMD_RGB_DP3264_BASE<Pars...>
					(mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
	{
	}

	void init(uint16_t scan_interval = 200) override
	{
		// MSB greyscale position for color bits
		this->gclk_bits = 13;
		
		this->GCLK_NUM = 1; // GCLK pulses in packet, 6353 - 138, 6363 - 74
#if defined(__STM32F1__)
		this->CLK_PERIOD = 12;
		this->TIM3_PERIOD = 12;
		this->ADD_NUM = 228; // Dummy timer ticks to finish the lines switching, can cause glitches if too short
#elif defined(__STM32F4__)
		this->CLK_PERIOD = 8;
		this->TIM3_PERIOD = 8;
		this->ADD_NUM = 228;
#endif
        // Timer settings (see DP3264 class for details)
		this->MAIN_TIMER_reload = this->GCLK_NUM * this->TIM3_PERIOD + this->TIM3_PERIOD * this->ADD_NUM + 4;
		this->MAIN_TIMER_cc1 = 12 * this->GCLK_NUM * this->TIM3_PERIOD;
		this->MAIN_TIMER_cc2 = this->GCLK_NUM * this->TIM3_PERIOD + this->TIM3_PERIOD * (this->ADD_NUM - 35);
		this->OE_TIMER_reload = 12 * this->TIM3_PERIOD - 1;
		this->OE_TIMER_cc = 4 * this->TIM3_PERIOD;
		DMD_RGB_DP3264_BASE<Pars...>::init(scan_interval);
		uint16_t icn2055_conf[] = {
			0x021f, 0x033f, 0x0400, 0x0507, 0x0603, 0x0720, 0x0820, 0x0908, 0x0a08, 0x0b00,
			0x0c08, 0x0d01, 0x0e04, 0x0f01, 0x1082, 0x1121, 0x1201, 0x17f0, 0x181f, 0x1950,
			0x1a1f, 0x1b10, 0x1ccf, 0x1d0a, 0x1e4c, 0x1f20, 0x2008, 0x2101, 0x221c};

		icn2055_conf[0] = 0x200 | (this->nRows - 1); /// panel scan

		ADD_CONFIG_REGS(icn2055_conf);
		this->spwm_chip_init();
	}

protected:
	void load_config_regs(uint16_t *conf_reg) override
	{
		static uint8_t r = this->conf_reg_cnt;
		r++;
		if (r >= this->conf_reg_cnt)
		{

			r = 0;
		}

		this->send_vsync(); // vsync
		this->send_clocks(8);
		this->send_latches(11); // pre-active command
		//*(this->oesetreg) = this->oemask << 16;
		this->send_clocks(8);
		//*(this->oesetreg) = this->oemask;
		this->send_latches(14); // pre-active command
		//*(this->oesetreg) = this->oemask << 16;
		this->send_clocks(8);
		// this->start_GCLK();
		this->send_to_allRGB(0x00aa, 5);
		this->send_to_allRGB(0x01aa, 5);
		this->send_to_allRGB(conf_reg[r], 5); // send config registers
		this->send_to_allRGB(0x0055, 5);
		this->send_to_allRGB(0x0155, 5);
		this->send_clocks(8);
	}
};

/*--------------------------------------------------------------------------------------*/
// FM6373 driver class
/*--------------------------------------------------------------------------------------*/
template <int... Pars>
class DMD_RGB_FM6373 : public DMD_RGB_DP3264_BASE<Pars...>
{

public:
	DMD_RGB_FM6373(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
				   byte panelsWide, byte panelsHigh, bool d_buf = false) : 
				   DMD_RGB_DP3264_BASE<Pars...>
				   (mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
	{
	}

	void init(uint16_t scan_interval = 200) override
	{

		this->GCLK_NUM = 1; // GCLK pulses in packet, 6353 - 138, 6363 - 74
#if defined(__STM32F1__)
		this->ADD_NUM = 228; // Dummy timer ticks to finish the lines switching, can cause glitches if too short
		this->CLK_PERIOD = 12;
		this->TIM3_PERIOD = 12;
#elif defined(__STM32F4__)
		this->ADD_NUM = 228;
		this->CLK_PERIOD = 8;
		this->TIM3_PERIOD = 8;
#endif
		// Timer settings (see DP3264 class for details)
		this->MAIN_TIMER_reload = this->GCLK_NUM * this->TIM3_PERIOD + this->TIM3_PERIOD * this->ADD_NUM + 4;
		this->MAIN_TIMER_cc1 = 12 * this->GCLK_NUM * this->TIM3_PERIOD;
		this->MAIN_TIMER_cc2 = this->GCLK_NUM * this->TIM3_PERIOD + this->TIM3_PERIOD * (this->ADD_NUM - 35);
		this->OE_TIMER_reload = 12 * this->TIM3_PERIOD - 1;
		this->OE_TIMER_cc = 4 * this->TIM3_PERIOD;
		DMD_RGB_DP3264_BASE<Pars...>::init(scan_interval);

		uint16_t fm6373_conf[] = {
			0x021f, 0x033f, 0x0402, 0x0507, 0x0603, 0x0720, 0x0820, 0x0900, 0x0a00, 0x0b00,
			0x0c01, 0x0d01, 0x0e04, 0x0f01, 0x10c2, 0x1121, 0x1201, 0x17f0, 0x181f, 0x1900,
			0x1a1f, 0x1b10, 0x1cc1, 0x1d0a, 0x1e42, 0x1f04, 0x2008, 0x2101, 0x221c};

		fm6373_conf[0] = 0x200 | (this->nRows - 1); /// panel scan
		ADD_CONFIG_REGS(fm6373_conf);
		this->spwm_chip_init();
	}

protected:
	void load_config_regs(uint16_t *conf_reg) override
	{
		static uint8_t r = this->conf_reg_cnt;
		r++;
		if (r >= this->conf_reg_cnt)
		{

			r = 0;
		}

		this->send_vsync(); // vsync
		this->send_clocks(8);
		this->send_latches(11); // pre-active command
		//*(this->oesetreg) = this->oemask << 16;
		this->send_clocks(8);
		//*(this->oesetreg) = this->oemask;
		this->send_latches(14); // pre-active command
		//*(this->oesetreg) = this->oemask << 16;
		this->send_clocks(8);
		// this->start_GCLK();
		this->send_to_allRGB(0x00aa, 5);
		this->send_to_allRGB(0x01aa, 5);
		this->send_to_allRGB(conf_reg[r], 5); // send config registers
		this->send_to_allRGB(0x0055, 5);
		this->send_to_allRGB(0x0155, 5);
		this->send_clocks(8);
	}
};
/*--------------------------------------------------------------------------------------*/
// SM16380sh driver class
/*--------------------------------------------------------------------------------------*/
template <int... Pars>
class DMD_RGB_SM16380SH : public DMD_RGB_DP3264_BASE<Pars...>
{

public:
	DMD_RGB_SM16380SH(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
				   byte panelsWide, byte panelsHigh, bool d_buf = false) : 
				   DMD_RGB_DP3264_BASE<Pars...>
				   (mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
	{
	}



	void init(uint16_t scan_interval = 200) override
	{
		// MSB greyscale position for color bits
		this->gclk_bits = 13;
		
		this->GCLK_NUM = 1; // GCLK pulses in packet, 6353 - 138, 6363 - 74
#if defined(__STM32F1__)
		this->ADD_NUM = 232; // Dummy timer ticks to finish the lines switching, can cause glitches if too short
		this->CLK_PERIOD = 12;
		this->TIM3_PERIOD = 12;
#elif defined(__STM32F4__)
		this->ADD_NUM = 232;
		this->CLK_PERIOD = 8;
		this->TIM3_PERIOD = 8;
#endif
		// Timer settings (see DP3264 class for details)
		this->MAIN_TIMER_reload = this->GCLK_NUM * this->TIM3_PERIOD + this->TIM3_PERIOD * this->ADD_NUM + 4;
		this->MAIN_TIMER_cc1 = 12 * this->GCLK_NUM * this->TIM3_PERIOD;
		this->MAIN_TIMER_cc2 = this->GCLK_NUM * this->TIM3_PERIOD + this->TIM3_PERIOD * (this->ADD_NUM - 35);
		this->OE_TIMER_reload = 12 * this->TIM3_PERIOD - 1;
		this->OE_TIMER_cc = 4 * this->TIM3_PERIOD;
		DMD_RGB_DP3264_BASE<Pars...>::init(scan_interval);

		uint16_t sm16380sh_conf[] = {
			0x021f, 0x0300, 0x0400, 0x0500, 0x0600, 
			0x0750, 0x0800, 0x0900, 
			0x0a02, 0x0b0c,
			0x0c08, 0x0d00, 0x0e05, 0x0f00, 0x1000, 0x1100, 0x1200, 0x1300, 
			0x1414, 0x1500,
			0x1630, 0x1700, 
			0x1801, 0x1904,0x1a03, 0x1b14, 0x1c12, 0x1d00, 0x1e00, 0x1f0c};

		sm16380sh_conf[0] = 0x200 | (this->nRows - 1); /// panel scan
		ADD_CONFIG_REGS(sm16380sh_conf);
		this->spwm_chip_init();
	}

protected:
	void load_config_regs(uint16_t *conf_reg) override
	{
		static uint8_t r = this->conf_reg_cnt;
		r++;
		if (r >= this->conf_reg_cnt)
		{

			r = 0;
		}

		this->send_vsync(); // vsync
		//this->send_clocks(8);
		//this->send_latches(11); // pre-active command
		//*(this->oesetreg) = this->oemask << 16;
		this->send_clocks(8);
		//*(this->oesetreg) = this->oemask;
		this->send_latches(14); // pre-active command
		//*(this->oesetreg) = this->oemask << 16;
		this->send_clocks(8);
		
		this->send_to_allRGB(0x00aa, 5);
		this->send_to_allRGB(0x01aa, 5);
		this->send_to_allRGB(conf_reg[r], 5); // send config registers
		//this->send_to_allRGB(0xF003, 5);
		this->send_to_allRGB(0x0055, 5);
		this->send_to_allRGB(0x0155, 5);
		//this->send_clocks(8);
		
	}
};

/*--------------------------------------------------------------------------------------*/
// ICND1065 driver class
/*--------------------------------------------------------------------------------------*/
template <int... Pars>
class DMD_RGB_ICN1065 : public DMD_RGB_DP3264_BASE<Pars...>
{

public:
	DMD_RGB_ICN1065(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
				   byte panelsWide, byte panelsHigh, bool d_buf = false) : 
				   DMD_RGB_DP3264_BASE<Pars...>
				   (mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
	{
	}

	void init(uint16_t scan_interval = 200) override
	{
		// MSB greyscale position for color bits
		this->gclk_bits = 12;

		this->GCLK_NUM = 1; // GCLK pulses in packet, 6353 - 138, 6363 - 74
#if defined(__STM32F1__)
		this->ADD_NUM = 228; // Dummy timer ticks to finish the lines switching, can cause glitches if too short
		this->CLK_PERIOD = 12;
		this->TIM3_PERIOD = 12;
#elif defined(__STM32F4__)
		this->ADD_NUM = 228;
		this->CLK_PERIOD = 8;
		this->TIM3_PERIOD = 8;
#endif
		// Timer settings (see DP3264 class for details)
		this->MAIN_TIMER_reload = this->GCLK_NUM * this->TIM3_PERIOD + this->TIM3_PERIOD * this->ADD_NUM + 4;
		this->MAIN_TIMER_cc1 = 12 * this->GCLK_NUM * this->TIM3_PERIOD;
		this->MAIN_TIMER_cc2 = this->GCLK_NUM * this->TIM3_PERIOD + this->TIM3_PERIOD * (this->ADD_NUM - 35);
		this->OE_TIMER_reload = 12 * this->TIM3_PERIOD - 1;
		this->OE_TIMER_cc = 4 * this->TIM3_PERIOD;
		DMD_RGB_DP3264_BASE<Pars...>::init(scan_interval);

		uint16_t icn1065_conf[] = {
			0x00aa, 0x01aa, 0x022a, 0x0335, 0x0412, 0x0500, 0x0601, 0x0720, 0x0c18, 0x0d01, 0x0e86, 0x0f01, //00-12
			0x1040, 0x1127, 0x1200, 0x1300, 0x1400, 0x1500, 0x1600, 0x1800, 0x1906, 0x1c60, 0x1dca, 0x1e73, //13-24
			0x1f00, 0x2000, 0x2100, 0x2200, 0x2300, 0x2400, 0x2500, 0x2600, 0x2700, 0x7000, 0x7100, 0x7200, 0x7300, 0x74A0 //25-38
			};
		icn1065_conf[2] = 0x200 | (this->nRows - 1); //Special register location is 2
		ADD_CONFIG_REGS(icn1065_conf);
		this->spwm_chip_init();
	}

protected:
	void load_config_regs(uint16_t *conf_reg) override
	{
		static uint8_t r = this->conf_reg_cnt;
		r++;
		if (r >= this->conf_reg_cnt)
		{

			r = 0;
		}

		this->send_vsync(); // vsync
		this->send_clocks(8);
		this->send_latches(11); // pre-active command
		//*(this->oesetreg) = this->oemask << 16;
		this->send_clocks(8);
		//*(this->oesetreg) = this->oemask;
		this->send_latches(14); // pre-active command
		//*(this->oesetreg) = this->oemask << 16;
		this->send_clocks(8);
		// this->start_GCLK();
		this->send_to_allRGB(0x00aa, 5);
		this->send_to_allRGB(0x01aa, 5);
		this->send_to_allRGB(conf_reg[r], 5); // send config registers
		this->send_to_allRGB(0x0055, 5);
		this->send_to_allRGB(0x0155, 5);
		this->send_clocks(8);
	}
};
#endif // STM32F1 & F4
#endif // DMD_RGB_SPWM_DRIVER_H