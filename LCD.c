#include "LCD.h"

void i2c_write_byte(uint8_t val) {
    i2c_write_blocking(I2C_PORT, lcd_addr, &val, 1, false);
}

void lcd_toggle_enable(uint8_t val) {
    // Toggle enable pin on LCD display
    i2c_write_byte(val | LCD_ENABLE_BIT);
    i2c_write_byte(val & ~LCD_ENABLE_BIT);
}

void lcd_send_byte(uint8_t val, uint8_t mode, uint8_t backlight) {
    uint8_t high;
    uint8_t low;

    if(backlight)
    {
        high = mode | (val & 0xF0) | LCD_BACKLIGHT;
        low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;
    }
    else {
        high = mode | (val & 0xF0);
        low = mode | ((val << 4) & 0xF0);
    }

    i2c_write_byte(high);
    lcd_toggle_enable(high);
    i2c_write_byte(low);
    lcd_toggle_enable(low);
}

void lcd_clear(void) {
    lcd_send_byte(LCD_CLEARDISPLAY, LCD_COMMAND, 1);
}

void lcd_setCursor(uint8_t line, uint8_t position) {
    uint8_t line_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
    uint8_t val = 0x80 + line_offsets[line] + position;
    lcd_send_byte(val, LCD_COMMAND, 1);
}

void lcd_write(char val) {
    lcd_send_byte(val, LCD_CHARACTER, 1);
}

void lcd_print(const char *s) {
    while (*s) {
        lcd_write(*s++);
    }
}

void lcd_init(uint8_t sda, uint8_t scl) {
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_pull_up(sda);
    gpio_pull_up(scl);

    // Make the I2C pins available to picotool
    // bi_decl( bi_2pins_with_func(sda, scl, GPIO_FUNC_I2C)); For some reason this produces an error.

    lcd_send_byte(0x03, LCD_COMMAND, 1);
    lcd_send_byte(0x03, LCD_COMMAND, 1);
    lcd_send_byte(0x03, LCD_COMMAND, 1);
    lcd_send_byte(0x02, LCD_COMMAND, 1);

    lcd_send_byte(LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND, 1);
    lcd_send_byte(LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND, 1);
    lcd_send_byte(LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_COMMAND, 1);
    lcd_clear();
}

int nameFileSize(char * str)
{
    int i  = 0;
    while (str[i] != '.')
    {
        i++;
    }
    return i;
}

void showFileNames (int cursor,char fileNames[][255],int size)
{
    for(int i = 0; i<4;i++)
    {
        
        if(i<size)
        {
            char auxil[20];
            memset(auxil,'\0',20);
            strncpy(auxil,fileNames[i],20);
            auxil[nameFileSize(fileNames[i])]= '\0';
            if(i == 0)
            {
                lcd_setCursor(i,nameFileSize(fileNames[i])+1);
                
                lcd_write(CURSOR);
            }
            lcd_setCursor(i,0);
            lcd_print(auxil);
        }
    }
    
}