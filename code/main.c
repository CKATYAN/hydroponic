// libs:
#include "pico/stdlib.h" // need to remove, first remove sleep_ms by "watcher"
// header files:
#include "pinout_handler.h"

// signals:
// #define INPUT_REACTOR_READINESS 
#define INPUT_GARDEN_1_SELECTED 7
#define INPUT_GARDEN_2_SELECTED 8
// #define INPUT_GARDEN_3_SELECTED 

// devices:
#define OUTPUT_REACTOR_TO_GARDEN_PUMP_1 0
#define OUTPUT_REACTOR_TO_GARDEN_PUMP_2 1
// #define OUTPUT_REACTOR_TO_GARDEN_PUMP_3 2
// #define OUTPUT_GARDEN_TO_JAR_PUMP

void init() {
    init_input_pin_list(
        INPUT_GARDEN_1_SELECTED, 
        INPUT_GARDEN_2_SELECTED
    );
    init_output_pin_list(
        OUTPUT_REACTOR_TO_GARDEN_PUMP_1,
        OUTPUT_REACTOR_TO_GARDEN_PUMP_2
    );
}

int main() {
    init();
        
    bool pump_1_work_state = 0;
    bool pump_2_work_state = 0;

    while(1) {
        if(is_input_pin_pressed(INPUT_GARDEN_1_SELECTED)) {
            pump_1_work_state = !pump_1_work_state;
            sleep_ms(200); // bad practice
        }
        if(is_input_pin_pressed(INPUT_GARDEN_2_SELECTED)) {
            pump_2_work_state = !pump_2_work_state;
            sleep_ms(200); // bad practice
        }

        put_output_pin(OUTPUT_REACTOR_TO_GARDEN_PUMP_1, pump_1_work_state);
        put_output_pin(OUTPUT_REACTOR_TO_GARDEN_PUMP_2, pump_2_work_state);
    }
}