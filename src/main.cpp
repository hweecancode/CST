#include "config.h"
#include "components/buttons.h"
#include "components/buzzer.h"
#include "components/distance_sensor.h"
#include "components/lcd_display.h"
#include <Arduino.h>

int timer_length = 0;
int brightness = 0;
bool timer_running = false;

// put function declarations here:

void setup() {
  Serial.begin(115200);
  delay(1000);
  buttons_init();
  distance_init();
  lcd_init();


}

void loop() {
  timer_length = 0;

  Serial.print("[MAIN] Printing start up \n");
  lcd_print_startup();

  float dist = get_distance();

  if(dist <= 5.0) {
    buttons_update_system(&timer_length, &brightness);

  } else if(timer_length >= 1 && dist < 5.0 ) {

  }


}

