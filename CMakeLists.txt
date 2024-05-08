cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(pico-projects)

pico_sdk_init()

add_executable(hydroponic
    code/main.c
    code/simple_pins_handler.c
    code/ssd1306_handler.c
)

target_link_libraries(hydroponic 
    pico_stdlib
    hardware_i2c
)

pico_add_extra_outputs(hydroponic)