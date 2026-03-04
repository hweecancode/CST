#include "lcd_display.h"
#include "config.h"
#include <LiquidCrystal.h>

//  
LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_E, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

void lcd_init() {
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T:"); 
    lcd.setCursor(8, 0);
    lcd.print("D:"); 
}

void lcd_update_screen(int mins, int secs) {
    // update timer display
    lcd.setCursor(0, 1);
    if (mins < 10) lcd.print("0");
    lcd.print(mins);
    lcd.print(":");
    if (secs < 10) lcd.print("0");
    lcd.print(secs);
}

void lcd_show_timeout() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   TIME UP!    ");
}