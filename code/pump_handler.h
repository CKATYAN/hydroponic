#ifndef PUMPS_HANDLER_
#define PUMPS_HANDLER_

void pump_pin_init_mask(int input_list, ...);

void pump_pin_put(uint pump_pin, bool value);

#endif