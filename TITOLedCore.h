#if !defined(TITOLedCore)
#define TITOLedCore
#include <stdio.h>
#include "pico/stdlib.h"
#include "./NeoPixel/NeoPixel.h"
#include "./FileSystem/FileSystem.h"
#include "./LCD/LCD.h"
#include "./SwichHandler/SwichHandler.h"
typedef enum
{
    START,
    FILES,
    READING
};
typedef enum 
{
    ERRSD,
    ERRFILE
};
typedef enum 
{
    RESET,
    READA_PRINTB,
    READB_PRINTA,
};

struct Flags {
    uint8_t flags; 

    bool loadDataFromFile : 1;
    bool ledCubeDataRequest : 1;
    bool fillBufferToggle : 1;
    bool readDataComplete : 1;
    bool alreadySend : 1;
    bool showFileFlag : 1;
    bool flag7 : 1;
    bool flag8 : 1;
};
void showErrorMessage(int error);
void manageMenuState(int *cursor,char fileNames[][255],int *cant, struct Flags *flags);
void updateCubeBuffersFromSD(int *index,struct Flags *flags,struct Leds *cubeBufferA,struct Leds *cubeBufferB,int shift,int framenum);
void showFileInLEDMatrix3D(int frameNum, int timePerFrameMs, struct Leds *cubeBufferA, struct Leds *cubeBufferB,struct Flags * flags,int *time,int *index);
#endif