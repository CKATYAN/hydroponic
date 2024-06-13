// libs:
#include "pico/stdlib.h"
// header files:
#include "simple_pins_handler.h"

void initialize_simple_input_pin_mask(uint32_t input_pin_mask) {
    for(uint i = 0; i < NUM_BANK0_GPIOS; i++) {
        if (input_pin_mask & 1) {
            gpio_init(i);
            gpio_set_dir(i, 0);
            gpio_pull_down(i);
        }
        input_pin_mask >>= 1;
    }
}

void initialize_simple_output_pin_mask(uint32_t output_pin_mask) {
    gpio_init_mask(output_pin_mask);
    gpio_set_dir_out_masked(output_pin_mask);
}

bool is_input_pin_active(uint8_t input_pin) {
    return gpio_get(input_pin);
}

void put_output_pin_value(uint8_t output_pin, bool value) {
    gpio_put(output_pin, value);
}