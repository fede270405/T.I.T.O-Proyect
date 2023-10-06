#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sd_card.h"
#include "ff.h"
#include "pico/stdlib.h"
#include "./NeoPixel/NeoPixel.h"
#include "./FileSystem/FileSystem.h"
#include "./LCD/LCD.h"
#include "SwichHandler/SwichHandler.h"
char fileNames[255][255];

struct Leds leds[1000];
int main()
{

    
    stdio_init_all();
    SystemCoreClockUpdate();
    memset(leds,255,sizeof(struct Leds)*1000);
    lcd_init(16,17);
    initSd();
    initButton();
    toggleSDCardMount(true);
    int cant = readFileNames(fileNames);
    int cursor = 0;
    showFileNames(0,fileNames,cant);
    while(true)
    {

    }
    return 0;
}
