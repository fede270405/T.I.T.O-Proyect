#include "TITOLedCore.h"

void manageMenuState(int *cursor,char fileNames[][255],int *cant, struct Flags *flags)
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
                initSd(true);
                if(!toggleSDCardMount(true))
                {
                    showErrorMessage(ERRSD);
                    sleep_ms(2000);
                    writen = false;
                    menuStates = START;
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
                else
                {
                    writen = false;
                    menuStates = READING;
                }
            }
        break;
        case READING:   
            if(!writen)
            {
                if(toggleFileAccess(fileNames[*cursor],true))
                {
                    char auxil[20];
                    removeExtension(fileNames[*cursor],auxil,20);
                    lcd_clear();
                    lcd_setCursor(0,0);
                    lcd_print("Reading:");
                    lcd_setCursor(1,0);
                    lcd_print(auxil);
                    lcd_setCursor(3,0);
                    lcd_print("Undo, press ENTER");
                    flags->loadDataFromFile = true;
                    writen = true;
                }
                else
                {
                            showErrorMessage(ERRFILE);
                            sleep_ms(2000);
                            writen = false;
                            menuStates = START;
                            toggleSDCardMount(false);
                            break; 
                }

            }
            if(getEnterButton())
            {
                if(toggleFileAccess(fileNames[*cursor],false))
                {
                    *cant = readFileNames(fileNames);
                    *cursor = 0;
                    showFileNames(*cursor,fileNames,*cant);
                    menuStates = FILES;
                    break;
                }
                else
                {
                    showErrorMessage(ERRFILE);
                    sleep_ms(2000);
                    writen = false;
                    menuStates = START;
                    toggleSDCardMount(false);
                    break; 
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
        case ERRFILE:
            lcd_clear();
            lcd_setCursor(0,0);
            lcd_print("Read File Error");
            lcd_setCursor(2,0);
            lcd_print("Cannot Read File");
        break;
    }
}