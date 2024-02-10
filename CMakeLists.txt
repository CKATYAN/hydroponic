cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(pico-projects)

pico_sdk_init()

add_executable(hydroponic
    code/main.c
    code/pump/pump_handler.c
    code/pump/pump_handler.h
    code/button/button_handler.c
    code/button/button_handler.h
)

target_link_libraries(hydroponic pico_stdlib)

pico_add_extra_outputs(hydroponic)