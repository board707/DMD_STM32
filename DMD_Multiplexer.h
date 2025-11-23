#ifndef DMD_Multiplexer_H
#define DMD_Multiplexer_H
#include "DMD_Defs.h"

enum MUX_TYPE { DMD_MUX_TYPE138= 0, DMD_MUX_TYPE_SHIFTREG = 1};
// Pure Virtual Base Multiplexer Class
class DMD_Multiplexer {
    protected:
    DMD_Pinlist* mux_pins;
    uint8_t n_Rows;   
   
    
#if (defined(__STM32F1__) || defined(__STM32F4__))
	
	// PORT register pointers 
	volatile PortType* muxsetreg;
#endif

public:
    MUX_TYPE mux_type;
    // Constructor with two parameters
    DMD_Multiplexer (DMD_Pinlist* _mux_pinlist, uint8_t n_Rows);
    
    virtual ~DMD_Multiplexer();

    virtual void init();
    void transfer_data(DMD_Multiplexer* src);
    
    virtual void set_mux(uint8_t curr_row)  = 0; // Pure virtual function
};
    
    // Derived Class A
    class DMD_Mux3to8 : public DMD_Multiplexer {
        private:
            uint32_t* mux_mask2;
            #if (defined(ARDUINO_ARCH_RP2040))
            PIO pio = pio0;
            uint8_t sm_mux = 1;
            #endif

         public:
             DMD_Mux3to8 (DMD_Pinlist* _mux_pinlist, uint8_t n_Rows);
            
             ~DMD_Mux3to8();
             void init() override;    
    // Implementing the pure virtual method
             void set_mux(uint8_t curr_row) override;
    };
    
    // Derived Class A
    class DMD_Mux595 : public DMD_Multiplexer {
        public:
            DMD_Mux595 (DMD_Pinlist* _mux_pinlist, uint8_t n_Rows);
            
            // void init() override;
            // Implementing the pure virtual method
            void set_mux(uint8_t curr_row) override;
        };

#endif