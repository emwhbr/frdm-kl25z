#ifndef SUPPORT_LED_H
#define SUPPORT_LED_H

typedef enum
{
   LED_ID_RED = 0,
   LED_ID_GREEN,
   LED_ID_BLUE,
   LED_ID_MAX
} led_id_t;

void led_init();
void led_on(led_id_t id);
void led_off(led_id_t id);

#endif // SUPPORT_LED
