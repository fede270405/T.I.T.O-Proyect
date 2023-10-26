#include "FileSystem.h"

FRESULT fr;
FATFS fs;
FILINFO fileInfo;
FIL fil;

void initSd(bool force)
{
    if (!sd_init_driver(force)) {
    printf("ERROR: Could not initialize SD card\r\n");
    while (true);
    }
}

bool toggleSDCardMount(bool mount)
{
    if(mount)
    {
        fr = f_mount(&fs, "0:", 1);
        if (fr != FR_OK) {
         return false;
        }
    }
    else
    {
        f_unmount("0:");
    }
    return true;
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

bool toggleFileAccess(char *fileName,bool open,bool read)
{
    
    int val = (read) ?  FA_READ:(FA_CREATE_ALWAYS|FA_WRITE);
    if(open)
    {
        fr = f_open(&fil, fileName, val);
        if (fr != FR_OK) 
        {
            return false;
        }
    }
    else
    {
        fr = f_close(&fil);
        if (fr != FR_OK) 
        {
            return false;
        }
    }
    return true;
}

void writeCubeDataColors(struct Leds *leds,uint16_t index,int shift)
{
    uint32_t position = (index * sizeof(struct Leds) * 1000)+shift;
    f_lseek(&fil,position);
    f_write(&fil, leds, sizeof(struct Leds) * 1000, &leds);
 }

 void readCubeDataColors(struct Leds *leds,uint16_t index,int shift)
 {
    uint32_t position = (index * sizeof(struct Leds) * 1000)+shift;
    f_lseek(&fil,position);
    f_read(&fil, leds, sizeof(struct Leds) * 1000, &leds);
 }

int readAnimationData(int *frames,int * timeperframe)
{
    uint32_t position = 0;
    f_lseek(&fil,position);
    f_read(&fil,frames, sizeof(int),&frames);
    position += sizeof(int);
    f_lseek(&fil,position);
    f_read(&fil,timeperframe, sizeof(int),&timeperframe);
    position += sizeof(int);
    return position;
}
int writeAnimationData(int *frames,int * timeperframe)
{
    uint32_t position = 0;
    f_lseek(&fil,position);
    f_write(&fil,frames, sizeof(int),&frames);
    position += sizeof(int);
    f_lseek(&fil,position);
    f_write(&fil,timeperframe, sizeof(int),&timeperframe);
    position += sizeof(int);
    return position;
}