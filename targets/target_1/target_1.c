#include <stdint.h>
#include <stddef.h>

#include "MKL25Z4.h"

#define DATA_BUFFER_SIZE  (100)

static volatile uint8_t s_data_buffer[DATA_BUFFER_SIZE] = { 0 };

void main(void)
{
    while (1)
    {
        for (size_t i=0; i < DATA_BUFFER_SIZE; i++)
        {
            s_data_buffer[i] = (uint8_t)i;
        }
    }
}
