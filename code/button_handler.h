#ifndef BUTTON_HANDLER_
#define BUTTON_HANDLER_

void button_pin_init_mask(int input_list, ...);

bool is_button_pressed(uint button_pin);

#endif