#if !defined(FileSystem)
#define FileSystem
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sd_card.h"
#include "pico/malloc.h"
#include "pico/mem_ops.h"
#include "ff.h"
#include "../NeoPixel/NeoPixel.h"

#define EXTENSION ".tito3d"

int readFileNames(char fileNames[][255]);
void writeCubeDataColors(struct Leds *leds,uint16_t index);
bool toggleSDCardMount(bool mount);
void initSd(bool force);
bool toggleFileAccess(char *fileName,bool open);
#endif