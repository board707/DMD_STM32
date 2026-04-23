#pragma once
#ifndef DMD_RGB_SPWM_DRIVER_RP_H
#define DMD_RGB_SPWM_DRIVER_RP_H
/*--------------------------------------------------------------------------------------
 This file is a part of the DMD_STM32 library.

 DMD_STM32  - STM32 & RP2040 port of DMD.h library

 This module is an attempt to provide an experimental support
 of the new generation HUB75 LED panel drivers - so-called PWM/SPWM type.

 The file includes a one base class DMD_RGB_SPWM_DRIVER_BASE and a five 
 children class for specific LED drivers.

 The chips supported:

	* DMD_RGB_DP3264 class
		+ DP3264
	
	* DMD_RGB_ICN2055 class
		+ ICND2055	

	* DMD_RGB_FM6373 class
		+ FM6373

 	* DMD_RGB_FM6353 class
		+ FM6353
		+ ICN2153

	* DMD_RGB_FM6363 class
		+ FM6363

	* DMD_RGB_ICN1065 class
		+ ICND1065

 https://github.com/board707/DMD_STM32
 Dmitry Dmitriev (c) 2019-2026

 (for RP2040 boards )
/--------------------------------------------------------------------------------------*/

#if (defined(ARDUINO_ARCH_RP2040))
#include "DMD_RGB.h"
#include "dmd_spwm.pio.h"


#define ADD_CONFIG_REGS(arr) this->add_config_regs((arr), sizeof(arr) / sizeof((arr)[0]))

