#if !defined(NeoPixel)
#define NeoPixel
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/dma.h"
#include "RP2040.h"

#define LED_STRIP 10
#define LEDS_MODULE LED_STRIP * 20
#define CALCULATE_INDEX(x,y,z) (10*10*(z)+10 *(y)+(x))
struct Leds
{
    uint8_t r,g,b;
}; 

void initLedPorts();
void setLedPwmData(struct Leds leds,uint8_t ledNum, uint8_t channel);
void sendLedPwmData(uint8_t channel);
void setLedsModule(struct Leds leds[],int8_t channel);
typedef enum 
{
    A,
    B,
    C,
    D,
    E
}channels;


#endif // NeoPixel
