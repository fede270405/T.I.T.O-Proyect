#if !defined(LCD)
#define LCD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#define LCD_CLEARDISPLAY 0x01 
#define LCD_RETURNHOME 0x02 
#define LCD_ENTRYMODESET 0x04 
#define LCD_DISPLAYCONTROL 0x08 
#define LCD_CURSORSHIFT 0x10 
#define LCD_FUNCTIONSET 0x20 
#define LCD_SETCGRAMADDR 0x40 
#define LCD_SETDDRAMADDR 0x80 
#define LCD_ENTRYSHIFTINCREMENT 0x01 
#define LCD_ENTRYLEFT 0x02 
#define LCD_BLINKON 0x01 
#define LCD_CURSORON 0x02 
#define LCD_DISPLAYON 0x04 
#define LCD_MOVERIGHT 0x04 
#define LCD_DISPLAYMOVE 0x08 
#define LCD_BACKLIGHT 0x08 
#define LCD_ENABLE_BIT 0x04 
#define LCD_CHARACTER 1 
#define LCD_COMMAND 0 
#define I2C_PORT i2c0
#define LCD_5x10DOTS 0x04
#define LCD_2LINE  0x08
#define LCD_8BITMODE 0x10
#define lcd_addr  0x27


#define CURSOR  '<'
void lcd_init(uint8_t sda, uint8_t scl);
void lcd_print(const char *s);
void lcd_setCursor(uint8_t line, uint8_t position);
int nameFileSize(char * str);
void showFileNames (int cursor,char fileNames[][255],int size);
#endif