#include "DMD_Multiplexer.h"

//#if (defined(ARDUINO_ARCH_RP2040))
// short delay for tune MUX595 CLK pulse
static inline __attribute__((always_inline)) void busyWaitDelay(volatile uint32_t cycles) {
    while (cycles--) {
        __asm volatile ("nop");  // No-operation instruction
    }
}
//#endif

DMD_Multiplexer::DMD_Multiplexer (DMD_Pinlist* _mux_pinlist, uint8_t n_Rows) : 
mux_pins(_mux_pinlist), n_Rows(n_Rows) { } 


DMD_Multiplexer::~DMD_Multiplexer() {
    free(mux_pins);
}

void DMD_Multiplexer::init() {
#if (defined(__STM32F1__) || defined(__STM32F4__))
	muxsetreg = portSetRegister(mux_pins->list[0]);
#endif
    for (uint8_t i = 0; i < mux_pins->count; i++) {
        pinMode(mux_pins->list[i], OUTPUT);
        digitalWrite(mux_pins->list[i], LOW);
    }
}

void DMD_Multiplexer::transfer_data(DMD_Multiplexer* src) {
	this -> mux_pins = src -> mux_pins;
	this -> n_Rows = src -> n_Rows;
	src -> mux_pins = nullptr;
	src -> n_Rows = 0;
}

/*****************************************************************/
DMD_Mux3to8::DMD_Mux3to8 (DMD_Pinlist* _mux_pinlist, uint8_t n_Rows) : DMD_Multiplexer(_mux_pinlist, n_Rows)
 {
	mux_type = DMD_MUX_TYPE138;
 }


DMD_Mux3to8::~DMD_Mux3to8() {
    free(mux_mask2);
}

void DMD_Mux3to8::init() {
    DMD_Multiplexer::init();
    mux_mask2 = (uint32_t*)malloc((n_Rows + 1) * 4);
/*--------------------------------------------------------------------------------------*/
#if (defined(__STM32F1__) || defined(__STM32F4__))


#define set_mux_ch_by_mask(x)  ((uint32_t) x)
#define clr_mux_ch_by_mask(x)  (((uint32_t)x) << 16)

	for (uint8_t i = 0; i < n_Rows; i++)
	{
		mux_mask2[i] = 0;
		if (mux_pins->count == n_Rows)                // DIRECT MUX
		{
			for (uint8_t j = 0; j < n_Rows; j++)
			{
				uint16_t mux_ch_mask = digitalPinToBitMask(mux_pins->list[j]);
				// set selected channel to LOW, all other to HIGH
				if (i == j)
				{
					mux_mask2[i] |= clr_mux_ch_by_mask(mux_ch_mask);    //low
				}
				else
				{
					mux_mask2[i] |= set_mux_ch_by_mask(mux_ch_mask);    //high
				}
			}
		}
		else {                             // BINARY MUX
			for (uint8_t j = 0; (1 << j) < n_Rows; j++)
			{
				uint16_t mux_ch_mask = digitalPinToBitMask(mux_pins->list[j]);
				if (i & (1 << j))
				{
					mux_mask2[i] |= set_mux_ch_by_mask(mux_ch_mask);
				}
				else
				{
					mux_mask2[i] |= clr_mux_ch_by_mask(mux_ch_mask);
				}
			}
		}
	}
	mux_mask2[n_Rows] = mux_mask2[0];


/*--------------------------------------------------------------------------------------*/
#elif (defined(ARDUINO_ARCH_RP2040))


	for (uint8_t i = 0; i < n_Rows; i++)
		{		
		if (mux_pins->count == n_Rows)                // DIRECT MUX
			// set selected channel to LOW, all other to HIGH
			{
			mux_mask2[i] = ((1 << n_Rows) - 1) & (~(1 << i));
			}
		else {                             // BINARY MUX
			mux_mask2[i] = i;
			}
		}
	mux_mask2[n_Rows] = mux_mask2[0];

	sm_mux = pio_claim_unused_sm(pio, true);
	//uint8_t data_mux_offs = pio_add_program(pio, &dmd_mux_program);
	uint8_t data_mux_offs = pio_add_dmd_mux_program(pio, this->mux_pins->count);
	dmd_mux_program_init(pio, sm_mux, data_mux_offs,this->mux_pins->list[0], this->mux_pins->count);

#endif

}

