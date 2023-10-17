#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sd_card.h"
#include "ff.h"
#include "pico/stdlib.h"
#include "./NeoPixel/NeoPixel.h"
#include "./FileSystem/FileSystem.h"
#include "./LCD/LCD.h"
#include "./SwichHandler/SwichHandler.h"
#include "TITOLedCore.h"

char fileNames[255][255];
struct Leds leds[1000];
struct Flags flags;
int main()
{

    
    stdio_init_all();
    SystemCoreClockUpdate();
    memset(leds,0,sizeof(struct Leds)*1000);
    initLedPorts();
    lcd_init(16,17);
    initSd(false);
    initButton();
    int cant = 0;
    int cursor = 0;
   // showFileNames(0,fileNames,cant);

    int x = 0;
    int y = 0;
    int z = 0;

    while(true)
    {
    manageMenuState(&cursor,fileNames,&cant,&flags);
   /*  memset(leds,'0',sizeof(struct Leds)*1000);
    leds[CALCULATE_INDEX(1,0,0)].r = '1';
    leds[CALCULATE_INDEX(1,0,0)].g = '1';
    leds[CALCULATE_INDEX(1,0,0)].b = '1';
   
    initSd(false);
    toggleSDCardMount(true);
    toggleFileAccess("prueba.tito3d",true);
    writeCubeDataColors(leds,0);
    toggleFileAccess("prueba.tito3d",false);
    toggleSDCardMount(false); */

   /*      
        leds[CALCULATE_INDEX(x,y,z)].r = z+1*20;
        leds[CALCULATE_INDEX(x,y,z)].g = x+1*60;
        leds[CALCULATE_INDEX(x,y,z)].b = y+1*20;
        y++;
        if(y>= 10)
        {
            y = 0;
            z++;
            if(z>= 10 )
            {
                x++;
                z = 0;
                if(x>1)
                {
                    x = 0;
                    memset(leds,0,sizeof(struct Leds)*1000);
                }
            }
        }
        setLedsModule(leds,A);
        sendLedPwmData(A);
        
        sleep_ms(10);
         */

    }
    return 0;
}
