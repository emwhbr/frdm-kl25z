# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME}
   target_1.c
)

target_link_libraries(${PROJECT_NAME}
   device-mkl25z4         # NXP SDK
)

memory_statistics()
convert_to_firmware_filetype()