void DMD_Mux3to8::set_mux(uint8_t curr_row) {
#if (defined(__STM32F1__) || defined(__STM32F4__))
    *muxsetreg = mux_mask2[curr_row];
#elif (defined(ARDUINO_ARCH_RP2040))
    pio_sm_put_blocking(pio, sm_mux, mux_mask2[curr_row]);
#endif
}


DMD_Mux595::DMD_Mux595 (DMD_Pinlist* _mux_pinlist, uint8_t n_Rows) : DMD_Multiplexer(_mux_pinlist, n_Rows)
{
	mux_type = DMD_MUX_TYPE_SHIFTREG;
}



void DMD_Mux595::set_mux(uint8_t new_row)  {
	static uint8_t last_row = n_Rows;
#if (defined(__STM32F1__) || defined(__STM32F4__))
const uint32_t mux_clk_mask = digitalPinToBitMask(this->mux_pins->list[0]);   //this->mux_pins->list[0]
const uint32_t mux_lat_mask = digitalPinToBitMask(this->mux_pins->list[1]);  
const uint32_t mux_sdi_mask = digitalPinToBitMask(this->mux_pins->list[2]);  
if (new_row != last_row) {
	*this->muxsetreg = mux_lat_mask;   // LAT - HIGH
	if (new_row == 0) {
		*this->muxsetreg =  mux_sdi_mask;	
	}	
	else {
		*this->muxsetreg = (mux_sdi_mask << 16);			
	}
	busyWaitDelay(1);
	*this->muxsetreg = mux_clk_mask ;
	busyWaitDelay(1);
	*this->muxsetreg = (mux_clk_mask  << 16);
	*this->muxsetreg = (mux_lat_mask  << 16); // LAT - LOW
	last_row = new_row;
}
#elif (defined(ARDUINO_ARCH_RP2040))

// Add extra delay to avoid flickering
#if (CYCLES_PER_MICROSECOND > 133)
#define MUX595_DELAY 2
#else
#define MUX595_DELAY 1
#endif

	const byte pin_DMD_A = this->mux_pins->list[0];
	const byte pin_DMD_B = this->mux_pins->list[1];
	const byte pin_DMD_C = this->mux_pins->list[2];
    // Just shift the row mux by one for incremental access
	if (new_row != last_row) {
		gpio_put(pin_DMD_B, HIGH);  // LAT - HIGH
		gpio_put(pin_DMD_C, (new_row == 0));
		busyWaitDelay(MUX595_DELAY); 	// hold SDI before CLK
		gpio_put(pin_DMD_A, HIGH); 		// Clock out this bit
		busyWaitDelay(2*MUX595_DELAY);	// hold CLK HIGH
		gpio_put(pin_DMD_A, LOW);	
		gpio_put(pin_DMD_B, LOW);  // LAT - LOW 
		last_row = new_row;
	}
 #endif  
    
}
		
		
		/*if (new_row < last_row) {
            digitalWrite(pin_DMD_C, LOW); // Shift out 0 
			for (uint8_t i = 0; i < (n_Rows - last_row ); i++) {
				
				digitalWrite(pin_DMD_A, HIGH); // Clock out this bit
				digitalWrite(pin_DMD_A, LOW);
			}
			digitalWrite(pin_DMD_C, 1); // Shift out 1 for line 0
			digitalWrite(pin_DMD_A, HIGH); // Clock out this bit
			digitalWrite(pin_DMD_A, LOW);	
			last_row =0;
			
		}
		digitalWrite(pin_DMD_C, LOW); 
		for (uint8_t i = 0; i < (new_row - last_row ); i++) {
				
			digitalWrite(pin_DMD_A, HIGH); // Clock out this bit
			digitalWrite(pin_DMD_A, LOW);
		}
		
		*/
		
	


