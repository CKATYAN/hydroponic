#ifndef SIMPLE_PINS_HANDLER_H_
    #define SIMPLE_PINS_HANDLER_H_
    
    void init_simple_input_pin_list(int input_list, ...);
    void init_simple_output_pin_list(int input_list, ...);
    bool is_input_pin_pressed(uint button_pin);
    void put_output_pin_value(uint pump_pin, bool value);
#endif