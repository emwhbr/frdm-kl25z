# Define "Generic" type for the build generator to use cross-compilation
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_SYSTEM_NAME Generic)

set(TOOLCHAIN_PREFIX arm-none-eabi-)

set(CMAKE_C_COMPILER   ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_AR           ${TOOLCHAIN_PREFIX}ar)
set(CMAKE_OBJCOPY      ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_ELFSIZE      "${TOOLCHAIN_PREFIX}size" "--format=berkeley" CACHE INTERNAL "")

# Using C11
set(CMAKE_C_STANDARD 11)

# Using -std=c++14
set(CMAKE_CXX_STANDARD 14)

# Apply strict compiler flags
add_compile_options(-Werror -Wall -Wextra -Wconversion -Wpedantic)

# NXP MCU architecture specific compiler options
set(MKL25Z128_FLAGS "${MKL25Z128_FLAGS} -mcpu=cortex-m0plus")
set(MKL25Z128_FLAGS "${MKL25Z128_FLAGS} -mfloat-abi=soft")
set(MKL25Z128_FLAGS "${MKL25Z128_FLAGS} -mthumb")
set(MKL25Z128_FLAGS "${MKL25Z128_FLAGS} -MMD")
set(MKL25Z128_FLAGS "${MKL25Z128_FLAGS} -MP")
set(MKL25Z128_FLAGS "${MKL25Z128_FLAGS} -fno-common")
set(MKL25Z128_FLAGS "${MKL25Z128_FLAGS} -ffunction-sections")
set(MKL25Z128_FLAGS "${MKL25Z128_FLAGS} -fdata-sections")
set(MKL25Z128_FLAGS "${MKL25Z128_FLAGS} -ffreestanding")
set(MKL25Z128_FLAGS "${MKL25Z128_FLAGS} -fno-builtin")
set(MKL25Z128_FLAGS "${MKL25Z128_FLAGS} -mapcs")
set(MKL25Z128_FLAGS "${MKL25Z128_FLAGS} -D CPU_MKL25Z128VLK4")

# Target specific options
set(MKL25Z128_TARGET_FLAGS
    $<$<CONFIG:DEBUG>:--verbose>
    $<$<CONFIG:DEBUG>:-g>
    $<$<CONFIG:DEBUG>:-O0>
    $<$<CONFIG:DEBUG>:-DDEBUG>
    $<$<CONFIG:RELEASE>:-Os>
    $<$<CONFIG:RELEASE>:-DNDEBUG>
)

# Architecture specific options. Overwriting flags to discard defaults.
set(COMMON_FLAGS ${MKL25Z128_FLAGS})

# Switching off virtual for C++ so we don't have v-tables
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -fno-rtti -fno-exceptions" CACHE INTERNAL "")
set(CMAKE_C_FLAGS   "${COMMON_FLAGS}" CACHE INTERNAL "")
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS}" CACHE INTERNAL "")

set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG   ${CMAKE_CXX_FLAGS})
set(CMAKE_C_FLAGS_RELEASE   ${CMAKE_C_FLAGS})
set(CMAKE_C_FLAGS_DEBUG     ${CMAKE_C_FLAGS})
set(CMAKE_ASM_FLAGS_RELEASE ${CMAKE_ASM_FLAGS})
set(CMAKE_ASM_FLAGS_DEBUG   ${CMAKE_ASM_FLAGS})

# Architecture specific options
add_compile_options(${MKL25Z128_TARGET_FLAGS})

# Cleaning linker defaults
set(CMAKE_EXE_LINKER_FLAGS "")

# Add --verbose beforehand if "DEBUG" stated
add_link_options($<$<CONFIG:DEBUG>:--verbose>)

# Set the linker script
set(MKL25Z128_LD_SCRIPT "${CMAKE_SOURCE_DIR}/nxp_sdk/Device/MKL25Z4/gcc/MKL25Z128xxx4_flash.ld")

# Set the linker configuration
set(MKL25Z128_LD_CONFIG "-Wl,--start-group -static -lc -lgcc -lstdc++ -lrdimon -Wl,--end-group -Wl,--gc-sections -specs=nosys.specs")

# Set the linker flags
set(MKL25Z128_LD_FLAGS "${MKL25Z128_LD_CONFIG} -T${MKL25Z128_LD_SCRIPT} -Wl,-Map=target.map")

# Set the custom linker options
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MKL25Z128_LD_FLAGS}")

# Macro to get statistics on memory usage
macro(memory_statistics)
if (CMAKE_ELFSIZE)
    add_custom_command(TARGET ${PROJECT_NAME}.${PROJECT_TARGET_EXT}
        POST_BUILD
        COMMAND ${CMAKE_ELFSIZE} ${PROJECT_NAME}.${PROJECT_TARGET_EXT}
        DEPENDS ${PROJECT_NAME}
    )
else()
    message(WARNING "${Red}'size' not found:${ColorReset} cannot print memory footprint")
endif()
endmacro()

# Macro to transform resulting object file in the format used by the flashing tool
macro(convert_to_firmware_filetype)

# Getting and saving the path of the resulting file
set(ARTIFACT_HEX "${PROJECT_NAME}_${TARGET_HW}.hex")
set(ARTIFACT_BIN "${PROJECT_NAME}_${TARGET_HW}.bin" CACHE INTERNAL "")

# Converting the file type to the one we can write to target's memory
if (CMAKE_OBJCOPY)
    add_custom_command(TARGET ${PROJECT_NAME}.${PROJECT_TARGET_EXT}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.${PROJECT_TARGET_EXT}>
                ${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_NAME:${ARTIFACT_HEX}>
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.${PROJECT_TARGET_EXT}>
                ${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_NAME:${ARTIFACT_BIN}>
        COMMENT "Firmware file: ${CMAKE_CURRENT_BINARY_DIR}/${ARTIFACT_HEX} generated\nFirmware file: ${CMAKE_CURRENT_BINARY_DIR}/${ARTIFACT_BIN} generated"
    )
else()
    message(WARNING "${Red}'objcopy' not found:${ColorReset} cannot generate firmware file(s)")
endif()
endmacro()
