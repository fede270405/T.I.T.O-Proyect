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
                clearLEDMatrix();
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
                    clearLEDMatrix();
                    writen = false;
                    menuStates = READING;
                }
            }
        break;
        case READING:   
            if(!writen)
            {
                if(toggleFileAccess(fileNames[*cursor],true,true))
                {
                    char auxil[20];
                    flags->readDataComplete = false;
                    removeExtension(fileNames[*cursor],auxil,20);
                    lcd_clear();
                    lcd_setCursor(0,0);
                    lcd_print("Reading:");
                    lcd_setCursor(1,0);
                    lcd_print(auxil);
                    lcd_setCursor(3,0);
                    lcd_print("Undo, press ENTER");
                    flags->loadDataFromFile = true;
                    flags->alreadySend = false;
                    flags->showFileFlag = false;
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
                if(toggleFileAccess(fileNames[*cursor],false,true))
                {
                    clearLEDMatrix();
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
void updateCubeBuffersFromSD(int *index,struct Flags *flags,struct Leds *cubeBufferA,struct Leds *cubeBufferB,int shift,int framenum)
{
    if(flags->ledCubeDataRequest)
    {
        if(flags->fillBufferToggle)
        {
            readCubeDataColors(cubeBufferA,(*index)++,shift);
        }
        else
        {
            readCubeDataColors(cubeBufferB,(*index)++,shift);
        }
        if(*index >= framenum)
        {
            *index = 0;
        }
        flags->ledCubeDataRequest = false;
    }
}

void updateCubeBuffersFromMicrophone(int *index,struct Flags *flags,struct Leds *cubeBufferA,struct Leds *cubeBufferB)
{
    if(flags->ledCubeDataRequest)
    {
        if(flags->fillBufferToggle)
        {
            
        }
        else
        {
            
        }

        flags->ledCubeDataRequest = false;
    }
}
void showFileInLEDMatrix3D(int frameNum, int timePerFrameMs, struct Leds *cubeBufferA, struct Leds *cubeBufferB,struct Flags * flags,int *time,int *index)
{
    static int state = RESET;
    if(frameNum == 1)
    {
        if(!flags->showFileFlag)
        {
            flags->fillBufferToggle = true;
            flags->ledCubeDataRequest = true;
            flags->alreadySend = false;
            flags->showFileFlag = true;

        }
        if(!flags->ledCubeDataRequest)
        {
            if(!flags->alreadySend)
            {
                displayLedCube(cubeBufferA);
                flags->alreadySend = true;
            }
        }
    }
    else
    { 
        switch(state)
        {
            case RESET:
                if(!flags->showFileFlag)
                {
                    flags->fillBufferToggle = true;
                    flags->ledCubeDataRequest = true;
                    flags->showFileFlag = true;
                }
                if(!flags->ledCubeDataRequest)
                {
                    
                    state = READB_PRINTA;
                    flags->showFileFlag = false;
                }
            break;
            case READB_PRINTA: 
                if(!flags->showFileFlag)
                {
                    flags->fillBufferToggle = false;
                    flags->ledCubeDataRequest = true;
                    *time = timePerFrameMs;
                    flags->showFileFlag = true;
                }
                if(!flags->ledCubeDataRequest && *time <= 0)
                {
                    displayLedCube(cubeBufferA);
                    state = READA_PRINTB;
                    flags->showFileFlag = false;
                } 
            break;
            case READA_PRINTB: 
                if(!flags->showFileFlag)
                {
                    flags->fillBufferToggle = true;
                    flags->ledCubeDataRequest = true;
                    *time = timePerFrameMs;
                    flags->showFileFlag = true;
                }
                if(!flags->ledCubeDataRequest && *time <= 0)
                {
                    displayLedCube(cubeBufferB);
                    state = READB_PRINTA;
                    flags->showFileFlag = false;
                } 
            break;
        }
    }
}
void initModules()
{
    initLedPorts();
    lcd_init(16,17);
    initSd(false);
    initButton();
    systickInit();
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