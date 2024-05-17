// libs:
#include "pico/stdlib.h"  // need to remove, first remove sleep_ms by "watcher"
// header files:
#include "simple_pins_handler.h"
#include "ssd1306_handler.h"

// signals:
// #define INPUT_REACTOR_READINESS 
#define INPUT_GARDEN_1_SELECTED 7
#define INPUT_GARDEN_2_SELECTED 8
// #define INPUT_GARDEN_3_SELECTED 

// simple devices:
#define OUTPUT_REACTOR_TO_GARDEN_PUMP_1 0
#define OUTPUT_REACTOR_TO_GARDEN_PUMP_2 1
// #define OUTPUT_REACTOR_TO_GARDEN_PUMP_3 2
// #define OUTPUT_GARDEN_TO_JAR_PUMP

// ssd1306:
#define PICO_DEFAULT_I2C_SDA_PIN 4
#define PICO_DEFAULT_I2C_SCL_PIN 5

void init() {
    init_simple_input_pin_list(
        INPUT_GARDEN_1_SELECTED, 
        INPUT_GARDEN_2_SELECTED
    );
    init_simple_output_pin_list(
        OUTPUT_REACTOR_TO_GARDEN_PUMP_1,
        OUTPUT_REACTOR_TO_GARDEN_PUMP_2
    );
    init_ssd1306(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN);
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

        put_output_pin_value(OUTPUT_REACTOR_TO_GARDEN_PUMP_1, pump_1_work_state);
        put_output_pin_value(OUTPUT_REACTOR_TO_GARDEN_PUMP_2, pump_2_work_state);
    }
}