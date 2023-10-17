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

struct Flags {
    uint8_t flags; 

    bool loadDataFromFile : 1;
    bool flag2 : 1;
    bool flag3 : 1;
    bool flag4 : 1;
    bool flag5 : 1;
    bool flag6 : 1;
    bool flag7 : 1;
    bool flag8 : 1;
};
void manageMenuState(int *cursor,char fileNames[][255],int *cant, struct Flags *flags);
void showErrorMessage(int error);
#endif