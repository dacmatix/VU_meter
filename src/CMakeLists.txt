cmake_minimum_required(VERSION 3.12)

# Default SDK path to submodule location if not set via environment
if (NOT PICO_SDK_PATH AND NOT DEFINED ENV{PICO_SDK_PATH})
    set(PICO_SDK_PATH ${CMAKE_CURRENT_LIST_DIR}/../pico-sdk)
endif()

# Pull in PICO SDK (must be before project)
include(../pico_sdk_import.cmake)

# Set the project name and specify the target
project(vu_meter C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

add_executable(vu_meter
    vu_meter.c
    bitmap.c
    display.c
    font.c
    needle_coordinates.c
    needle_sprite.c
    oled.c
    progmem_image_sprite.c
    watermark.c
    i2c_driver.c
    watermark.c
    background.c
    peak_indicator.c
    splash.c
    main.c
)

# Include any directories with additional headers
target_include_directories(vu_meter PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link the Pico SDK libraries
target_link_libraries(vu_meter
    pico_stdlib
    pico_unique_id
    hardware_i2c
    hardware_gpio
    hardware_timer
)

# Enable USB output, disable UART output
pico_enable_stdio_usb(vu_meter 1)
pico_enable_stdio_uart(vu_meter 0)

# Create map/bin/hex/uf2 file on project (optional)
pico_add_extra_outputs(vu_meter)

target_compile_definitions(vu_meter PRIVATE
    AUDIO_FREQ_MAX=48000
)

# # Specify the source file you want to copy
set(TARGET_UF2_FILE "${CMAKE_CURRENT_LIST_DIR}/../build-rp2350/vu_meter.uf2")

# # Copy uf2 file to root folder
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${TARGET_UF2_FILE} ${CMAKE_CURRENT_LIST_DIR}/..
    COMMENT "Copying uf2 file ${TARGET_UF2_FILE} to ${CMAKE_CURRENT_LIST_DIR}/.."
)