#include <stdint.h>

#include "MKL25Z4.h"

#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

#include "led.h"

typedef struct
{
   PORT_Type *port;
   GPIO_Type *gpio;
   uint32_t   pin;
} led_pin_cfg_t;

static const led_pin_cfg_t s_led_pin_cfg[LED_ID_MAX] =
{
   { PORTB, GPIOB, 18u },  // RED:   PTB18, pin53
   { PORTB, GPIOB, 19u },  // GREEN: PTB19, pin54
   { PORTD, GPIOD,  1u }   // BLUE:  PTD1,  pin74
};

///////////////////////////////////////////////////////////////////////////

void led_init()
{
   // Red and Green LED @ Port B
   // Blue LED @ Port D
   CLOCK_EnableClock(kCLOCK_PortB); // Port B Clock Gate Control: Clock enabled
   CLOCK_EnableClock(kCLOCK_PortD); // Port D Clock Gate Control: Clock enabled

   PORT_SetPinMux(s_led_pin_cfg[LED_ID_RED].port, s_led_pin_cfg[LED_ID_RED].pin, kPORT_MuxAsGpio);
   PORT_SetPinMux(s_led_pin_cfg[LED_ID_GREEN].port, s_led_pin_cfg[LED_ID_GREEN].pin, kPORT_MuxAsGpio);
   PORT_SetPinMux(s_led_pin_cfg[LED_ID_BLUE].port, s_led_pin_cfg[LED_ID_BLUE].pin, kPORT_MuxAsGpio);

   // The LEDs on this board is turned on by setting corresponding pin to 0.
   // Start with all LEDs off.
   gpio_pin_config_t led_config = { kGPIO_DigitalOutput, 1 };

   GPIO_PinInit(s_led_pin_cfg[LED_ID_RED].gpio, s_led_pin_cfg[LED_ID_RED].pin, &led_config);
   GPIO_PinInit(s_led_pin_cfg[LED_ID_GREEN].gpio, s_led_pin_cfg[LED_ID_GREEN].pin, &led_config);
   GPIO_PinInit(s_led_pin_cfg[LED_ID_BLUE].gpio, s_led_pin_cfg[LED_ID_BLUE].pin, &led_config);
}

///////////////////////////////////////////////////////////////////////////

void led_on(led_id_t id)
{
   if (id < LED_ID_MAX)
   {
      GPIO_WritePinOutput(s_led_pin_cfg[id].gpio, s_led_pin_cfg[id].pin, 0);
   }
}

///////////////////////////////////////////////////////////////////////////

void led_off(led_id_t id)
{
   if (id < LED_ID_MAX)
   {
      GPIO_WritePinOutput(s_led_pin_cfg[id].gpio, s_led_pin_cfg[id].pin, 1);
   }
}
