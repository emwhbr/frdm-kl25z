# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME}.${PROJECT_TARGET_EXT}
   target_1.c
)

target_link_libraries(${PROJECT_NAME}.${PROJECT_TARGET_EXT}
   device-mkl25z4         # NXP SDK
   target-support         # Target support library
)

memory_statistics()
convert_to_firmware_filetype()
