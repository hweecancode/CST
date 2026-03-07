#include "config.h"
#include "components/buttons.h"
#include "components/buzzer.h"
#include "components/distance_sensor.h"
#include "components/lcd_display.h"
#include <Arduino.h>

int timer_length = 0;
int remaining_sec = 0;
bool timer_running = false;
int brightness = 0;
unsigned long last_tick = 0;

// put function declarations here:

void setup() {
  Serial.begin(115200);
  delay(1000);
  buttons_init();
  distance_init();
  lcd_init();

  Serial.print("[MAIN] Printing start up \n");
  lcd_print_startup();
  Serial.print("[MAIN] Start up over");

}

void loop() {
  // float dist = get_distance();
  // unsigned long current_tick = 0;

  // lcd_set_brightness(brightness);

  // if(!timer_running) {
  //   if(dist > 2.5) {
  //     buttons_update_system(&timer_length, &brightness);
  //     lcd_set_brightness(brightness);
  //     remaining_sec = timer_length * 60;

  //     // update lcd
  //   } else if (timer_length > 0){
  //     Serial.print("[MAIN] Object placed starting timer");

  //     timer_running = true;
  //     last_tick = current_tick;
  //   }

  // } else {
  //   if(remaining_sec > 0) { 

  //     if(current_tick - last_tick >= 1000) {
  //       last_tick += 1000;
  //       remaining_sec--;

  //       // update lcd
  //     }

  //     // object removed during timer
  //     if(dist > 2.5) {
  //       timer_running = false;
  //       Serial.print("[MAIN] Object removed");
  //     }

  //   } else {
  //     // time up

  //     // lcd_show_timeup();
  //     // buzzer_on();

  //     if(dist > 2.5) {
  //       // buzzer_off();
  //       timer_length = 0;
  //       timer_running = false;
  //     }
  //   }
  // }

  while(timer_length <= 25) {
    buttons_update_system(&timer_length, &brightness);
    lcd_set_brightness(brightness);
    lcd_update_screen(timer_length, 0);
  }


}

