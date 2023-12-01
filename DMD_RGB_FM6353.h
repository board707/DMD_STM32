#pragma once

#ifndef DMD_RGB_FM6353_H
#define DMD_RGB_FM6353_H
/*--------------------------------------------------------------------------------------
 This file is a part of the DMD_STM32 library

 DMD_STM32.h  - STM32 port of DMD.h library

 https://github.com/board707/DMD_STM32
 Dmitry Dmitriev (c) 2019-2023
/--------------------------------------------------------------------------------------*/

// FM6353/6363 drivers

// (supported for STM32 boards only)
/*--------------------------------------------------------------------------------------*/
#if (defined(__STM32F1__) || defined(__STM32F4__))
#include "DMD_RGB.h"

/* Config registers for FM6353 and FM6363
*
*  Values are from discussion: https://github.com/hzeller/rpi-rgb-led-matrix/issues/466
*/
static uint16_t conf_6353[] = { 0x0008, 0x1f70 , 0x6707 , 0x40f7 , 0x0040 };
static uint16_t conf_6363[] = { 0x7e08, 0x0fb0 , 0xe79d , 0x60b6 , 0x5a70 };
// 6353
	/*	const uint16_t conf_reg4 = 0x1f70;     // hi byte - number of scans - 1
		const uint16_t conf_reg6 = 0x6707;
		const uint16_t conf_reg8 = 0x40f7;
		const uint16_t conf_reg10 = 0x0040;
		const uint16_t conf_reg2 = 0x0008;   */
		//6363
			/*  const uint16_t conf_reg4 = 0x0fb0;
				const uint16_t conf_reg6 = 0xe79d;       // hi byte should be e7
				const uint16_t conf_reg8 = 0x60b6;       // can be as 6353
				const uint16_t conf_reg10 = 0x5a70;
				const uint16_t conf_reg2 = 0x7e08;   */


#define pew_6353_2(x)                    \
       *(this->datasetreg) = (x); \
		*(this->datasetreg) = this->clk_clrmask;     

