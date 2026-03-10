#include "buttons.h"
#include "config.h"
#include "lcd_display.h"

static unsigned long last_press_time[4] = {0, 0, 0, 0};
// active low buttons
static bool last_state[4] = {true, true, true, true}; 
static const unsigned long DEBOUNCE_MS = 200;


void buttons_init() {
    // initialize button pins 
    pinMode(PIN_BUTTON_K1, INPUT_PULLUP);
    pinMode(PIN_BUTTON_K2, INPUT_PULLUP);
    pinMode(PIN_BUTTON_K3, INPUT_PULLUP);
    pinMode(PIN_BUTTON_K4, INPUT_PULLUP);

    Serial.println("Buttons initialized.");
}

static uint8_t buttons_debounced() {
    uint8_t triggered = 0;
    unsigned long now  = millis();

    const int pins[4] = {
        PIN_BUTTON_K1, PIN_BUTTON_K2,
        PIN_BUTTON_K3, PIN_BUTTON_K4
    };

    for (int i = 0; i < 4; i++) {
        bool current_state = digitalRead(pins[i]); 

        // Detect falling edge (unpressed → pressed) with debounce window
        if (current_state == LOW && last_state[i] == HIGH) {
            if (now - last_press_time[i] >= DEBOUNCE_MS) {
                triggered      |= (1 << i);
                last_press_time[i] = now;
            }
        }
        last_state[i] = current_state;
    }
    return triggered;
}

void buttons_update_system(int* timer_len, int* brightness, bool timer_running) {
    // create an 8 bit bus for buttons 
    uint8_t button_bus = buttons_debounced();
  
    if (button_bus == 0) return;

    // check if more than one button is pressed
    if ((button_bus & (button_bus - 1)) != 0) {
        Serial.printf("Multiple buttons pressed, ignoring input\n");
        delay(250);
        return;
    }

    if (button_bus == 0b0001) {
        if(!timer_running) {
            *timer_len = 10;
            Serial.printf("Button 1: 10 min set\n");
        }
    }
    else if (button_bus == 0b0010) {
        if(!timer_running) {
            *timer_len = 5;
            Serial.printf("Button 2: 5 min set\n");
        }
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
    
}