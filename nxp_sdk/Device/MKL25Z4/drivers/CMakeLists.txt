# The library (PROJECT_NAMWE = driver-mkl25z4)
project(driver-mkl25z4 LANGUAGES C)

# Using ISO C99 here
set(CMAKE_C_STANDARD 99)

# Use the source files for the library
set(source_files
    fsl_adc16.c
    fsl_clock.c
    fsl_cmp.c
#    fsl_common.c
    fsl_cop.c
    fsl_dac.c
    fsl_dma.c
    fsl_dmamux.c
    fsl_flash.c
    fsl_gpio.c
    fsl_i2c_dma.c
#    fsl_i2c_freertos.c
    fsl_i2c.c
    fsl_llwu.c
    fsl_lpsci_dma.c
#   fsl_lpsci_freertos.c
    fsl_lpsci.c
    fsl_lptmr.c
    fsl_pit.c
    fsl_pmc.c
    fsl_rcm.c
    fsl_rtc.c
    fsl_sim.c
    fsl_smc.c
    fsl_spi_dma.c
#    fsl_spi_freertos.c
    fsl_spi.c
    fsl_tpm.c
    fsl_tsi_v4.c
    fsl_uart_dma.c
#    fsl_uart_freertos.c
    fsl_uart.c
)

# Inhibit all warning messages for NXP SDK files.
# There are a lot of compiler warnings accoring to:
# error: conversion from 'unsigned int' to 'uint8_t' {aka 'unsigned char'} changes the value of xxx [-Werror=conversion]
# Probably because we are using a newer and more picky GCC.
# We are lazy and can't fix everything, so supressing all warning for these files is enough.
set_source_files_properties(
    ${source_files}
    PROPERTIES APPEND_STRING PROPERTY COMPILE_FLAGS " -w"
)

# We want a STATIC library (libdriver-mkl25z4.a)
add_library(${PROJECT_NAME} STATIC ${source_files})

# Expose the include folder for the library
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# This library has dependencies to other parts of NXP SDK
target_link_libraries(${PROJECT_NAME}
    device-mkl25z4            # Device specific
)
