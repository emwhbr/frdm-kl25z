#include "MKL25Z4.h"

#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

#include "debug_io.h"

typedef enum
{
   DEBUG_IO_PIN_1 = 0,
   DEBUG_IO_PIN_2,
   DEBUG_IO_PIN_3,
   DEBUG_IO_PIN_4,
   DEBUG_IO_PIN_MAX
} debug_io_pin_id_t;

#define DEBUG_IO_SPI_DATA  DEBUG_IO_PIN_3  // SPI MOSI
#define DEBUG_IO_SPI_CLK   DEBUG_IO_PIN_4  // SPI CLK

typedef struct
{
   PORT_Type *port;
   GPIO_Type *gpio;
   uint32_t   pin;
} debug_io_pin_cfg_t;

static const debug_io_pin_cfg_t s_debug_io_pin_cfg[DEBUG_IO_PIN_MAX] =
{
   { PORTB, GPIOB,  8u },  // PIN 1: PTB8,  pin47, Connector J9-01
   { PORTB, GPIOB,  9u },  // PIN 2: PTB9,  pin48, Connector J9-03
   { PORTB, GPIOB, 10u },  // PIN 3: PTB10, pin49, Connector J9-05
   { PORTB, GPIOB, 11u }   // PIN 4: PTB11, pin50, Connector J9-07
};

///////////////////////////////////////////////////////////////////////////

void debug_io_init()
{
   // All debug pins @ Port B
   CLOCK_EnableClock(kCLOCK_PortB); // Port B Clock Gate Control: Clock enabled

   // Start with all debug pins off.
   gpio_pin_config_t led_config = { kGPIO_DigitalOutput, 0 };

   for (uint8_t i=0; i < DEBUG_IO_PIN_MAX; i++)
   {
      PORT_SetPinMux(s_debug_io_pin_cfg[i].port, s_debug_io_pin_cfg[i].pin, kPORT_MuxAsGpio);
      GPIO_PinInit(s_debug_io_pin_cfg[i].gpio, s_debug_io_pin_cfg[i].pin, &led_config);
   }
}

///////////////////////////////////////////////////////////////////////////

void debug_io_pin(uint8_t count_1, uint8_t count_2, uint8_t count_3, uint8_t count_4)
{
   while (0 != count_1)
   {
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_PIN_1].gpio, s_debug_io_pin_cfg[DEBUG_IO_PIN_1].pin, 1);
      //sleep_us(1);
      count_1--;
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_PIN_1].gpio, s_debug_io_pin_cfg[DEBUG_IO_PIN_1].pin, 0);
      //sleep_us(1);
   }

   while (0 != count_2)
   {
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_PIN_2].gpio, s_debug_io_pin_cfg[DEBUG_IO_PIN_2].pin, 1);
      //sleep_us(1);
      count_2--;
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_PIN_2].gpio, s_debug_io_pin_cfg[DEBUG_IO_PIN_2].pin, 0);
      //sleep_us(1);
   }

   while (0 != count_3)
   {
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_PIN_3].gpio, s_debug_io_pin_cfg[DEBUG_IO_PIN_3].pin, 1);
      //sleep_us(1);
      count_3--;
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_PIN_3].gpio, s_debug_io_pin_cfg[DEBUG_IO_PIN_3].pin, 0);
      //sleep_us(1);
   }

   while (0 != count_4)
   {
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_PIN_4].gpio, s_debug_io_pin_cfg[DEBUG_IO_PIN_4].pin, 1);
      //sleep_us(1);
      count_4--;
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_PIN_4].gpio, s_debug_io_pin_cfg[DEBUG_IO_PIN_4].pin, 0);
      //sleep_us(1);
   }
}

///////////////////////////////////////////////////////////////////////////

void debug_io_pin_on(bool pin_1, bool pin_2, bool pin_3, bool pin_4)
{
   if (true == pin_1)
   {
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_PIN_1].gpio, s_debug_io_pin_cfg[DEBUG_IO_PIN_1].pin, 1);
   }

   if (true == pin_2)
   {
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_PIN_2].gpio, s_debug_io_pin_cfg[DEBUG_IO_PIN_2].pin, 1);
   }

   if (true == pin_3)
   {
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_PIN_3].gpio, s_debug_io_pin_cfg[DEBUG_IO_PIN_3].pin, 1);
   }

   if (true == pin_4)
   {
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_PIN_4].gpio, s_debug_io_pin_cfg[DEBUG_IO_PIN_4].pin, 1);
   }
}

///////////////////////////////////////////////////////////////////////////

void debug_io_pin_off(bool pin_1, bool pin_2, bool pin_3, bool pin_4)
{
   if (true == pin_1)
   {
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_PIN_1].gpio, s_debug_io_pin_cfg[DEBUG_IO_PIN_1].pin, 0);
   }

   if (true == pin_2)
   {
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_PIN_2].gpio, s_debug_io_pin_cfg[DEBUG_IO_PIN_2].pin, 0);
   }

   if (true == pin_3)
   {
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_PIN_3].gpio, s_debug_io_pin_cfg[DEBUG_IO_PIN_3].pin, 0);
   }

   if (true == pin_4)
   {
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_PIN_4].gpio, s_debug_io_pin_cfg[DEBUG_IO_PIN_4].pin, 0);
   }
}

///////////////////////////////////////////////////////////////////////////

void debug_io_code8(uint8_t code)
{
   // SPI: 8bit, MSb first, CPOL=0, CPHA=0
   uint8_t clk = 8U;

   while (0 != clk)
   {
      // CLK low
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_SPI_CLK].gpio, s_debug_io_pin_cfg[DEBUG_IO_SPI_CLK].pin, 0);
      //sleep_us(1);

      // DATA
      if (code & 0x80)
      {
         GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_SPI_DATA].gpio, s_debug_io_pin_cfg[DEBUG_IO_SPI_DATA].pin, 1);
      }
      else
      {
         GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_SPI_DATA].gpio, s_debug_io_pin_cfg[DEBUG_IO_SPI_DATA].pin, 0);
      }

      code = (uint8_t)(code << 1U);

      // CLK high
      GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_SPI_CLK].gpio, s_debug_io_pin_cfg[DEBUG_IO_SPI_CLK].pin, 1);
      //sleep_us(1);
      clk--;
   }

   GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_SPI_CLK].gpio, s_debug_io_pin_cfg[DEBUG_IO_SPI_CLK].pin, 0);
   GPIO_WritePinOutput(s_debug_io_pin_cfg[DEBUG_IO_SPI_DATA].gpio, s_debug_io_pin_cfg[DEBUG_IO_SPI_DATA].pin, 0);
}

///////////////////////////////////////////////////////////////////////////

void debug_io_code16(uint16_t code)
{
   debug_io_code8( (uint8_t)((uint16_t)(0xff00 & code) >> 8) );
   debug_io_code8( (uint8_t)((uint16_t)(0x00ff & code) >> 0) );
}

///////////////////////////////////////////////////////////////////////////

void debug_io_code32(uint32_t code)
{
   debug_io_code8( (uint8_t)((uint32_t)(0xff000000 & code) >> 24) );
   debug_io_code8( (uint8_t)((uint32_t)(0x00ff0000 & code) >> 16) );
   debug_io_code8( (uint8_t)((uint32_t)(0x0000ff00 & code) >> 8) );
   debug_io_code8( (uint8_t)((uint32_t)(0x000000ff & code) >> 0) );
}