#include "buttons.h"
#include "config.h"
#include "lcd_display.h"

void buttons_init() {
    // initialize button pins 
    pinMode(PIN_BUTTON_K1, INPUT_PULLUP);
    pinMode(PIN_BUTTON_K2, INPUT_PULLUP);
    pinMode(PIN_BUTTON_K3, INPUT_PULLUP);
    pinMode(PIN_BUTTON_K4, INPUT_PULLUP);

    Serial.println("Buttons initialized.");
}

void buttons_update_system(int* timer_len, int* brightness) {
    // create an 8 bit bus for buttons 
    uint8_t button_bus =
        (!digitalRead(PIN_BUTTON_K1) << 0) |
        (!digitalRead(PIN_BUTTON_K2) << 1) |
        (!digitalRead(PIN_BUTTON_K3) << 2) |
        (!digitalRead(PIN_BUTTON_K4) << 3);
  
    if (button_bus == 0) return;

    // check if more than one button is pressed
    if ((button_bus & (button_bus - 1)) != 0) {
        Serial.printf("Multiple buttons pressed, ignoring input\n");
        delay(250);
        return;
    }

    if (button_bus == 0b0001) {
        *timer_len = 10;
        Serial.printf("Button 1: 10 min set\n");
    }
    else if (button_bus == 0b0010) {
        *timer_len = 5;
        Serial.printf("Button 2: 5 min set\n");
    }
    else if (button_bus == 0b0100) {
        *timer_len += 1;
        Serial.printf("Button 3: Increment. Total: %d\n", *timer_len);
    }
    else if (button_bus == 0b1000) {

        if(*brightness >= 2) {
            *brightness = 0;
            Serial.printf("Button 4: brightness reset to min\n");
            
        } else {
            *brightness += 1;    
            Serial.printf("Button 4: Increasing brightness to %d\n", *brightness);
        }
        lcd_set_brightness(*brightness);
    }

    delay(250); 
}