/*--------------------------------------------------------------------------------------*/
/*
* Base class for FM6353/6363 drivers
*/
/*--------------------------------------------------------------------------------------*/
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE, int COL_DEPTH>
class DMD_RGB_FM6353_BASE : public DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>
	{
	public:
		DMD_RGB_FM6353_BASE(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>
			(mux_list, _pin_nOE, _pin_SCLK, pinlist,
				panelsWide, panelsHigh, false)
			{
			// Config value for 4 latches depends on number of scans
			conf_6353[1] = ((SCAN - 1) << 8) | (conf_6353[1] & 0xFF);
			}
		volatile bool oe_scan_flag = false;
		volatile bool oe_scan_res = false;
		uint8_t TIM3_PERIOD = 8;
		uint8_t GCLK_NUM = 138;   // GCLK pulses in packet, 6353 - 138, 6363 - 74
		
#if defined(__STM32F1__) 
		uint8_t ADD_NUM = 40;     // Dummy timer ticks to finish the lines switching, can cause glitches if too short
		dma_dev* rgbDmaDev = DMA1;
#if defined(ALTERNATIVE_DMD_TIMERS)
		dma_channel  DmaMuxChannel = DMA_CH2;
#else
		dma_channel  DmaMuxChannel = DMA_CH5;
#endif
#elif defined(__STM32F4__) 
		uint8_t ADD_NUM = 22;
#endif


		void generate_rgbtable()  override { DMD_RGB_BASE::generate_rgbtable_default(CLK_WITH_DATA); }


		virtual void init(uint16_t scan_interval = 200) override {
			this->oe_scan_flag = false;
			DMD_RGB_BASE::init(scan_interval);
			pinMode(this->pin_DMD_nOE, PWM);

			}


		// Hold LAT line HIGH for given number of CLK pulses
		void send_latches(uint16_t latches) {
			*(this->datasetreg) = this->clk_clrmask; // off all rgb channels
			*(this->latsetreg) = this->latmask;      // switch LE ON
			while (latches) {
				*(this->datasetreg) = this->clkmask;
				*(this->datasetreg) = this->clkmask << 16;
				latches--;
				}
			*(this->latsetreg) = this->latmask << 16;      // LAT - LOW
			}


		// Using timers:
		// GCLK pulse packets generated by PWM1 mode of OE_TIMER on its output pin.
		// To insure exact number of GCLK pulses in packet, OE_TIMER start/stop is triggered by CH1 of MAIN_TIMER (Master mode)
		// Line switching is going by DMA on CH3 (STM32F1) or by CH2 compare match interrupt (STM32F4) 
		void initialize_timers(voidFuncPtr handler) override {

			timer_init(this->MAIN_TIMER);
			timer_pause(this->MAIN_TIMER);
			timer_set_prescaler(this->MAIN_TIMER, 0);
			(this->MAIN_TIMER->regs).gen->SMCR = TIMER_SMCR_MSM;	// Master mode

			timer_set_reload(this->MAIN_TIMER, (GCLK_NUM * TIM3_PERIOD + 8 * ADD_NUM - 1));
			(this->MAIN_TIMER->regs).gen->CR2 = TIMER_CR2_MMS_COMPARE_OC1REF;         // Master/slave : use CC1 as trigger output
			timer_set_compare(this->MAIN_TIMER, 1, GCLK_NUM * TIM3_PERIOD);           // OE generator on/off

#if defined(__STM32F1__)	
			timer_set_compare(this->MAIN_TIMER, 2, GCLK_NUM * TIM3_PERIOD + 4 * ADD_NUM);       // set CC value for interrupt
			timer_set_compare(this->MAIN_TIMER, 3, GCLK_NUM * TIM3_PERIOD + 2 * ADD_NUM);       // set CC value for DMA request
			timer_dma_enable_req(this->MAIN_TIMER, 3);                                          // CH3 DMA request enable
#elif defined(__STM32F4__) 
			timer_set_compare(this->MAIN_TIMER, 2, GCLK_NUM * TIM3_PERIOD + 2 * ADD_NUM);       // set CC value for interrupt
#endif		
			timer_oc_set_mode(this->MAIN_TIMER, 1, TIMER_OC_MODE_PWM_1, 0);


#if defined(__STM32F1__) 
			// setup DMA transfer from mux table to A B C D E GPIOs
			dma_init(rgbDmaDev);
			dma_setup_transfer(rgbDmaDev, DmaMuxChannel, (uint32_t*)this->muxsetreg, DMA_SIZE_32BITS, (uint32_t*)this->mux_mask2 + 1, DMA_SIZE_32BITS, (DMA_MINC_MODE | DMA_CIRC_MODE | DMA_FROM_MEM));
			dma_set_num_transfers(rgbDmaDev, DmaMuxChannel, this->nRows);
			dma_enable(rgbDmaDev, DmaMuxChannel);

#elif defined(__STM32F4__) 
			// Not use DMA because in STM32F4 MCU only DMA2 has access to GPIOs
			timer_attach_interrupt(this->MAIN_TIMER, TIMER_CC2_INTERRUPT, scan_running_dmd_R);

#endif

			timer_init(this->OE_TIMER);
			timer_pause(this->OE_TIMER);
			timer_set_prescaler(this->OE_TIMER, 0);

			// connect slave OE_TIMER to Master
#if defined(ALTERNATIVE_DMD_TIMERS)
			(this->OE_TIMER->regs).gen->SMCR = TIMER_SMCR_TS_ITR2 | TIMER_SMCR_SMS_GATED;
#else
			(this->OE_TIMER->regs).gen->SMCR = TIMER_SMCR_TS_ITR3 | TIMER_SMCR_SMS_GATED;
#endif

			timer_oc_set_mode(this->OE_TIMER, this->oe_channel, TIMER_OC_MODE_PWM_1, 0);
			timer_set_reload(this->OE_TIMER, TIM3_PERIOD - 1);
			timer_cc_enable(this->OE_TIMER, this->oe_channel);
			timer_cc_set_pol(this->OE_TIMER, this->oe_channel, 1);
			timer_set_compare(this->OE_TIMER, this->oe_channel, TIM3_PERIOD / 2);
			}

		// VSYNC pulse
		virtual void fm6353_vsync() {
			*(this->datasetreg) = this->clk_clrmask;
			*(this->datasetreg) = this->clkmask;
			this->send_latches(3);

			}

		// initialization pulse train
		virtual void init_fm63x3(uint16_t* conf_reg) {

			this->send_latches(14);								// pre-active command
			this->send_latches(12);								// eneble all output
			this->fm6353_vsync();								// vsync
			for (uint8_t r = 0; r < 5; r++) {
				delayMicroseconds(1);
				this->send_latches(14);							// pre-active command
				this->send_to_allRGB(conf_reg[r], r * 2 + 2);	// send config registers
				}

			}

		// interrupt handler
		void scan_dmd() override {

			// in case of new greyscale data
			if (this->oe_scan_flag == false) {
				// switch off master timer trigger
				// and disable GCLK generation
				timer_set_compare(this->MAIN_TIMER, 1, 0);
				}
#if defined(__STM32F4__) 
			// otherwise the normal operation - switching lines
			else {
				this->set_mux(this->row);
				this->row++;
				if (this->row >= this->nRows) this->row = 0;
				}
#endif
			this->oe_scan_res = false;
			}

		// part of greyscale loading process  - stop GCLK generation
		virtual void stop_GCLK() {
			// if timer is running
			if (this->oe_scan_flag) {
				noInterrupts();
				// set stopping GCLK (OE) flag
				this->oe_scan_flag = false;
				this->oe_scan_res = true;

#if defined(__STM32F1__)	
				timer_attach_interrupt(this->MAIN_TIMER, TIMER_CC2_INTERRUPT, scan_running_dmd_R);
#endif
				interrupts();
				// wait for GCLK stop
				while (this->oe_scan_res) {};
				delayMicroseconds(5);
				}

			timer_pause(this->MAIN_TIMER);
#if defined(__STM32F1__) 
			dma_disable(rgbDmaDev, DmaMuxChannel);
			timer_detach_interrupt(this->MAIN_TIMER, TIMER_CC2_INTERRUPT);
#endif

			// switch to row 0
			this->row = 0;
			this->set_mux(this->row);
			this->row++;
			delayMicroseconds(10);
			this->oe_scan_flag = true;

			}

		// part of greyscale loading process  -  restart GCLK generation
		virtual void start_GCLK() {

			timer_pause(this->OE_TIMER);
			timer_set_compare(this->MAIN_TIMER, 1, this->GCLK_NUM * this->TIM3_PERIOD);
#if defined(__STM32F1__) 
			dma_setup_transfer(rgbDmaDev, DmaMuxChannel, (uint32_t*)this->muxsetreg, DMA_SIZE_32BITS, (uint32_t*)this->mux_mask2 + 1, DMA_SIZE_32BITS, (DMA_MINC_MODE | DMA_CIRC_MODE | DMA_FROM_MEM));
			dma_set_num_transfers(rgbDmaDev, DmaMuxChannel, this->nRows);
			dma_enable(rgbDmaDev, DmaMuxChannel);
#endif		

			timer_set_count(this->MAIN_TIMER, 0);
			timer_set_count(this->OE_TIMER, 0);
			timer_resume(this->OE_TIMER);
			timer_resume(this->MAIN_TIMER);
			}


		virtual uint16_t expand_planes(volatile uint8_t* ptr2) { return 0; }

		// part of greyscale loading process  - load greyscale data
		virtual void data_transfer() {
			this->buffptr = this->matrixbuff[1 - this->backindex];
			volatile uint8_t* ptr = this->buffptr;
			volatile uint8_t* ptr2 = this->buffptr;
			const uint8_t num_sect = this->x_len / 16;
			// iterate each scan line
			for (uint8_t y = 0; y < this->nRows; y++)
				{
				// data pointer to next scan line data
				ptr = this->buffptr + y * (this->x_len);

				// each FM63x3 driver controls 16 leds
				// so the data should be loaded by 16 pixels

				for (uint8_t x = 0; x < 16; x++)
					{

					ptr2 = ptr + x;

					for (uint8_t sect = 0; sect < num_sect; sect++)
						{
						// 16 greyscale bits for each pixel MSB first

						//4 most significant bits are loaded from buffer
						uint16_t b = this->expand_planes(ptr2);

						// the others are copied from 4th bit
						pew_6353_2(b) pew_6353_2(b)
							pew_6353_2(b) pew_6353_2(b) pew_6353_2(b)
							pew_6353_2(b) pew_6353_2(b) pew_6353_2(b)
							pew_6353_2(b) pew_6353_2(b) pew_6353_2(b)


							// The last bit in serie must latched
							if (sect < num_sect - 1) {
								pew_6353_2(b)
									ptr2 += 16;
								}
							else
								{
								*(this->latsetreg) = this->latmask;  // switch LE ON
								pew_6353_2(b)
									* (this->latsetreg) = this->latmask << 16;      // LAT - LOW
								}

						}

					}
				}
			}

		// the main greyscale upload function
		virtual void fm6353_refresh() {

			this->stop_GCLK();
			*(this->datasetreg) = this->clk_clrmask;
			delayMicroseconds(2);
			this->init_fm63x3(conf_6353);

			this->start_GCLK();
			this->data_transfer();
			}


		// load user data buffer to matrix
		void swapBuffers(boolean copy) override {

			this->fm6353_refresh();

			}
	};

/*--------------------------------------------------------------------------------------*/
/*
* Base class for FM6363 driver
*/
/*--------------------------------------------------------------------------------------*/

template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE, int COL_DEPTH>
class DMD_RGB_FM6363_BASE : public DMD_RGB_FM6353_BASE<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>
	{
	public:
		DMD_RGB_FM6363_BASE(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB_FM6353_BASE <MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>
			(mux_list, _pin_nOE, _pin_SCLK, pinlist,
				panelsWide, panelsHigh, false)
			{

			// Config value for 4 latches depends on number of scans
			conf_6363[1] = ((SCAN - 1) << 8) | (conf_6363[1] & 0xFF);
			}

		uint32_t dclk_strobe[2] = { 0 };
		uint8_t CLK_PERIOD = 8;


#if defined(__STM32F1__) 
		timer_dev* CLK_TIMER = TIMER2;
		dma_channel  DmaClkChannel = DMA_CH1;

#elif defined(__STM32F4__) 
		const timer_dev* CLK_TIMER = TIMER1;
		const dma_dev* rgbDmaDev = DMA2;

		dma_channel  DmaClkChannel = DMA_CH6;
		dma_stream  ClkDmaStream = DMA_STREAM6; // TIM1 CH3 */


#endif


		void init(uint16_t scan_interval = 200) override {
			
			this->dclk_strobe[0] = this->clkmask;
			this->dclk_strobe[1] = (this->clkmask) << 16;
			this->TIM3_PERIOD = 8;
			this->GCLK_NUM = 74;    // GCLK in pulse packet: 6353 - 138, 6363 - 74
#if defined(__STM32F1__) 
			this->ADD_NUM = 32;     // timer ticks for line switching 6353 - 72, 6363 - 22
#elif defined(__STM32F4__) 
			this->ADD_NUM = 22;     // timer ticks for line switching 6353 - 72, 6363 - 22
#endif
			DMD_RGB_FM6353_BASE <MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>::init(scan_interval);
			}

		// Timer setup : continuous CLK by DMA request on CH3 of CLK_TIMER
		// On STM32F4 only Timer1 can used for DMA
		virtual void initialize_timers(voidFuncPtr handler) override {

			DMD_RGB_FM6353_BASE <MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>::initialize_timers(handler);

			timer_init(this->CLK_TIMER);
			timer_pause(this->CLK_TIMER);
			timer_set_prescaler(this->CLK_TIMER, 0);

			timer_dma_enable_req(this->CLK_TIMER, 3);								//CH3 DMA request enable
			timer_set_reload(this->CLK_TIMER, this->CLK_PERIOD - 1);
			timer_set_compare(this->CLK_TIMER, 3, this->CLK_PERIOD / 2);



#if defined(__STM32F1__) 
			dma_setup_transfer(this->rgbDmaDev, this->DmaClkChannel, (uint32_t*)(this->datasetreg), DMA_SIZE_32BITS, (uint32_t*)this->dclk_strobe, DMA_SIZE_32BITS, (DMA_MINC_MODE | DMA_CIRC_MODE | DMA_FROM_MEM));
			dma_set_num_transfers(this->rgbDmaDev, this->DmaClkChannel, 2);
			dma_enable(this->rgbDmaDev, this->DmaClkChannel);

#elif defined(__STM32F4__) 
			dma_init(rgbDmaDev);
			dma_disable(this->rgbDmaDev, this->ClkDmaStream);
			dma_clear_isr_bits(this->rgbDmaDev, this->ClkDmaStream);
			dma_setup_transfer(this->rgbDmaDev, this->ClkDmaStream, this->DmaClkChannel, DMA_SIZE_32BITS, (uint32_t*)(this->datasetreg), (uint32_t*)this->dclk_strobe, NULL, (DMA_CIRC_MODE | DMA_MINC_MODE | DMA_FROM_MEM));
			dma_set_num_transfers(this->rgbDmaDev, this->ClkDmaStream, 2);
			dma_enable(this->rgbDmaDev, this->ClkDmaStream);

#endif

			}

		
		void fm6353_refresh() override {
			
			this->stop_GCLK();
			timer_pause(this->CLK_TIMER);
#if defined(__STM32F1__) 
			dma_disable(this->rgbDmaDev, this->DmaClkChannel);
#elif defined(__STM32F4__) 
			dma_disable(this->rgbDmaDev, this->ClkDmaStream);
#endif

			* (this->datasetreg) = this->clk_clrmask;
			delayMicroseconds(2);

			this->init_fm63x3(conf_6363);
			this->start_GCLK();

			this->data_transfer();
#if defined(__STM32F1__) 
			dma_enable(this->rgbDmaDev, this->DmaClkChannel);
#elif defined(__STM32F4__) 
			dma_enable(this->rgbDmaDev, this->ClkDmaStream);
#endif

			timer_set_count(this->CLK_TIMER, 0);
			timer_resume(this->CLK_TIMER);
			}

	};


// FM6363 color template for COLOR_1BIT and COLOR_4BITS modes
/*--------------------------------------------------------------------------------------*/
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE, int COL_DEPTH>

class DMD_RGB_FM6363 : public DMD_RGB_FM6363_BASE<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>
	{

	public:
		DMD_RGB_FM6363(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB_FM6363_BASE<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>
			(mux_list, _pin_nOE, _pin_SCLK, pinlist,
				panelsWide, panelsHigh, d_buf)
			{

			}

		// load COL_DEPTH greyscale values
		uint16_t expand_planes(volatile uint8_t* ptr3) override {
			uint16_t b = 0;
			for (byte i = 0; i < 4; i++) {
				if (i < COL_DEPTH) {
					b = this->expand[*ptr3];
					//b = *ptr3;
					ptr3 += this->displ_len;
					}
				pew_6353_2(b)
				}
			return b;
			}
	};


// FM6363 color template for COLOR_4BITS_Packed mode
/*--------------------------------------------------------------------------------------*/
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE>
class DMD_RGB_FM6363<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COLOR_4BITS_Packed>
	: public DMD_RGB_FM6363_BASE<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COLOR_4BITS_Packed>
	{
	public:
		DMD_RGB_FM6363(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB_FM6363_BASE <MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COLOR_4BITS_Packed>
			(mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
			{

			}

		// load 4 MSB greyscale values
		uint16_t expand_planes(volatile uint8_t* ptr2) override {

			uint16_t factor_l = this->displ_len;
			uint16_t b1 = this->expand[*ptr2];
			uint16_t b2 = this->expand[*(ptr2 + factor_l)];
			uint16_t b3 = this->expand[*(ptr2 + factor_l * 2)];

			byte b0 =
				(((*ptr2) >> 2) & 0x30) |
				((*(ptr2 + factor_l)) & 0x0C) |
				(((*(ptr2 + factor_l * 2)) >> 6) & 0x03);
			uint16_t b = this->expand[b0];
			pew_6353_2(b3) pew_6353_2(b2) pew_6353_2(b1) pew_6353_2(b)
				return b;
			}


	};

// FM6353 color template for COLOR_1BIT and COLOR_4BITS modes
/*--------------------------------------------------------------------------------------*/
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE, int COL_DEPTH>

class DMD_RGB_FM6353 : public DMD_RGB_FM6353_BASE<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>
	{
	public:
		DMD_RGB_FM6353(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB_FM6353_BASE <MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COL_DEPTH>
			(mux_list, _pin_nOE, _pin_SCLK, pinlist,
				panelsWide, panelsHigh, d_buf)
			{

			}


		uint16_t expand_planes(volatile uint8_t* ptr3) override {
			uint16_t b = 0;
			for (byte i = 0; i < 4; i++) {
				if (i < COL_DEPTH) {
					b = this->expand[*ptr3];
					//b = *ptr3;
					ptr3 += this->displ_len;
					}
				pew_6353_2(b)
				}
			return b;
			}
	};

// FM6363 color template for COLOR_4BITS_Packed mode
/*--------------------------------------------------------------------------------------*/
template <int MUX_CNT, int P_Width, int P_Height, int SCAN, int SCAN_TYPE>
class DMD_RGB_FM6353<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COLOR_4BITS_Packed> :
	public DMD_RGB_FM6353_BASE<MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COLOR_4BITS_Packed>
	{
	public:
		DMD_RGB_FM6353(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
			byte panelsWide, byte panelsHigh, bool d_buf = false) :
			DMD_RGB_FM6353_BASE <MUX_CNT, P_Width, P_Height, SCAN, SCAN_TYPE, COLOR_4BITS_Packed>
			(mux_list, _pin_nOE, _pin_SCLK, pinlist,
				panelsWide, panelsHigh, d_buf)
			{

			}

		uint16_t expand_planes(volatile uint8_t* ptr2) override {

			uint16_t factor_l = this->displ_len;
			uint16_t b1 = this->expand[*ptr2];
			uint16_t b2 = this->expand[*(ptr2 + factor_l)];
			uint16_t b3 = this->expand[*(ptr2 + factor_l * 2)];

			byte b0 =
				(((*ptr2) >> 2) & 0x30) |
				((*(ptr2 + factor_l)) & 0x0C) |
				(((*(ptr2 + factor_l * 2)) >> 6) & 0x03);
			uint16_t b = this->expand[b0];
			pew_6353_2(b3) pew_6353_2(b2) pew_6353_2(b1) pew_6353_2(b)
				return b;
			}

	};

#endif

#endif

