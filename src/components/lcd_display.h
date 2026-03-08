#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>


// initilize lcd display
void lcd_init();

// print start up message
void lcd_print_startup(); 

// update screen 
void lcd_update_screen(int mins, int secs);

void lcd_set_brightness(int level);

void lcd_place_object();

void lcd_place_object_back();

void lcd_show_timeout();

void lcd_start();


#endif