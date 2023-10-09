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
    FILES
};
typedef enum 
{
    ERRSD
};

void manageMenuState(int *cursor,char fileNames[][255],int *cant);
void showErrorMessage(int error);
#endif