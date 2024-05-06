#ifndef BUTTON_HANDLER_
    #define BUTTON_HANDLER_

    uint32_t get_mask(int input_list, ...);
    void init_input_pin_list(int input_list, ...);
    void init_output_pin_list(int input_list, ...);
    bool is_input_pin_pressed(uint button_pin);
    void put_output_pin(uint pump_pin, bool value);
    
#endif