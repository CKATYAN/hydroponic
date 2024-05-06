#include "pico/stdlib.h"
#include "stdarg.h" // https://www.geeksforgeeks.org/variadic-functions-in-c/

#include "button_handler.h"

void button_pin_init_mask(int input_list, ...) {
    uint32_t pin_mask;

    va_list ptr;
    va_start(ptr, input_list);
    for (int i = 0; i < input_list; i++) {
        pin_mask |= 1 << va_arg(ptr, int);
    }

    gpio_init_mask(pin_mask);
    gpio_set_dir_in_masked(pin_mask);
    gpio_pull_down(pin_mask);
}

bool is_button_pressed(uint button_pin) {
    return gpio_get(button_pin);
}