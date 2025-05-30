# The library (PROJECT_NAMWE = target-support)
project(target-support LANGUAGES C)

# Adding path for the library include directory
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Use the source files for the library
set(source_files
    debug/debug_io.c
    led/led.c
)

# We want a STATIC library (libtarget-support.a)
add_library(${PROJECT_NAME} STATIC ${source_files})

# Expose the include folder for the library
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_INCLUDE_DIR}
)

# This library has dependencies to NXP SDK drivers
target_link_libraries(${PROJECT_NAME}
    device-mkl25z4        # NXP SDK
    driver-mkl25z4        # NXP SDK drivers
)
