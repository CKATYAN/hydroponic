#include "pico/stdlib.h"

#include "../hardware_pinout.h"
#include "button_handler.h"

void button_initialization() {
    uint pin_mask = (
        1 << INPUT_GARDEN_1_SELECTED |
        1 << INPUT_GARDEN_2_SELECTED
    );
    
    gpio_init_mask(pin_mask);
    gpio_set_dir_in_masked(pin_mask);
    gpio_pull_down(pin_mask);
}

bool is_button_pressed(uint button_pin) {
    return gpio_get(button_pin);
}