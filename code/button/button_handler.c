#include "pico/stdlib.h"
#include "button_handler.h"

void button_initialization() {
    int pin_array[] = {
        REACTOR_READINESS,
        GARDEN_1_SELECTED,
        GARDEN_2_SELECTED,
        GARDEN_3_SELECTED
    };
    
    int array_size = sizeof(pin_array)/sizeof(pin_array[0]);
    for (size_t i = 0; i < array_size; i++) {
        gpio_init(pin_array[i]);
        gpio_set_dir(pin_array[i], GPIO_IN);
        gpio_pull_down(pin_array[i]);
    }
}

bool is_button_pressed(uint button_pin) {
    if (!gpio_get(button_pin)) {
        return 0;
    }
    return 1;
}