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
    while (1)
    {
        updateCubeBuffersFromSD(&ind,&flags,cubeBufferA,cubeBufferB,shift,frame);
    }
        tight_loop_contents();
}


int main()
{
    stdio_init_all();
    SystemCoreClockUpdate();

    initModules();
    
    int cant = 0;
    int cursor = 0;

    multicore_launch_core1(core1_main);

    while(true)
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
    } 
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