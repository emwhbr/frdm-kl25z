set(CMAKE_MCU_PROGRAMMER
    "$ENV{JLINK_FLASHER}"
    "-hide"
    "-openprj../jlink/frdm-kl25z.jflash"
    "-open./${PROJECT_TARGET}/${ARTIFACT_BIN},0x0"
    "-auto"
    "-exit"
)

# Macro that enables "program_mcu", to program binary into MCU flash
macro(enable_programmer)
    add_custom_target(program_mcu
        COMMAND ${CMAKE_MCU_PROGRAMMER}
        COMMENT "Programming MCU flash ..."
        VERBATIM
    )
endmacro()
