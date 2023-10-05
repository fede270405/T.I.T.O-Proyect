#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sd_card.h"
#include "ff.h"
#include "pico/stdlib.h"
#include "./NeoPixel/NeoPixel.h"
#include "FileSystem.h"
#include "LCD.h"
char fileNames[255][255];
struct Leds leds[10][10][10];
int main()
{
    stdio_init_all();
    SystemCoreClockUpdate();

    for(int i = 0;i<10;i++)
    {
        for(int x = 0;x<10;x++)
        {
            memset(leds[i][x],255,sizeof(struct Leds)*10);
        }
    }

    initSd();
    mountAndUnmount(true);
    openFile("cubo.txt");
    writeCubeDataColors(leds);
    mountAndUnmount(false);
    
    lcd_init(16,17);
    


    return 0;
}
