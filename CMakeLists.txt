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

############################################################
# project specific / editable
project(s2-pico-logger C CXX ASM)
pico_sdk_init()

add_executable(s2-pico-logger
    src/led.c
    src/logtransform.cpp
    src/serialuart.c
    src/stdintoqueue.cpp
    src/main.cpp
)

target_link_libraries(s2-pico-logger
    PRIVATE
    pico_stdlib
    hardware_uart
    hardware_flash
    )

pico_enable_stdio_usb(s2-pico-logger TRUE)
pico_add_extra_outputs(s2-pico-logger)

# adjustments
target_compile_definitions(s2-pico-logger PRIVATE PARAM_ASSERTIONS_ENABLE_ALL=1) # Not working - why ???
if(PICO_BOARD STREQUAL "pico2")
    # see https://github.com/oyama/pico-vfs/issues/57
    target_compile_definitions(s2-pico-logger PRIVATE PICO_FS_DEFAULT_SIZE=3145728)
endif()