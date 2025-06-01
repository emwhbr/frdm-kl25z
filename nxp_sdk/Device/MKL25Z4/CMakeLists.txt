# The library (PROJECT_NAMWE = device-mkl25z4)
project(device-mkl25z4 LANGUAGES C ASM)

# Using C11 here, to avoid compile error: 
# ISO C99 doesn't support unnamed structs/unions [-Werror=pedantic]
set(CMAKE_C_STANDARD 11)

# Adding path for the library include directory
set(PROJECT_INCLUDE_DIR
   ${CMAKE_CURRENT_SOURCE_DIR}/gcc
)

# Add preprocessor definitions when compiling source files in this project.
# We need to set definitions to signal a customized start.
add_compile_definitions(__CUSTOM_START=1 __STARTUP_CLEAR_BSS=1)

# Use the source files for the library
set(source_files
    system_MKL25Z4.c
    gcc/startup_MKL25Z4.S
)

# We want a STATIC library (device-mkl25z4.a)
add_library(${PROJECT_NAME} STATIC ${source_files})

# Expose the include folder for the library
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# This library has dependencies to other parts of NXP SDK(CMSIS-Core)
target_link_libraries(${PROJECT_NAME}
    CMSIS-Core            # CMSIS-Core
    hw-api                # Hardware layer
)
