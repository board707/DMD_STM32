enum sm_pin_type {IN_PINS = 0, OUT_PINS, SET_PINS, SIDE_PINS }; 


#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ------------- //
// clock_latches //
// ------------- //

#define clock_latches_wrap_target 0
#define clock_latches_wrap 2

static const uint16_t clock_latches_program_instructions[] = {
            //     .wrap_target
    0x80a0, //  0: pull   block           side 0     
    0x6001, //  1: out    pins, 1         side 0     
    0x7167, //  2: out    null, 7         side 1 [1]     
            //     .wrap
    0xa042, //  3: nop                    side 0     
    0x1003, //  4: jmp    3               side 1  
};

#if !PICO_NO_HARDWARE
static const struct pio_program clock_latches_program = {
    .instructions = clock_latches_program_instructions,
    .length = 5,
    .origin = -1,
};

static inline pio_sm_config clock_latches_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + clock_latches_wrap_target, offset + clock_latches_wrap);
    sm_config_set_sideset(&c, 1, false, false);
    return c;
}

bool pio_sm_is_tx_fifo_stall(PIO pio, uint sm) {
    check_pio_param(pio);
    check_sm_param(sm);
    return ((pio->fdebug & (1u << (PIO_FDEBUG_TXSTALL_LSB + sm))) != 0);
}
void pio_sm_tx_fifo_stall_clear(PIO pio, uint sm) {
    pio->fdebug |= (1u << (PIO_FDEBUG_TXSTALL_LSB + sm)) ;
}

void sm_config_any_pins(PIO pio, uint sm, pio_sm_config *c, sm_pin_type pin_type, uint pin_base, uint pin_count) 
{
  if (! pin_count) return; 
  pio_sm_set_consecutive_pindirs(pio, sm, pin_base, pin_count, (pin_type != IN_PINS) );  
  for (uint i = 0; i < pin_count; i++) {pio_gpio_init(pio, pin_base + i);}
  switch(pin_type) 
  {
    case IN_PINS:
    sm_config_set_in_pins(c, pin_base);
    break;

    case OUT_PINS:
    sm_config_set_out_pins(c, pin_base, pin_count);
    break;

    case SET_PINS:
    sm_config_set_set_pins(c, pin_base, pin_count);
    break;

    case SIDE_PINS:
    sm_config_set_sideset_pins(c, pin_base);
    sm_config_set_sideset(c, pin_count, false, false);
    break;

    
  } 
  }

  static inline pio_sm_config clock_latches_prg_init(PIO pio, uint sm, uint offset, int clk_div,
                  uint out_pins_base,
                  uint side_pin_base) 
{
    pio_sm_config c = clock_latches_program_get_default_config(offset);
    sm_config_set_clkdiv(&c, clk_div);   
    
    
    // OUT pins
    sm_config_any_pins(pio, sm, &c, OUT_PINS, out_pins_base, 1);
    // SIDE pins
    sm_config_any_pins(pio, sm, &c, SIDE_PINS, side_pin_base, 1); 
    
   //rightshift = true, autopull = true, threshold = 8
    sm_config_set_out_shift(&c, true, false, 8); 
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_exec(pio, sm, offset );
    pio_sm_set_enabled(pio, sm, true);
    return c;
}          
#endif

// ------------ //
// dmd_out_spwm //
// ------------ //

#define dmd_out_spwm_wrap_target 0
#define dmd_out_spwm_wrap 11

static const uint16_t dmd_out_spwm_program_instructions[] = {
    //     .wrap_target
    0x80a0, //  0: pull   block           side 0     
    0x6030, //  1: out    x, 16           side 0     
    0x6050, //  2: out    y, 16           side 0     
    0x80a0, //  3: pull   block           side 0     
    0x6006, //  4: out    pins, 6         side 0     
    0x7162, //  5: out    null, 2         side 1 [1] 
    0x0088, //  6: jmp    y--, 8          side 0     
    0xe001, //  7: set    pins, 1         side 0     
    0x0043, //  8: jmp    x--, 3          side 0     
    0xe000, //  9: set    pins, 0         side 0     
    0xa003, // 10: mov    pins, null      side 0     
    0xc007, // 11: irq    nowait 7        side 0       

            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program dmd_out_spwm_program = {
    .instructions = dmd_out_spwm_program_instructions,
    .length = 12,
    .origin = -1,
};

static inline pio_sm_config dmd_out_spwm_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + dmd_out_spwm_wrap_target, offset + dmd_out_spwm_wrap);
    sm_config_set_sideset(&c, 1, false, false);
    return c;
}

