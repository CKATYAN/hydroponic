#include "pico/stdlib.h"

#include "../hardware_pinout.h"
#include "pump_handler.h"

void pump_initialization() {
    uint pin_mask = (
        1 << OUTPUT_REACTOR_TO_GARDEN_PUMP_1 |
        1 << OUTPUT_REACTOR_TO_GARDEN_PUMP_2
    );
    
    gpio_init_mask(pin_mask);
    gpio_set_dir_out_masked(pin_mask);
}

void pump_put(uint pump_pin, bool value) {
    gpio_put(pump_pin, value);
}