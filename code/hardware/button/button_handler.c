#include "pico/stdlib.h"

#include "button_handler.h"

void button_pin_mask_initialization(uint pin_mask) {
    gpio_init_mask(pin_mask);
    gpio_set_dir_in_masked(pin_mask);
    gpio_pull_down(pin_mask);
}

bool is_button_pressed(uint button_pin) {
    return gpio_get(button_pin);
}