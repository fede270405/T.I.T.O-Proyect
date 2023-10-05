#if !defined(FileSystem)
#define FileSystem
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sd_card.h"
#include "pico/malloc.h"
#include "pico/mem_ops.h"
#include "ff.h"

#define EXTENSION ".tito3d"

int fileNames(char fileNames[][255]);
#endif