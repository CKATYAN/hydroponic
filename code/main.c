#include "pico/stdlib.h"
#include "pump/pump_handler.h"
#include "button/button_handler.h"

void initialization() {
    pump_initialization();
    button_initialization();
}

int main() {
    initialization();

    while(1) {
        while (!is_button_pressed(REACTOR_READINESS)) {
            sleep_ms(300);
        }
        pump_working_within_ms(PUMP_JAR_TO_REACTOR, 1000);

        if (is_button_pressed(GARDEN_1_SELECTED)) {
            pump_working_within_ms(PUMP_REACTOR_TO_GARDEN_1, 1000);
        }
        else if (is_button_pressed(GARDEN_2_SELECTED)) {
            pump_working_within_ms(PUMP_REACTOR_TO_GARDEN_2, 1000);
        }
        else if (is_button_pressed(GARDEN_3_SELECTED)) {
            pump_working_within_ms(PUMP_REACTOR_TO_GARDEN_3, 1000);
        }
    }
}