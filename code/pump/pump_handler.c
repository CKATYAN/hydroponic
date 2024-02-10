#include "pico/stdlib.h"
#include "pump_handler.h"

void pump_initialization() {
    int pin_array[] = {
        PUMP_JAR_TO_REACTOR,
        PUMP_REACTOR_TO_GARDEN_1,
        PUMP_REACTOR_TO_GARDEN_2,
        PUMP_REACTOR_TO_GARDEN_3
    };
    
    int array_size = sizeof(pin_array)/sizeof(pin_array[0]);
    for (size_t i = 0; i < array_size; i++) {
        gpio_init(pin_array[i]);
        gpio_set_dir(pin_array[i], GPIO_OUT);
    }
}

void pump_working_within_ms(uint pump_pin, uint32_t ms) {
    gpio_put(pump_pin, 1);
    sleep_ms(ms);
    gpio_put(pump_pin, 0);
}