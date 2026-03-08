#include "lcd_display.h"
#include "config.h"
#include <LiquidCrystal.h>

//  
LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_E, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

const int pwm_chan = 0;
unsigned long lcd_last_place_object_update = 0;
unsigned long lcd_last_timeout_update = 0;


void lcd_set_brightness(int level);

void lcd_init() {
    ledcSetup(pwm_chan, LCD_PWM_FREQ, LCD_PWM_RES);

    ledcAttachPin(PIN_LCD_BACKLIGHT, pwm_chan);

    lcd_set_brightness(0);

    lcd.begin(16, 2);
    lcd.clear();
}

void lcd_update_screen(int mins, int secs) {
    lcd.setCursor(0,0);
    lcd.print("Remaining time: ");
    // update timer display

    lcd.setCursor(0, 1);
    if (mins < 10) lcd.print("0");

    lcd.print(mins);
    lcd.print(":");
    if(secs < 10 ) {
        lcd.print("0");
    }
    lcd.printf("%d         ",secs);
}

void lcd_set_brightness(int level) {
    // pwm levels
    const int brightness_level[] = {60, 150, 255};

    ledcWrite(pwm_chan, brightness_level[level]);
}

void lcd_print_startup() {
    lcd.setCursor(0,0);
    lcd.print("Thanks for using");
    lcd.setCursor(0,1);
    lcd.print("CustomStudyTimer");
    delay(5000);

    lcd.clear();
}

void lcd_place_object() {

    if(millis() - lcd_last_place_object_update < 1000) return;

    lcd.setCursor(0,0);
    lcd.print("Place object and");
    lcd.setCursor(0,1);
    lcd.print("select a time   ");
    
    lcd_last_place_object_update = millis();
}

void lcd_place_object_back() {
    lcd.setCursor(0,0);
    lcd.print("PLACE THAT BACK!");
}

void lcd_start() {
    lcd.setCursor(0,0);
    lcd.printf("STARTING\n");

}

void lcd_show_timeout() {
    if(millis() - lcd_last_timeout_update < 1000) return;

    lcd.setCursor(0, 0);
    lcd.print("    TIME UP!    ");
    lcd.setCursor(0,1);
    lcd.print("                ");

    lcd_last_place_object_update = millis();
}