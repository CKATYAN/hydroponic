#ifndef SIMPLE_PINS_HANDLER_H_
    #define SIMPLE_PINS_HANDLER_H_

    void initialize_simple_input_pin_mask(uint32_t input_pin_mask);
    void initialize_simple_output_pin_mask(uint32_t output_pin_mask);
    bool is_input_pin_active(uint8_t button_pin);
    void put_output_pin_value(uint8_t output_pin, bool value);
#endif