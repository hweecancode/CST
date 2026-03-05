#include "config.h"
#include "components/buttons.h"
#include "components/buzzer.h"
#include "components/distance_sensor.h"
#include "components/lcd_display.h"
#include <Arduino.h>

int timer_length = 0;

// put function declarations here:

void setup() {
  Serial.begin(115200);
  delay(1000);
  buttons_init();
  distance_init();
  buzzer_init();


}

void loop() {
  float dist = get_distance();

  if(dist > 2.25 && dist < 3.25) {
    update_timer(&timer_length);
  }
  
  delay(250);
  Serial.printf("%f\n", get_distance());
}

