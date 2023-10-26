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
#include "pico/multicore.h"
#include "./Systick/Systick.h"

#define FLAG_VALUE 123

char fileNames[255][255];
struct Leds cubeBufferA[1000];
struct Leds cubeBufferB[1000];

struct Flags flags;
int ms = 0;
int ind = 0;
int shift = 0;
int frame = 0;
int timeperframe = 0;
void core1_main() {

/*     multicore_fifo_push_blocking(FLAG_VALUE);

    uint32_t g = multicore_fifo_pop_blocking();

    if (g != FLAG_VALUE)
        printf("Hmm, that's not right on core 1!\n");
    else
        printf("Its all gone well on core 1!");
 */
    while (1)
    {
        updateCubeBuffersFromSD(&ind,&flags,cubeBufferA,cubeBufferB,shift,frame);
    }
        tight_loop_contents();
}

struct Leds interpolateColors(struct Leds color1, struct Leds color2, double factor) {
    struct Leds result;
    result.r = color1.r + (int)(factor * (color2.r - color1.r));
    result.g = color1.g + (int)(factor * (color2.g - color1.g));
    result.b = color1.b + (int)(factor * (color2.b - color1.b));
    return result;
}

int main()
{
         stdio_init_all();
    SystemCoreClockUpdate();
    initLedPorts();
    lcd_init(16,17);
    initSd(false);
    initButton();
    systickInit();
    int cant = 0;
    int cursor = 0;

    multicore_launch_core1(core1_main);

/*     while(true)
    {
        manageMenuState(&cursor,fileNames,&cant,&flags);

        if(flags.loadDataFromFile)
        {
            if(!flags.readDataComplete)
            {
                shift = readAnimationData(&frame,&timeperframe);
                flags.readDataComplete = true;
            }
            showFileInLEDMatrix3D(frame,timeperframe,cubeBufferA,cubeBufferB,&flags,&ms,&ind);
        }
    }  */

    memset(cubeBufferA,0,sizeof(struct Leds)*1000);

    initSd(false);
    toggleSDCardMount(true);
    toggleFileAccess("XXX.tito3d",true,false);
    int a = writeAnimationData(&frame,&timeperframe);
    for(int i = 0; i<1000;i++)
    {
    cubeBufferA[i].r = 255;
    }
    writeCubeDataColors(cubeBufferA,0,a);
    memset(cubeBufferA,0,sizeof(struct Leds)*1000);
    for(int i = 0; i<1000;i++)
    {
    cubeBufferA[i].g = 255;
    }
    writeCubeDataColors(cubeBufferA,1,a);
    toggleFileAccess("XXX.tito3d",false,false);
    toggleSDCardMount(false);
    return 0;
}

void SysTick_Handler(void)
{
    if(ms<= 0)
    {
        ms = 0;
    }
    else
    {
        ms--;
    }
}