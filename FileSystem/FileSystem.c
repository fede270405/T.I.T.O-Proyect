#include "FileSystem.h"

FRESULT fr;
FATFS fs;
FILINFO fileInfo;
FIL fil;

void initSd()
{
    if (!sd_init_driver()) {
    printf("ERROR: Could not initialize SD card\r\n");
    while (true);
    }
}

void toggleSDCardMount(bool mount)
{
    if(mount)
    {
        fr = f_mount(&fs, "0:", 1);
        if (fr != FR_OK) {
            printf("ERROR: Could not mount filesystem (%d)\r\n", fr);
            while (true);
        }
    }
    else
    {
        f_unmount("0:");
    }

}

int readFileNames(char fileNames[][255])
{
    for(int i = 0; i<255;i++)
    {
        memset(fileNames[i],'\0',255);
    }
    
    int fileNum = 0;
    DIR dir;
    fr = f_opendir(&dir, "/");
    if (fr == FR_OK) {

        while (true) {
            
            fr = f_readdir(&dir, &fileInfo);
            if (fr != FR_OK || fileInfo.fname[0] == 0) {
            break; 
            }
           
            if (fileInfo.fattrib & AM_DIR) {
                printf("Directory: %s\n", fileInfo.fname);
            } else {
                char *fileExtension;
                fileExtension =  strrchr(fileInfo.fname, '.');
                if(strcmp(fileExtension,EXTENSION) == 0 && fileExtension != NULL)
                {
                    if(fileNum < 254)
                    {
                        strncpy(fileNames[fileNum++],fileInfo.fname, 255);  
                    }
                    else
                    {
                        break;
                    }

                }   
            }

         } 
         strncpy(fileNames[fileNum++],"unmount.tito3d", 255);  
         return fileNum;
    }
    else
    {
        return -1;
    }
}

void toggleFileAccess(char *fileName,bool open)
{
    if(open)
    {
        fr = f_open(&fil, fileName, FA_WRITE| FA_CREATE_ALWAYS);
        if (fr != FR_OK) {
            printf("ERROR: Could not open file (%d)\r\n", fr);
            while (true);
        }
    }
    else
    {
        fr = f_close(&fil);
        if (fr != FR_OK) {
            printf("ERROR: Could not close file (%d)\r\n", fr);
            while (true);
        }
    }

}

void writeCubeDataColors(struct Leds *leds,uint16_t index)
{
    uint32_t position = index * sizeof(struct Leds) * 1000;
    f_lseek(&fil,position);
    f_write(&fil, leds, sizeof(struct Leds) * 1000, &leds);
 }

 void readCubeDataColors(struct Leds *leds,uint16_t index)
 {
    uint32_t position = index * sizeof(struct Leds) * 1000;
    f_lseek(&fil,position);
    f_write(&fil, leds, sizeof(struct Leds) * 1000, &leds);
 }