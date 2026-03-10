#include "buzzer.h"
#include "config.h"

#define BUZZER_CHANNEL 5

void buzzer_init() {
    // Initialize
        // pinMode(PIN_BUZZER, INPUT_PULLUP);
    // Attach PWM directly to the pin
    ledcSetup(BUZZER_CHANNEL, BUZZER_FREQ, BUZZER_RESOLUTION);
    ledcAttachPin(PIN_BUZZER, BUZZER_CHANNEL);

}

void buzzer_on() {
    // Buzzer ON
    ledcWrite(BUZZER_CHANNEL, 128);
}

void buzzer_off() {
    ledcWrite(BUZZER_CHANNEL, 0);
}