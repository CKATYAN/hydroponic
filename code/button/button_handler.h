#ifndef BUTTON_HANDLER_
#define BUTTON_HANDLER_

#define REACTOR_READINESS 5
#define GARDEN_1_SELECTED 6
#define GARDEN_2_SELECTED 7
#define GARDEN_3_SELECTED 8

void button_initialization();

bool is_button_pressed(uint button_pin);

#endif