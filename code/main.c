#include "pico/stdlib.h"

#include "hardware/pump/pump_handler.h"
#include "hardware/button/button_handler.h"

// #define INPUT_REACTOR_READINESS 
#define INPUT_GARDEN_1_SELECTED 7
#define INPUT_GARDEN_2_SELECTED 8
// #define INPUT_GARDEN_3_SELECTED 

#define OUTPUT_REACTOR_TO_GARDEN_PUMP_1 0
#define OUTPUT_REACTOR_TO_GARDEN_PUMP_2 1
// #define OUTPUT_REACTOR_TO_GARDEN_PUMP_3 2
// #define OUTPUT_GARDEN_TO_JAR_PUMP

void initialization() {
    button_pin_mask_initialization(
        1 << INPUT_GARDEN_1_SELECTED |
        1 << INPUT_GARDEN_2_SELECTED
    );
    pump_pin_mask_initialization(
        1 << OUTPUT_REACTOR_TO_GARDEN_PUMP_1 |
        1 << OUTPUT_REACTOR_TO_GARDEN_PUMP_2
    );
}

int main() {
    initialization();
        
    bool pump_1_work_state = 0;
    bool pump_2_work_state = 0;

    while(1) {
        if(is_button_pressed(INPUT_GARDEN_1_SELECTED)) {
            pump_1_work_state = !pump_1_work_state;
            sleep_ms(200);
        }
        if(is_button_pressed(INPUT_GARDEN_2_SELECTED)) {
            pump_2_work_state = !pump_2_work_state;
            sleep_ms(200);
        }

        pump_put(OUTPUT_REACTOR_TO_GARDEN_PUMP_1, pump_1_work_state);
        pump_put(OUTPUT_REACTOR_TO_GARDEN_PUMP_2, pump_2_work_state);
    }
}