#if !defined(LCD)
#define LCD
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#define ENTER   14
#define UP      15
#define DOWN    13
#define DEBOUNCEDELAYUS 100
typedef struct DebouncedButton{
    int pin;
    uint32_t last_pressed_time;
    bool state;
};
#endif