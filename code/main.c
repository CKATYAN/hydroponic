// libs:
#include "pico/stdlib.h"  // need to remove, first remove sleep_ms by "interrupt_buttons"
// header files:
#include "simple_pins_handler.h"
#include "ssd1306_handler.h"

// signals:
// #define INPUT_REACTOR_READINESS 
// #define INPUT_GARDEN_1_SELECTED
// #define INPUT_GARDEN_2_SELECTED
// #define INPUT_GARDEN_3_SELECTED

// simple devices:
#define OUTPUT_REACTOR_TO_GARDEN_PUMP_1 1
#define OUTPUT_REACTOR_TO_GARDEN_PUMP_2 2
// #define OUTPUT_REACTOR_TO_GARDEN_PUMP_3 2
// #define OUTPUT_GARDEN_TO_JAR_PUMP

// ssd1306:
#define I2C_SDA_PIN 14
#define I2C_SCL_PIN 15

void init() {
    // init_simple_input_pin_mask(
    //     1ul << INPUT_REACTOR_READINESS |
    //     1ul << INPUT_GARDEN_1_SELECTED
    // );
    // init_simple_output_pin_mask(
    //     1ul << OUTPUT_REACTOR_TO_GARDEN_PUMP_1 |
    //     1ul << OUTPUT_REACTOR_TO_GARDEN_PUMP_2
    // );
    init_ssd1306(I2C_SDA_PIN, I2C_SCL_PIN);
}

int main() {
    init();

    while(1) {
        put_output_pin_value(OUTPUT_REACTOR_TO_GARDEN_PUMP_1, 1);
        put_output_pin_value(OUTPUT_REACTOR_TO_GARDEN_PUMP_2, 1);
    }
        
    // bool pump_1_work_state = 0;
    // bool pump_2_work_state = 0;

    // while(1) {
    //     if(is_input_pin_active(INPUT_GARDEN_1_SELECTED)) {
    //         pump_1_work_state = !pump_1_work_state;
    //         sleep_ms(200); // bad practice
    //     }
    //     if(is_input_pin_active(INPUT_GARDEN_2_SELECTED)) {
    //         pump_2_work_state = !pump_2_work_state;
    //         sleep_ms(200); // bad practice
    //     }

    //     put_output_pin_value(OUTPUT_REACTOR_TO_GARDEN_PUMP_1, pump_1_work_state);
    //     put_output_pin_value(OUTPUT_REACTOR_TO_GARDEN_PUMP_2, pump_2_work_state);
    // }
}