#include "pico/stdlib.h"

#include "pump_handler.h"

void pump_pin_mask_initialization(uint pin_mask) {
    gpio_init_mask(pin_mask);
    gpio_set_dir_out_masked(pin_mask);
}

void pump_put(uint pump_pin, bool value) {
    gpio_put(pump_pin, value);
}