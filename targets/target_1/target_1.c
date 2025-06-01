#include <stdint.h>
#include <stddef.h>

#include "MKL25Z4.h"

#include "debug_io.h"
#include "led.h"

#define DATA_BUFFER_SIZE  (100)

static volatile uint8_t s_data_buffer[DATA_BUFFER_SIZE] = { 0 };

void main(void)
{
   // Make sure variable 'SystemCoreClock' is updated with correct value
   SystemCoreClockUpdate();

   // Initialize the target support library
   debug_io_init();
   led_init();

   // Signal started -LED
   led_on(LED_ID_BLUE);

   // Signal started - debug i/o
   debug_io_pin(2,4,8,16);
   debug_io_pin_on(1,0,0,0);
   debug_io_code8(0xab);
   debug_io_pin_off(1,0,0,0);
   debug_io_pin_on(0,1,0,0);
   debug_io_code16(0x1234);
   debug_io_pin_off(0,1,0,0);
   debug_io_pin_on(1,0,0,0);
   debug_io_code32(0xa1b2c3d4);
   debug_io_pin_off(1,0,0,0);

   // Check system core clock (CMSIS)
   debug_io_code32(0xccccccc1);
   debug_io_code32(SystemCoreClock);

   // Start looping
   while (1)
   {
      debug_io_pin_on(1,0,0,0);
      for (size_t i=0; i < DATA_BUFFER_SIZE; i++)
      {
         debug_io_pin(0,1,0,0);
         s_data_buffer[i] = (uint8_t)i;
      }
      debug_io_pin_off(1,0,0,0);
   }
}
