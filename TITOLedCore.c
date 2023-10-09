#include "TITOLedCore.h"

void manageMenuState(int *cursor,char fileNames[][255],int *cant)
{
    static int menuStates = START;
    static bool writen = false;
    int a = 0;
    switch(menuStates)
    {
        case START:
            if(!writen)
            {
                lcd_clear();
                lcd_setCursor(0,6);
                lcd_setCursor(0,6);
                lcd_print("NO MEDIA");
                lcd_setCursor(2,1);
                lcd_print("Mount, press ENTER");
                writen = true;
            }
            if(getEnterButton())
            {
                if(!toggleSDCardMount(true))
                {
                    showErrorMessage(ERRSD);
                    sleep_ms(2000);
                    writen = false;
                    break;
                }
                *cant = readFileNames(fileNames);
                *cursor = 0;
                showFileNames(*cursor,fileNames,*cant);
                menuStates = FILES;
            }
        break;
        case FILES:
             a = moveMenuCursor();
            if(a != 0)
            {
                *cursor += a;
                if(*cursor <0){
                    *cursor = 0;
                } 
                if(*cursor >*cant-1)
                {
                    *cursor = *cant-1;
                }
                showFileNames(*cursor,fileNames,*cant);
            }
            if(getEnterButton())
            {
                if(*cursor == *cant-1)
                {
                   
                    writen = false;
                    toggleSDCardMount(false);
                    menuStates = START;
                }
            }
        break;
    }   

}

void showErrorMessage(int error)
{
    switch(error)
    {
        case ERRSD:
        lcd_clear();
        lcd_setCursor(0,0);
        lcd_print("SD Card Mount Error");
        lcd_setCursor(2,0);
        lcd_print("Cannot mount SD card");
        break;
    }
}