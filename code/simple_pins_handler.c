// libs:
#include "pico/stdlib.h"
// header files:
#include "simple_pins_handler.h"

void initialize_simple_input_pin_mask(uint32_t input_pin_mask) {
    gpio_init_mask(input_pin_mask);
    gpio_set_dir_in_masked(input_pin_mask);
    gpio_pull_down(input_pin_mask);
}

void initialize_simple_output_pin_mask(uint32_t output_pin_mask) {
    gpio_init_mask(output_pin_mask);
    gpio_set_dir_out_masked(output_pin_mask);
}

bool is_input_pin_active(uint input_pin) {
    return gpio_get(input_pin);
}

void put_output_pin_value(uint output_pin, bool value) {
    gpio_put(output_pin, value);
}