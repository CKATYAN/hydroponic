#include "pico/stdlib.h"
#include "stdarg.h" // https://www.geeksforgeeks.org/variadic-functions-in-c/

#include "pump_handler.h"

void pump_pin_init_mask(uint input_list, ...) {
    uint pin_mask;

    va_list ptr;
    va_start(ptr, input_list);
    for (int i = 0; i < input_list; i++) {
        pin_mask |= 1 << va_arg(ptr, int);
    }

    gpio_init_mask(pin_mask);
    gpio_set_dir_out_masked(pin_mask);
}

void pump_put(uint pump_pin, bool value) {
    gpio_put(pump_pin, value);
}