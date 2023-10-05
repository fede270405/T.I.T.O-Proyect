cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

include(pico_extras_import_optional.cmake)

project(T.I.T.O-Proyect C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_BOARD pico_w)


# Initialize the SDK
pico_sdk_init()


add_compile_options(-Wall
    -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
    -Wno-unused-function # we have some for the docs that aren't called
    -Wno-maybe-uninitialized
)

add_executable(T.I.T.O-Proyect
    main.c
    ./NeoPixel/NeoPixel.c
    ./kiss_FFT/kiss_fft.c
    FileSystem.c
    LCD.c
)

add_subdirectory(./FatFs_SPI build)

target_compile_definitions(T.I.T.O-Proyect PRIVATE
        WIFI_SSID=\"Fede2704\"
        WIFI_PASSWORD=\"fede2704\"
        )
target_include_directories(T.I.T.O-Proyect PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
        )

target_link_libraries(T.I.T.O-Proyect 
                        
                        
                        pico_cyw43_arch_lwip_poll
                        pico_stdlib
                        hardware_pwm hardware_spi hardware_dma hardware_adc hardware_i2c
                        cmsis_core FatFs_SPI)
# enable usb output, disable uart output
pico_enable_stdio_usb(T.I.T.O-Proyect 0)
pico_enable_stdio_uart(T.I.T.O-Proyect 1)



# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(T.I.T.O-Proyect)

######

