#include "buzzer.h"
#include "config.h"

void buzzer_init() {
    // Initialize
        pinMode(PIN_BUZZER, INPUT_PULLUP);
    // Attach PWM directly to the pin
    ledcAttachPin(PIN_BUZZER, BUZZER_FREQ);
    ledcSetup(0, BUZZER_FREQ, BUZZER_RESOLUTION);
}

void buzzer_on() {
    // Buzzer ON
    ledcWrite(PIN_BUZZER, 128);
    delay(500); // Buzz for 500ms

    // Buzzer OFF
    ledcWrite(PIN_BUZZER, 0);
    delay(500); // Pause for 500ms

}