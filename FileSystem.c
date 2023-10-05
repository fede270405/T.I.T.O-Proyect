#include "FileSystem.h"

FRESULT fr;
FATFS fs;
FILINFO fileInfo;
FIL fil;



int fileNames(char fileNames[][255])
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
