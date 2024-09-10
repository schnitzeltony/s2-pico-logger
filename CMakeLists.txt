# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
include(${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
# ====================================================================================

set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
include(${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico2 CACHE STRING "Board type")

include(pico_sdk_import.cmake)
project(s2-pico-logger C CXX ASM)
pico_sdk_init()

add_executable(s2-pico-logger
    src/led.c
    src/logtransform.cpp
    src/serialuart.c
    src/main.cpp
)

target_link_libraries(s2-pico-logger pico_stdlib hardware_uart)

pico_add_extra_outputs(s2-pico-logger)

# add url via pico_set_program_url
target_compile_definitions(s2-pico-logger PRIVATE PICO_UART_ENABLE_CRLF_SUPPORT=0)
