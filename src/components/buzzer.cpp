#include "buzzer.h"
#include "config.h"

void buzzer_init() {
    // Initialize
        pinMode(PIN_BUZZER, INPUT_PULLUP);
        const int freq = 440;       // 440Hz
        const int resolution = 8;   // 8-bit PWM (0-255)
    // Attach PWM directly to the pin
    ledcAttachPin(PIN_BUZZER, freq);
}

void buzzer_on() {
    // Buzzer ON
    ledcWrite(PIN_BUZZER, 128);
    delay(500); // Buzz for 500ms

    // Buzzer OFF
    ledcWrite(PIN_BUZZER, 0);
    delay(500); // Pause for 500ms

}