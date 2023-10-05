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

void mountAndUnmount(bool mount)
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
         return fileNum;
    }
    else
    {
        return -1;
    }
}

void openFile(char *fileName)
{
    fr = f_open(&fil, fileName, FA_WRITE| FA_CREATE_ALWAYS);
    if (fr != FR_OK) {
        printf("ERROR: Could not open file (%d)\r\n", fr);
        while (true);
    }
}
void writeCubeDataColors(struct Leds leds[][10][10])
{
    uint32_t aux;
    struct Leds lectura [1000]; // alto, ancho y prof

    // indice = alto * ancho * z + ancho * y + x

    f_write(&fil, leds, sizeof(struct Leds) * 1000, &aux);
    f_read(&fil, &lectura, sizeof(struct Leds) * 1000, &aux);
    fr = f_close(&fil);
    if (fr != FR_OK) {
        printf("ERROR: Could not close file (%d)\r\n", fr);
        while (true);
    }
 }