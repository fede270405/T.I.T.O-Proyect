#if !defined(NeoPixel)
#define NeoPixel
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/dma.h"
#include "RP2040.h"

#define CANT_LEDS 10

void initLedPorts();
void setLedPwmData(uint8_t red, uint8_t green, uint8_t blue,uint8_t ledNum, uint8_t channel);
void sendLedPwmData(uint8_t channel);
typedef enum 
{
    A,
    B,
    C,
    D,
    E
}channels;


#endif // NeoPixel