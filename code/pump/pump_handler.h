#ifndef PUMPS_HANDLER_
#define PUMPS_HANDLER_

#define PUMP_JAR_TO_REACTOR 1
#define PUMP_REACTOR_TO_GARDEN_1 2 
#define PUMP_REACTOR_TO_GARDEN_2 3
#define PUMP_REACTOR_TO_GARDEN_3 4

void pump_initialization();

void pump_working_within_ms(uint pump_pin, uint32_t ms);

#endif