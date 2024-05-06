#include "pico/stdlib.h"
#include "stdarg.h" // https://www.geeksforgeeks.org/variadic-functions-in-c/

#include "pinout_handler.h"

uint32_t get_mask(int input_list, ...) {
    uint32_t mask = 0;

    va_list ptr;
    va_start(ptr, input_list);
    for (int i = 0; i < input_list; i++) {
        mask |= 1 << va_arg(ptr, int);
    }
    va_end(ptr);

    return mask;
}

void init_input_pin_list(int input_list, ...) {
    uint32_t pin_mask = get_mask(input_list);

    gpio_init_mask(pin_mask);
    gpio_set_dir_in_masked(pin_mask);
    gpio_pull_down(pin_mask);
}

void init_output_pin_list(int input_list, ...) {
    uint32_t pin_mask = get_mask(input_list);
    
    gpio_init_mask(pin_mask);
    gpio_set_dir_out_masked(pin_mask);
}

bool is_input_pin_pressed(uint button_pin) {
    return gpio_get(button_pin);
}

void put_output_pin(uint pump_pin, bool value) {
    gpio_put(pump_pin, value);
}