/*--------------------------------------------------------------------------------------*/
/*
 * Base class for all SPWM drivers  ( specialized as DP3264 type)
 *
 * Key features: The clock source for the internal driver PWM is the DCLK (CLK) signal.
 * Row switching is synchronized based on GCLK (OE) pulses after fixed number of CLK pulses.
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
		free(dma_buffer);
	}

    virtual void init(uint16_t scan_interval = 200) override
	{
		
		DMD_RGB_BASE::init(scan_interval);
		// Two buffer for async DMA transfer, with one row length each
		dma_buffer = (uint8_t*)malloc(this->x_len * 2);
		dma_buffs[0] = dma_buffer;
		dma_buffs[1] = dma_buffer + this->x_len;
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
	uint8_t max_clk_freq = 15;  // 15 MHz (most HUB75 panels has max CLK about 20-25MHz )

    // Most driver chips only receives the lower 14 bits of 16 bits transmitted data.
	// Some drivers needs 13 or 12 bits.
	uint8_t gclk_bits = 14;
	uint8_t dimming_factor = 0;
	const uint8_t min_gclk = 8;

	// Clk_Lat SM
    uint8_t sm_clk_lat = 0;
	uint16_t clk_lat_prog_offs = 0;
	pio_sm_config clk_lat_pio_config;
	bool clk_lat_out_pin_is_lat = true;
	
    // Clk counter SM
	uint8_t sm_clk_cnt;
	uint16_t clk_cnt_prog_offs = 0;
	pio_sm_config clk_cnt_pio_config;

	dma_channel_config dma_c;
	volatile uint8_t mux_counter = 0;
	uint8_t* dma_buffer;
	uint8_t* dma_buffs[2];
	

	uint16_t *config_registers;
	uint8_t conf_reg_cnt;
    bool clk_after_upload = true;

    virtual void load_config_regs(uint16_t *conf_reg) {}

	// Copy chip config registers values to the class data
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

	virtual void spwm_chip_init() 
	{
		 this->clearScreen(true);
         for (uint8_t i = 0; i < this->conf_reg_cnt; i++) 
		 { 
			this->refresh_greyscale_data();
			delay(30);
		}
	}
	
	// Hold LAT line HIGH while generating given number of CLK pulses
    void send_latches(uint16_t latches)
	{
		// reinit pio program to use LAT as OUT pin
		if (! this->clk_lat_out_pin_is_lat) {
			sm_config_any_pins(this->pio, this->sm_clk_lat, &(this->clk_lat_pio_config), OUT_PINS, this->pin_DMD_SCLK, 1);
			dmd_out_program_reinit(this->pio, this->sm_clk_lat, this->clk_lat_prog_offs, &(this->clk_lat_pio_config));
			this->clk_lat_out_pin_is_lat = true;
		}
		send_clocks(latches, 1);
       
	}

    // The same as previous, but for OE line
	void send_oe(uint16_t latches)
	{
		// reinit pio program to use OE as OUT pin
		if ( this->clk_lat_out_pin_is_lat) {
			sm_config_any_pins(this->pio, this->sm_clk_lat, &(this->clk_lat_pio_config), OUT_PINS, this->pin_DMD_nOE, 1);
			dmd_out_program_reinit(this->pio, this->sm_clk_lat, this->clk_lat_prog_offs, &(this->clk_lat_pio_config));
			this->clk_lat_out_pin_is_lat = false;
		}
		send_clocks(latches, 1);
       
	}

	// Just send a given number of CLK pulses
	void send_clocks(uint16_t clocks, uint8_t out_state = 0)
	{
		if (!clocks) return;
		
		while (clocks)
		{
			pio_sm_put_blocking(this->pio, this->sm_clk_lat, out_state); 
			// cleat TX_STALL flag
			pio_sm_tx_fifo_stall_clear(this->pio, this->sm_clk_lat);
			clocks--;
			
		}
      
        // wait SM stall again after processing last pulse
        while(! pio_sm_is_tx_fifo_stall(this->pio, this->sm_clk_lat));
		

        // make LAT/OE line low after finishing
		if (out_state) {
			pio_sm_exec(this->pio, this->sm_clk_lat,  0xa003); // LAT - LOW
			
		}
		
	}

    // VSYNC = 3 clocks LAT pulse
	virtual void send_vsync()
	{
		if (! this->clk_lat_out_pin_is_lat) {
			sm_config_any_pins(this->pio, this->sm_clk_lat, &(this->clk_lat_pio_config), OUT_PINS, this->pin_DMD_SCLK, 1);
			dmd_out_program_reinit(this->pio, this->sm_clk_lat, this->clk_lat_prog_offs, &(this->clk_lat_pio_config));
			this->clk_lat_out_pin_is_lat = true;
		}
		pio_sm_put_blocking(this->pio, this->sm_clk_lat, 0);
		this->send_latches(3);
	}

	void initialize_timers(voidFuncPtr handler) override
	{

		// Adjust pio clk divider to not overflow panel CLK > 15 MHz
		// will be overwritten below, leave for compatibility
		if (CYCLES_PER_MICROSECOND / (4 * this->pio_clkdiv) > MAX_PANEL_CLK)
		{
			this->pio_clkdiv = 1 + CYCLES_PER_MICROSECOND / (4 * MAX_PANEL_CLK);
		}

		// PIO and DMA config
		pio_dma_init();

		// configure IRQ handler for mux change
		irq_set_exclusive_handler(PIO0_IRQ_0, handler);
		irq_set_enabled(PIO0_IRQ_0, true);
	}

	// CLK_CNT SM configuration differs in specific drivers, so we need virtual method
	virtual void add_pio_prg3()
	{
		this->pio_clkdiv = 1;
		this->sm_clk_cnt = pio_claim_unused_sm(this->pio, true);
		this->clk_cnt_prog_offs = pio_add_program(this->pio, &clock_cnt2_program);
		this->clk_cnt_pio_config = dmd_clk_cnt_program_init(this->pio, this->sm_clk_cnt, this->clk_cnt_prog_offs, this->pio_clkdiv,
															this->pin_DMD_CLK, this->pin_DMD_nOE);
	}

	virtual void pio_dma_init() override
	{
		// pio configs

		// Data out SM config
		// a PIO machine to output data to RGB pins
        this->pio_clkdiv = 1 + CYCLES_PER_MICROSECOND/(max_clk_freq * 5);
		this->sm_data = pio_claim_unused_sm(this->pio, true);
		this->data_prog_offs = pio_add_program(this->pio, &dmd_out_spwm_program);
		this->pio_config = dmd_out_spwm_program_init(this->pio, this->sm_data, this->data_prog_offs, this->pio_clkdiv,
							 this->data_pins[0], this->data_pins_cnt, this->pin_DMD_SCLK, this->pin_DMD_CLK);

        // CLK_LAT SM config
		// a PIO machine to generate CLK, LAT & OE pulses
		this->pio_clkdiv = 1 + CYCLES_PER_MICROSECOND/(max_clk_freq * 2);
		this->sm_clk_lat = pio_claim_unused_sm(this->pio, true);
		this->clk_lat_prog_offs = pio_add_program(this->pio, &clock_latches_program);
		this->clk_lat_pio_config = clock_latches_prg_init(this->pio, this->sm_clk_lat, this->clk_lat_prog_offs, this->pio_clkdiv,
                  this->pin_DMD_SCLK, this->pin_DMD_CLK);
		this->clk_lat_out_pin_is_lat = true;

        // CLK_CNT SM config
		// a PIO machine to generate DCLK & GCLK pulse trains
		this->add_pio_prg3();		  

	    pio_set_irq0_source_enabled(this->pio, pis_interrupt0, true);

		// DMA config
		this->dma_chan = dma_claim_unused_channel(true);
		this->dma_c = dma_channel_get_default_config(this->dma_chan);
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

	}						 
   
   // stop GCLK generation before loading new data
   virtual void stop_GCLK()
	{
		// if GCLK in progress
		if (this->oe_scan_flag)
		{
			noInterrupts();
			// set stopping GCLK (OE) flags
			this->oe_scan_flag = false;
			this->oe_scan_res = true;
			interrupts();

			// wait for GCLK stop flag change
			while (this->oe_scan_res){};
			
		}

        // stop CLK_LAT and CLK_CNT SMs
		pio_sm_set_enabled(this->pio, this->sm_clk_lat, false);
		//  move program counter to first line to set CLK low     
		pio_sm_exec(this->pio, this->sm_clk_lat,  this->clk_lat_prog_offs);  
		pio_sm_set_enabled(this->pio, this->sm_clk_cnt, false);
		// restart CLK_LAT to use it in send_latches() 
		pio_sm_init(this->pio, this->sm_clk_lat, this->clk_lat_prog_offs, &(this->clk_lat_pio_config));
		pio_sm_set_enabled(this->pio, this->sm_clk_lat, true);
		delayMicroseconds(10);
		
	}
   
   // main method for refresh greyscale data
	virtual void refresh_greyscale_data() 
	{

		// wait for 0-th row and stop the GCLK generation
		this->stop_GCLK();
		
        
		// load config registers
		channel_config_set_ring(&(this->dma_c), false, 4);	// (1 << 4) = wrap data by 16 bytes to write a config registers repeatedly
		dma_channel_set_config(this->dma_chan, &(this->dma_c), false); // reload DMA config after wrap change
		this->load_config_regs(this->config_registers);

		
		// load new grayscale data
        this->data_transfer();
		
		// wait for finishing upload and stop data SM
		while (!pio_interrupt_get(this->pio, 7));
		pio_interrupt_clear(this->pio, 7);
		pio_sm_set_enabled(this->pio, this->sm_data, false);

		// start CLK generation if needed
		if (this->clk_after_upload ) {
			pio_sm_init(this->pio, this->sm_clk_lat, this->clk_lat_prog_offs +clock_latches_wrap + 1, &(this->clk_lat_pio_config));
  	        pio_sm_set_enabled(this->pio, this->sm_clk_lat, true);
		}
		
	}
	
	// extract 4bit color data
	virtual uint32_t expand_planes(volatile uint8_t *ptr3) 
	{
		uint8_t b = 0;
		uint32_t res = 0;
		for (byte i = 0; i < 4; i++)
		{
			if (i < this->nPlanes)
			{
				b = *ptr3;
				// b = *ptr3;
				ptr3 += this->displ_len;
			}
			res = (res << 8) | b ;
		}
		return res;
	}


	virtual void start_DCLK()
	{
		// Start clock_counter SM
		dmd_out_program_reinit(this->pio, this->sm_clk_cnt, this->clk_cnt_prog_offs, &this->clk_cnt_pio_config);
        
		// GCLK/DCLK generation by PIO machine controlled by parameter below.
		// Format of `control_par' parameter:
		// clock loop:
		// MUX IRQ | ==== d1 ==== | OE pulse = d2 | ==== d3 ==== | MUX IRQ |
		// bits of control par: (8 MS bits - duration by CLKs, 1 LS bit - is OE switched ON (1) or OFF (0))
		// 26:19 - d3 , 18 - 0
		// 17:10 - d2, 9 - 1
		// 8:1 - d1, 0 - 0
		uint32_t control_par = 0;
		uint8_t d1 = 28, d2 = 4, d3 = 96;
		
		// TYPE_595 mux needs more time for switching
		if (this->Mux->mux_type == DMD_MUX_TYPE_SHIFTREG) {
			d1 = 38; d2 = 4; d3 = 86;
		}
		
		control_par = d3-1;
		control_par = (control_par << 9) | (1 << 8) | (d2-1);
		control_par = (control_par << 9) | (d1-1);
		pio_sm_put_blocking(this->pio, this->sm_clk_cnt, control_par);
		this->oe_scan_flag = true;
	}

    // upload greyscale to the panel
	virtual void data_transfer() 
	{
		this->buffptr = this->matrixbuff[1 - this->backindex];
		volatile uint8_t *ptr = this->buffptr;
		volatile uint8_t *ptr2 = this->buffptr;
		const uint8_t num_sect = this->x_len / 16;
		
	    uint8_t buff_select = 0;
		uint8_t* forward_ptr = dma_buffs[buff_select];
	    uint8_t* backward_ptr = dma_buffs[1 - buff_select];
	   
		bool first_run = true;

		// RP2040 code ================
		// RGB data transfer by PIO machine controlled by two parameters below
		// The first is a number of transfers (x_len - 1)
		// The second is a number of x_len - Latches
		uint32_t control_par1 = this->x_len - 1;
		uint32_t control_par2 = this->x_len - 2;
		
		// The postion of greyscale MSB can varied from 14 to 12th depending of chip
		// You can additionally shift it down as low as 8th bit by <dimming_factor>
		// to adjust color and brightness
		uint8_t gclk_msb = this->gclk_bits - this->dimming_factor;

		// generate 12 clocks OE pulse to start the data group (see the datasheet)
		//this->send_oe(12);  moved to init_mux()
		
		//  iterate each scan line
		for (uint8_t y = 0; y < this->nRows; y++)
		{
			// data pointer to next scan line data
			ptr = this->buffptr + y * (this->x_len);

			// =========================
			// copy xlen bytes for DMA

			// each driver controls 16 leds
			// so the data should be loaded by 16 pixels
           
			for (uint8_t x = 0; x < 16; x++)
			{

				ptr2 = ptr + x;
				
 				uint16_t i = 0;
				for (uint8_t sect = 0; sect < num_sect; sect++)
				{
					// get 4 color bits
					// and put them to dma_buffer
					uint32_t greyscale = this->expand_planes(ptr2);  
					// Zerofill upper bits above greyscale MSB (14-12th ) 
					memset(backward_ptr + i,(uint8_t)0,16-gclk_msb); 
					memcpy(backward_ptr + i + 16-gclk_msb, (uint8_t*)&greyscale, sizeof(greyscale));  
					
					// zerofill the remaining bits to make a total of 16
					uint8_t lsb = 0;
					memset(backward_ptr + i + 20-gclk_msb, lsb, gclk_msb -4);
					ptr2+=16;
					i+=16;
				}
			

			// swap DMA buffers
			buff_select = 1 - buff_select;
			forward_ptr = dma_buffs[buff_select];
	    	backward_ptr = dma_buffs[1 - buff_select];
			

			if ( first_run) {
				first_run = false;
				// reconfigure DMA for continuous transfer of x_len bytes
				channel_config_set_ring(&(this->dma_c), false, 0);	// cancel wrapping data for 16 bytes
		        dma_channel_set_config(this->dma_chan, &(this->dma_c), false); // reload DMA config after wrap change
				
				// start CLK_CNT SM (for compatibility with FM6363 code, do nothing for other drivers)
				pio_sm_set_enabled(this->pio, this->sm_clk_cnt, true);
				
			}
			
			else
			{

				// Wait for finishing previous transfer and uploads
				dma_channel_wait_for_finish_blocking(this->dma_chan);
				while (!pio_interrupt_get(this->pio, 7));
				pio_interrupt_clear(this->pio, 7);
			}

			// Restart DATA SM
			pio_sm_set_enabled(this->pio, this->sm_data, false);
			dmd_out_program_reinit(this->pio, this->sm_data, this->data_prog_offs, &this->pio_config);
			
			// Put a `control_par' parameters
			pio_sm_put_blocking(this->pio, this->sm_data, (control_par2<<16)|control_par1);
			
			// Start DMA transfer from `buffptr` buffer
			dma_channel_set_read_addr(this->dma_chan, forward_ptr, true);
			
			}
		}

	// Wait for finishing last transfer 
	dma_channel_wait_for_finish_blocking(this->dma_chan);
	
	}

	// send config register data to RGB lines
	void send_to_allRGB(uint16_t data, uint16_t latches) override
	{

		// to use DMA ring mode we need to align data to 16 bytes
		static uint8_t reg[16] __attribute__((aligned(16))) = {0};

		// Convert 16bit config value to byte array
		// high bits to 0xff, low bits to 0
		for (int i = 0; i < 16; i++)
		{
			if (data & 0x8000)
			{
				reg[i] = 0xff;
			}
			else
			{
				reg[i] = 0x00;
			}
			data <<= 1;
		}

		// Restart DATA SM
		dmd_out_program_reinit(this->pio, this->sm_data, this->data_prog_offs, &this->pio_config);

		// RGB data transfer by PIO machine controlled by two parameters below
		// The first is a number of transfers (x_len - 1)
		// The second is a number of x_len - Latches

		// Put a `control_par' parameters
		uint32_t control_par1 = this->x_len - 1;
		uint32_t control_par2 = this->x_len - (latches + 1);
		pio_sm_put_blocking(this->pio, this->sm_data, (control_par2 << 16) | control_par1);

		// Start DMA transfer of `reg` buffer
		dma_channel_set_read_addr(this->dma_chan, reg, true);

		// Wait for finishing DMA transfer and uploads
		dma_channel_wait_for_finish_blocking(this->dma_chan);
		while (!pio_interrupt_get(this->pio, 7))
			;
		pio_interrupt_clear(this->pio, 7);
	}

	void init_mux()
	{
		this->Mux->set_mux(0);
		this->row = 1;
		this->send_oe(12);
		this->send_clocks(88);
	}

	// PIO IRQ0 handler
	// Normal mode - Switch to next row
	// in case <oe_scan_flag == false> - waits for row =0 and stops GCLK/DCLK pulses
	// set <oe_scan_res = false> after stopping GCLK
	void scan_dmd() override
	{
		pio_interrupt_clear(this->pio, 0);
		// switch the row
		this->Mux->set_mux(this->row);

		if (this->row == 0)
		{
			if (this->oe_scan_flag == false)
			{
				// disable GCLK generation
				pio_sm_set_enabled(this->pio, this->sm_clk_cnt, false);
				pio_sm_set_enabled(this->pio, this->sm_clk_lat, false);
				this->oe_scan_res = false;
				return;
			}
		}

		this->row++;
		if (this->row >= this->nRows)
			this->row = 0;
	}
};

/*--------------------------------------------------------------------------------------*/
// DP3264 driver class
/*--------------------------------------------------------------------------------------*/
template <int... Pars>
class DMD_RGB_DP3264 : public DMD_RGB_SPWM_DRIVER_BASE<Pars...>
{

public:
	DMD_RGB_DP3264(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
				   byte panelsWide, byte panelsHigh, bool d_buf = false)
		: DMD_RGB_SPWM_DRIVER_BASE<Pars...>
		(mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
	{
	}

	void init(uint16_t scan_interval = 200) override
	{
		// MSB greyscale position for color bits
		this->gclk_bits = 13;
		
		DMD_RGB_SPWM_DRIVER_BASE<Pars...>::init(scan_interval);

		uint16_t conf_3264[] = {0x1100, 0x020f, 0x033f, 0x043f, 0x0504, 0x0642, 0x0700, 0x08BF, 0x0960, 0x0ABE, 0x0B8B, 0x0C88, 0x0D12};

		conf_3264[1] = 0x0200 | (this->nRows - 1); /// panel scan
		ADD_CONFIG_REGS(conf_3264);
		this->spwm_chip_init();
	}

protected:
	void load_config_regs(uint16_t *conf_reg) override
	{
		// send next config register in each call
		static uint8_t r = this->conf_reg_cnt;
		r++;
		if (r >= this->conf_reg_cnt)
		{

			r = 0;
		}
      
		this->send_vsync(); 
		this->send_clocks(16);
		this->send_latches(14); // pre-active command
		this->init_mux();
		pio_sm_set_enabled(this->pio, this->sm_clk_lat, false);
		
		// config and start clk_cnt SM
		this->start_DCLK();

		// send one config register 
		this->send_to_allRGB(conf_reg[r], 5); 
		
	}


};

/*--------------------------------------------------------------------------------------*/
// ICN2055 driver class
/*--------------------------------------------------------------------------------------*/
template <int... Pars>
class DMD_RGB_ICN2055 : public DMD_RGB_SPWM_DRIVER_BASE<Pars...>
{

public:
	DMD_RGB_ICN2055(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
					byte panelsWide, byte panelsHigh, bool d_buf = false) : 
					DMD_RGB_SPWM_DRIVER_BASE<Pars...>
					(mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
	{
	}

	void init(uint16_t scan_interval = 200) override
	{

	
		DMD_RGB_SPWM_DRIVER_BASE<Pars...>::init(scan_interval);
		
		// MSB greyscale position for color bits
		this->gclk_bits = 13;
		
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
		// send next config register in each call
		static uint8_t r = this->conf_reg_cnt;
		r++;
		if (r >= this->conf_reg_cnt)
		{

			r = 0;
		}

		this->send_vsync(); // vsync
		this->send_clocks(8);
		this->send_latches(11); // pre-active command
		this->send_clocks(8);
		this->send_latches(14); // pre-active command
		this->send_clocks(8);
		this->init_mux();
		pio_sm_set_enabled(this->pio, this->sm_clk_lat, false);
		
		// config and start clk_cnt SM
		this->start_DCLK();
		
		// in order to send config data we need 0x00AA 0x01AA before
		// and 0x0055,0x0155 after config value
		this->send_to_allRGB(0x00aa, 5);
		this->send_to_allRGB(0x01aa, 5);
		this->send_to_allRGB(conf_reg[r], 5); // send config register
		this->send_to_allRGB(0x0055, 5);
		this->send_to_allRGB(0x0155, 5);
		
	}
};
/*--------------------------------------------------------------------------------------*/
// FM6373 driver class
/*--------------------------------------------------------------------------------------*/
template <int... Pars>
class DMD_RGB_FM6373 : public DMD_RGB_SPWM_DRIVER_BASE<Pars...>
{

public:
	DMD_RGB_FM6373(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
				   byte panelsWide, byte panelsHigh, bool d_buf = false) : 
				  DMD_RGB_SPWM_DRIVER_BASE<Pars...>
				   (mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
	{
	}

	void init(uint16_t scan_interval = 200) override
	{

		DMD_RGB_SPWM_DRIVER_BASE<Pars...>::init(scan_interval);

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
		// send next config register in each call
		static uint8_t r = this->conf_reg_cnt;
		r++;
		if (r >= this->conf_reg_cnt)
		{

			r = 0;
		}

		this->send_vsync(); // vsync
		this->send_clocks(8);
		this->send_latches(11); // pre-active command
		this->send_clocks(8);
		this->send_latches(14); // pre-active command
		this->send_clocks(8);
		this->init_mux();
		pio_sm_set_enabled(this->pio, this->sm_clk_lat, false);
		
		// config and start clk_cnt SM
		this->start_DCLK();
		
		// in order to send config data we need 0x00AA 0x01AA before
		// and 0x0055,0x0155 after config value
		this->send_to_allRGB(0x00aa, 5);
		this->send_to_allRGB(0x01aa, 5);
		this->send_to_allRGB(conf_reg[r], 5); // send config register
		this->send_to_allRGB(0x0055, 5);
		this->send_to_allRGB(0x0155, 5);
	}
};

/*--------------------------------------------------------------------------------------*/
// SM16380SH driver class
/*--------------------------------------------------------------------------------------*/
template <int... Pars>
class DMD_RGB_SM16380SH : public DMD_RGB_SPWM_DRIVER_BASE<Pars...>
{

public:
	DMD_RGB_SM16380SH(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
				   byte panelsWide, byte panelsHigh, bool d_buf = false) : 
				  DMD_RGB_SPWM_DRIVER_BASE<Pars...>
				   (mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
	{
	}

	void init(uint16_t scan_interval = 200) override
	{

		DMD_RGB_SPWM_DRIVER_BASE<Pars...>::init(scan_interval);

		uint16_t sm16380sh_conf[] = {
			0x021f, 0x0300, 0x0400, 0x0500, 0x0600, 0x0750, 0x0800, 0x0900, 0x0a02, 0x0b0c,
			0x0c08, 0x0d00, 0x0e05, 0x0f00, 0x1000, 0x1100, 0x1200, 0x1300, 0x1414, 0x1500,
			0x1630, 0x1700, 0x1801, 0x1904,
			0x1a03, 0x1b14, 0x1c12, 0x1d00, 0x1e00, 0x1f0c};

		sm16380sh_conf[0] = 0x200 | (this->nRows - 1); /// panel scan
		ADD_CONFIG_REGS(sm16380sh_conf);
		this->spwm_chip_init();
	}

protected:
	void load_config_regs(uint16_t *conf_reg) override
	{
		// send next config register in each call
		static uint8_t r = this->conf_reg_cnt;
		r++;
		if (r >= this->conf_reg_cnt)
		{

			r = 0;
		}

		this->send_vsync(); // vsync
		this->send_clocks(8);
		this->send_latches(11); // pre-active command
		this->send_clocks(8);
		this->send_latches(14); // pre-active command
		this->send_clocks(8);
		this->init_mux();
		pio_sm_set_enabled(this->pio, this->sm_clk_lat, false);
		
		// config and start clk_cnt SM
		this->start_DCLK();
		
		// in order to send config data we need 0x00AA 0x01AA before
		// and 0x0055,0x0155 after config value
		this->send_to_allRGB(0x00aa, 5);
		this->send_to_allRGB(0x01aa, 5);
		this->send_to_allRGB(conf_reg[r], 5); // send config register
		this->send_to_allRGB(0x0055, 5);
		this->send_to_allRGB(0x0155, 5);
	}
};

/*--------------------------------------------------------------------------------------*/
// FM6353 driver class
/*--------------------------------------------------------------------------------------*/
template<int... Pars> 
class DMD_RGB_FM6353 : public DMD_RGB_SPWM_DRIVER_BASE<Pars...>
{

public:
	DMD_RGB_FM6353(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
				   byte panelsWide, byte panelsHigh, bool d_buf = false) : 
				  DMD_RGB_SPWM_DRIVER_BASE<Pars...>
				   (mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
	{
	}

	void init(uint16_t scan_interval = 200) override
	{

		DMD_RGB_SPWM_DRIVER_BASE<Pars...>::init(scan_interval);
		
		this->clk_after_upload  = false;
		
		uint16_t conf_6353[] = {0x0008, 0x1f70, 0x6707, 0x40f7, 0x0040};

		// Config value for 4 latches depends on number of scans
		conf_6353[1] = ((this->nRows - 1) << 8) | (conf_6353[1] & 0xFF);
		ADD_CONFIG_REGS(conf_6353);
	}

protected:
	void load_config_regs(uint16_t *conf_reg) override
	{
		// send next config register in each call
		static uint8_t r = this->conf_reg_cnt;
		r++;
		if (r >= this->conf_reg_cnt)
		{

			r = 0;
		}

        this->send_latches(14); // pre-active command, 14 clks LAT pulses
		delayMicroseconds(1);
		this->send_latches(12); // enable all output, 12 clks LAT
		delayMicroseconds(1);
		this->send_vsync();		// vsync, 3 clks LAT
		delayMicroseconds(1);
		this->start_DCLK();
		this->send_latches(14);	
		delayMicroseconds(1);		
		pio_sm_set_enabled(this->pio, this->sm_clk_lat, false);			 
		
		// send one config register 
		this->send_to_allRGB(conf_reg[r], r * 2 + 2); 
}


    // load GCLK SM program instead of CLK_CNT prog
	void add_pio_prg3() override {
		this->pio_clkdiv = 1 + CYCLES_PER_MICROSECOND/(this->max_clk_freq * 2);
		this->sm_clk_cnt = pio_claim_unused_sm(this->pio, true);
		this->clk_cnt_prog_offs = pio_add_program(this->pio, &gclk_program);
		this->clk_cnt_pio_config = gclk_program_init(this->pio, this->sm_clk_cnt, this->clk_cnt_prog_offs, this->pio_clkdiv,
        this->pin_DMD_nOE);
	}
   
   
	void start_DCLK() override
	{
		// Start clock_counter SM
		dmd_out_program_reinit(this->pio, this->sm_clk_cnt, this->clk_cnt_prog_offs, &this->clk_cnt_pio_config);
        
		// Put a `control_par' parameter
		// Format of `control_par' parameter:
		// clock loop:
		// d1 OE pulses | IRQ | d2 idle pulses
		this->row = 1;
		uint32_t control_par = 0;
		uint16_t d1 = 138, d2 = 30;
		control_par = d2-1;
		control_par = (control_par << 16) | (d1-1);
		pio_sm_put_blocking(this->pio, this->sm_clk_cnt, control_par);
		this->oe_scan_flag = true;
	}
};


/*--------------------------------------------------------------------------------------*/
// FM6353 driver class
/*--------------------------------------------------------------------------------------*/
template <int ...Pars>
class DMD_RGB_FM6363 : public DMD_RGB_SPWM_DRIVER_BASE<Pars...>
{

public:
	DMD_RGB_FM6363(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
				   byte panelsWide, byte panelsHigh, bool d_buf = false) : 
				  DMD_RGB_SPWM_DRIVER_BASE<Pars...>
				   (mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
	{
	}

	void init(uint16_t scan_interval = 200) override
	{

		DMD_RGB_SPWM_DRIVER_BASE<Pars...>::init(scan_interval);
		
		this->clk_after_upload  = true;
		// MSB greyscale position for color bits
		this->gclk_bits = 13;
		
		uint16_t conf_6363[] = {0x7e08, 0x0fb0, 0xe6fc, 0x60b6,  0x5a70};

		// Config value for 4 latches depends on number of scans
		conf_6363[1] = ((this->nRows - 1) << 8) | (conf_6363[1] & 0xFF);
		ADD_CONFIG_REGS(conf_6363);
	}

protected:
	void load_config_regs(uint16_t *conf_reg) override
	{
		
        this->send_latches(14); // pre-active command, 14 clks LAT pulses
		delayMicroseconds(1);
		this->send_latches(12); // enable all output, 12 clks LAT
		delayMicroseconds(1);
		this->send_vsync();		// vsync, 3 clks LAT
		delayMicroseconds(1);
		
		// load all config registers 
		for (uint8_t r = 0; r < this->conf_reg_cnt; r++)
		{
			pio_sm_set_enabled(this->pio, this->sm_clk_lat, true);	
			this->send_latches(14);						  // pre-active command
			pio_sm_set_enabled(this->pio, this->sm_clk_lat, false);	
			this->send_to_allRGB(conf_reg[r], r * 2 + 2); // send config registers
			pio_sm_set_enabled(this->pio, this->sm_data, false);
		}
		this->start_DCLK();
		
}

 
    // load GCLK SM program instead of CLK_CNT prog
	void add_pio_prg3() override {
		this->pio_clkdiv = 1 + CYCLES_PER_MICROSECOND/(this->max_clk_freq * 2);
		this->sm_clk_cnt = pio_claim_unused_sm(this->pio, true);
		this->clk_cnt_prog_offs = pio_add_program(this->pio, &gclk_program);
		this->clk_cnt_pio_config = gclk_program_init(this->pio, this->sm_clk_cnt, this->clk_cnt_prog_offs, this->pio_clkdiv,
        this->pin_DMD_nOE);
	}
   
   
	void start_DCLK() override
	{
		// Start GCLK SM
		
		// Reinit CLK_CNT SM, but not enable it.
		// It will be enabled in data_transfer method 
		// to starts of DCLK and GCLK generation synchronicly
		 pio_sm_init(this->pio, this->sm_clk_cnt, this->clk_cnt_prog_offs, &this->clk_cnt_pio_config);
         pio_sm_exec(this->pio, this->sm_clk_cnt, this->clk_cnt_prog_offs);
		// Put a `control_par' parameter
		// Format of `control_par' parameter:
		// clock loop:
		// d1 OE pulses | IRQ | d2 idle pulses
		this->row = 1;
		uint32_t control_par = 0;
		uint16_t d1 = 74, d2 = 20;
		control_par = d2-1;
		control_par = (control_par << 16) | (d1-1);
		pio_sm_put_blocking(this->pio, this->sm_clk_cnt, control_par);
		this->oe_scan_flag = true;
	}
};

/*--------------------------------------------------------------------------------------*/
// ICN1065 driver class
/*--------------------------------------------------------------------------------------*/
template <int ...Pars>
class DMD_RGB_ICN1065 : public DMD_RGB_SPWM_DRIVER_BASE<Pars...>
{

public:
	DMD_RGB_ICN1065(uint8_t *mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t *pinlist,
					byte panelsWide, byte panelsHigh, bool d_buf = false) : 
					DMD_RGB_SPWM_DRIVER_BASE<Pars...>
					(mux_list, _pin_nOE, _pin_SCLK, pinlist, panelsWide, panelsHigh, d_buf)
	{
	}
	  // Fast text shift is disabled for complex patterns, so we don't need the method
  	void disableFastTextShift(bool shift) override {}

