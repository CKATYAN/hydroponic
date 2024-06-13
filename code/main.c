// libs:
#include "pico/stdlib.h"
#include "hardware/rtc.h"
#include <stdio.h>
// header files:
#include "simple_pins_handler.h"
#include "ssd1306_handler.h"

// signals:
// #define INPUT_REACTOR_READINESS 26
// #define INPUT_GARDEN_1_SELECTED 27
// #define INPUT_GARDEN_2_SELECTED 28
// #define INPUT_GARDEN_3_SELECTED 29

// simple devices:

#define OUTPUT_REACTOR_TO_GARDEN_PUMP_1 0
#define OUTPUT_REACTOR_TO_GARDEN_PUMP_2 1
#define OUTPUT_REACTOR_TO_GARDEN_PUMP_3 2

// ssd1306:
#define I2C_SDA_PIN 14
#define I2C_SCL_PIN 15

// other:
#define PERIOD_SEC 20

void control_pumps(uint8_t pump_number);

void initialize() {
    // initialize_simple_input_pin_mask(
    //     1ul << INPUT_GARDEN_1_SELECTED |
    //     1ul << INPUT_GARDEN_2_SELECTED
    // );

    initialize_simple_output_pin_mask(
        1ul << OUTPUT_REACTOR_TO_GARDEN_PUMP_1 |
        1ul << OUTPUT_REACTOR_TO_GARDEN_PUMP_2 |
        1ul << OUTPUT_REACTOR_TO_GARDEN_PUMP_3
    );
    
    // gpio_set_irq_enabled_with_callback(INPUT_REACTOR_READINESS, GPIO_IRQ_EDGE_RISE, 1, &callback);
    // gpio_set_irq_enabled_with_callback(INPUT_GARDEN_1_SELECTED, GPIO_IRQ_EDGE_RISE, 1, &callback);
    SSD1306_initialize(I2C_SDA_PIN, I2C_SCL_PIN);

    datetime_t t = {
        .year  = 2024,
        .month = 06,
        .day   = 25,
        .dotw  = 2, // 0 is Sunday, so 3 is Wednesday
        .hour  = 00,
        .min   = 00,
        .sec   = 00
    };
    rtc_init();
    rtc_set_datetime(&t);
    sleep_ms(64); // wait for updating new datetime
}

int main() {
    initialize();

    datetime_t t;
    char buffer[128];
    uint8_t pump_number = 1;

    while(true) {
        SSD1306_clear_memory();

        rtc_get_datetime(&t);
        for(int i = 1; i <= 3; i++) {
            if(i == pump_number) {
                sprintf(buffer, "pump %d: on for %d sec", i, (60 + (i * PERIOD_SEC - t.sec)) % 60);
            } else {
                sprintf(buffer, "pump %d: off for %d sec", i, (60 + ((i-1) * PERIOD_SEC - t.sec)) % 60);
            }
            SDD1306_write_line(buffer);
        }
        control_pumps(pump_number);

        if(!(t.sec % PERIOD_SEC)) {
            pump_number %= 3;
            pump_number++;
        }
        sleep_ms(1000);
    }
}

void control_pumps(uint8_t pump_number) {
    if(pump_number == 1) {
        put_output_pin_value(OUTPUT_REACTOR_TO_GARDEN_PUMP_3, 0);
        put_output_pin_value(OUTPUT_REACTOR_TO_GARDEN_PUMP_1, 1);
    } else if (pump_number == 2) {
        put_output_pin_value(OUTPUT_REACTOR_TO_GARDEN_PUMP_1, 0);
        put_output_pin_value(OUTPUT_REACTOR_TO_GARDEN_PUMP_2, 1);
    } else if (pump_number == 3) {
        put_output_pin_value(OUTPUT_REACTOR_TO_GARDEN_PUMP_2, 0);
        put_output_pin_value(OUTPUT_REACTOR_TO_GARDEN_PUMP_3, 1);
    }
}