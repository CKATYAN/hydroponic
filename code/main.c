#include "pico/stdlib.h"

#include "hardware/hardware_pinout.h"
#include "hardware/pump/pump_handler.h"
#include "hardware/button/button_handler.h"

void initialization() {
    pump_initialization();
    button_initialization();
}

int main() {
    initialization();

    bool is_pump_1_working = 0;
    bool is_pump_2_working = 0;
    
    while(1) {
        if (is_button_pressed(INPUT_GARDEN_1_SELECTED)) {
            is_pump_1_working = !is_pump_1_working;
            sleep_ms(250);
        }
        if (is_button_pressed(INPUT_GARDEN_2_SELECTED)) {
            is_pump_2_working = !is_pump_2_working;
            sleep_ms(250);
        }

        pump_put(OUTPUT_REACTOR_TO_GARDEN_PUMP_1, is_pump_1_working);
        pump_put(OUTPUT_REACTOR_TO_GARDEN_PUMP_2, is_pump_2_working);
    }
}