# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico2)
#set(PICO_PLATFORM host)

include(pico_sdk_import.cmake)

############################################################
# project specific / editable
project(s2-pico-logger C CXX ASM)
pico_sdk_init()

add_executable(s2-pico-logger
    src/io/led.c
    src/io/serialuart.c
    src/io/stdintoqueue.cpp
    src/time/strptime.c
    src/time/timestringgenerator.cpp
    src/time/timesync.cpp
    src/command.cpp
    src/commandparser.cpp
    src/logger.cpp
    src/lineextractor.cpp
    src/linefromqueue.cpp
    src/stringutils.cpp
    src/main.cpp
)

target_include_directories(s2-pico-logger
    PRIVATE
    src
    src/io
    src/time
)

target_link_libraries(s2-pico-logger
    PRIVATE
    pico_stdlib
    hardware_uart
    hardware_flash
    )

pico_enable_stdio_usb(s2-pico-logger TRUE)
pico_enable_stdio_uart(s2-pico-logger FALSE)
pico_add_extra_outputs(s2-pico-logger)

# memory used build output
add_custom_target(memory-usage SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/memory_usage.py) # just to display file
add_custom_command(TARGET s2-pico-logger POST_BUILD
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/memory_usage.py "${CMAKE_CURRENT_BINARY_DIR}/s2-pico-logger.elf.map"
)
