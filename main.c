#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sd_card.h"
#include "ff.h"
#include "pico/stdlib.h"
#include "./NeoPixel/NeoPixel.h"
#include "FileSystem.h"
#include "LCD.h"

int main()
{
    stdio_init_all();
    SystemCoreClockUpdate();

    FRESULT fr;
    FATFS fs;
    FILINFO fileInfo;
    FIL fil;
    
    lcd_init(16,17);
    // Initialize SD card
    if (!sd_init_driver()) {
        printf("ERROR: Could not initialize SD card\r\n");
        while (true);
    }

    // Mount drive
    fr = f_mount(&fs, "0:", 1);
    if (fr != FR_OK) {
        printf("ERROR: Could not mount filesystem (%d)\r\n", fr);
        while (true);
    }
    char a[255][255];

    int cant = fileNames(a);

    showFileNames(1,a,cant);
    


    

/*         DIR dir;
        fr = f_opendir(&dir, "/");
        if (fr == FR_OK) {
            // Read directory entries
            while (true) {
                fr = f_readdir(&dir, &fileInfo);
                if (fr != FR_OK || fileInfo.fname[0] == 0) {
                    break; // No more files in the directory
                }

                if (fileInfo.fattrib & AM_DIR) {
                    // It's a directory
                    printf("Directory: %s\n", fileInfo.fname);
                } else {
                    // It's a regular file
                    printf("File: %s\n", fileInfo.fname);
                }
            }
} */
    return 0;
}