	void init(uint16_t scan_interval = 200) override
	{
		DMD_RGB_SPWM_DRIVER_BASE<Pars...>::init(scan_interval);
		this->fast_Hbyte = false;
    	this->use_shift = false;
		// MSB greyscale position for color bits
		this->gclk_bits = 12;
		
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
		// send next config register in each call
		static uint8_t r = this->conf_reg_cnt;
		r++;
		if (r >= this->conf_reg_cnt)
		{
			r = 0;
		}

		this->send_vsync(); // vsync
		this->send_clocks(8);
		this->send_latches(11); // pre-active command
		this->send_clocks(8);
		this->send_latches(14); // pre-active command
		this->send_clocks(8);
		this->init_mux();
		pio_sm_set_enabled(this->pio, this->sm_clk_lat, false);
		
		// config and start clk_cnt SM
		this->start_DCLK();
		
		// in order to send config data we need 0x00AA 0x01AA before
		// and 0x0055,0x0155 after config value
		this->send_to_allRGB(0x00aa, 5);
		this->send_to_allRGB(0x01aa, 5);
		this->send_to_allRGB(conf_reg[r], 5); // send config register
		this->send_to_allRGB(0x0055, 5);
		this->send_to_allRGB(0x0155, 5);
		
	}
};

#endif  // ARCH_RP2040
#endif