static inline pio_sm_config dmd_out_spwm_program_init(PIO pio, uint sm, uint offset,
    int clk_div,
    int out_pins_base, int out_pins_cnt,
    int set_pin_base,
    int side_pin_base)
{
    
    pio_sm_config c = dmd_out_spwm_program_get_default_config(offset);
    sm_config_set_clkdiv(&c, clk_div);   
    
    
    // OUT pins
    sm_config_any_pins(pio, sm, &c, OUT_PINS, out_pins_base, out_pins_cnt);
    // SET pins
    sm_config_any_pins(pio, sm, &c, SET_PINS, set_pin_base, 1); 
    // SIDE pins
    sm_config_any_pins(pio, sm, &c, SIDE_PINS, side_pin_base, 1); 
    
   //rightshift = true, autopull = true, threshold = 8
    sm_config_set_out_shift(&c, true, false, 8); 
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_exec(pio, sm, offset );
    pio_sm_set_enabled(pio, sm, true);
    return c;

}

// ---------- //
// clock_cnt2 //
// ---------- //

#define clock_cnt2_wrap_target 2
#define clock_cnt2_wrap 10

static const uint16_t clock_cnt2_program_instructions[] = {
    0x80a0, //  0: pull   block                      
    0xa0c7, //  1: mov    isr, osr                   
            //     .wrap_target
    0xc000, //  2: irq    nowait 0                   
    0xe042, //  3: set    y, 2                       
    0x6028, //  4: out    x, 8                       
    0x6001, //  5: out    pins, 1                    
    0x2020, //  6: wait   0 pin, 0                   
    0x20a0, //  7: wait   1 pin, 0                   
    0x0046, //  8: jmp    x--, 6                     
    0x0084, //  9: jmp    y--, 4                     
    0xa0e6, // 10: mov    osr, isr                   
            //     .wrap
};


static const struct pio_program clock_cnt2_program = {
    .instructions = clock_cnt2_program_instructions,
    .length = 11,
    .origin = -1,
};

static inline pio_sm_config clock_cnt2_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + clock_cnt2_wrap_target, offset + clock_cnt2_wrap);
    return c;
}

static inline pio_sm_config dmd_clk_cnt_program_init(PIO pio, uint sm, uint offset,
    int clk_div,
    int in_pins_base,
    int out_pins_base
   )
{
    
    pio_sm_config c = clock_cnt2_program_get_default_config(offset);
    sm_config_set_clkdiv(&c, clk_div);   
    
    // IN pins
    sm_config_set_in_pins(&c, in_pins_base);
    // OUT pins
    sm_config_any_pins(pio, sm, &c, OUT_PINS, out_pins_base, 1);
    // SET pins
   // sm_config_any_pins(pio, sm, &c, SET_PINS, set_pin_base, 1); 
    // SIDE pins
   // sm_config_any_pins(pio, sm, &c, SIDE_PINS, side_pin_base, 1); 
    
   //rightshift = true, autopull = true, threshold = 8
    sm_config_set_out_shift(&c, true, false, 24); 
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_exec(pio, sm, offset );
   // pio_sm_set_enabled(pio, sm, true);
    return c;

}

// ---- //
// gclk //
// ---- //

#define gclk_wrap_target 2
#define gclk_wrap 9

static const uint16_t gclk_program_instructions[] = {
    0x80a0, //  0: pull   block           side 0     
    0xa0c7, //  1: mov    isr, osr        side 0     
            //     .wrap_target
    0x6030, //  2: out    x, 16           side 0     
    0xb042, //  3: nop                    side 1     
    0x0043, //  4: jmp    x--, 3          side 0     
    0xa142, //  5: nop                    side 0 [1] 
    0xc000, //  6: irq    nowait 0        side 0     
    0x6050, //  7: out    y, 16           side 0     
    0x0188, //  8: jmp    y--, 8          side 0 [1] 
    0xa0e6, //  9: mov    osr, isr        side 0
            //     .wrap
};


static const struct pio_program gclk_program = {
    .instructions = gclk_program_instructions,
    .length = 10,
    .origin = -1,
};

static inline pio_sm_config gclk_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + gclk_wrap_target, offset + gclk_wrap);
    sm_config_set_sideset(&c, 1, false, false);
    return c;
}

static inline pio_sm_config gclk_program_init(PIO pio, uint sm, uint offset,
    int clk_div,
    int side_pin_base
   )
{
    
    pio_sm_config c = gclk_program_get_default_config(offset);
    sm_config_set_clkdiv(&c, clk_div);   
    
   
    // OUT pins
   // sm_config_any_pins(pio, sm, &c, OUT_PINS, out_pins_base, 1);
    // SET pins
   // sm_config_any_pins(pio, sm, &c, SET_PINS, set_pin_base, 1); 
    // SIDE pins
    sm_config_any_pins(pio, sm, &c, SIDE_PINS, side_pin_base, 1); 
    
   //rightshift = true, autopull = true, threshold = 8
    sm_config_set_out_shift(&c, true, false, 24); 
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_exec(pio, sm, offset );
   // pio_sm_set_enabled(pio, sm, true);
    return c;

}

#endif