#ifndef SUPPORT_DEBUG_IO_H
#define SUPPORT_DEBUG_IO_H

#include <stdint.h>
#include <stdbool.h>

void debug_io_init();
void debug_io_pin(uint8_t count_1, uint8_t count_2, uint8_t count_3, uint8_t count_4);
void debug_io_pin_on(bool pin_1, bool pin_2, bool pin_3, bool pin_4);
void debug_io_pin_off(bool pin_1, bool pin_2, bool pin_3, bool pin_4);
void debug_io_code8(uint8_t code);
void debug_io_code16(uint16_t code);
void debug_io_code32(uint32_t code);

#endif // SUPPORT_DEBUG_IO
