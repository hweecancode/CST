#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>

void lcd_init();

void lcd_update_screen(int mins, int secs);

#endif