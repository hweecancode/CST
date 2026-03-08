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
  buzzer_init();
  lcd_init();
  lcd_set_brightness(brightness);

  Serial.print("[MAIN] Printing start up \n");
  lcd_print_startup();
  Serial.print("[MAIN] Start up over\n");

}

void loop() {
  float dist = get_distance();
  Serial.printf("[MAIN] Distance: %f\n", dist);
  unsigned long current_tick = millis();

  if(!timer_running) {
    if(dist >= 4.5) {
      lcd_place_object();
    } else {
      Serial.printf("Scanning button inputs\n");
      buttons_update_system(&timer_length, &brightness);
      lcd_update_screen(remaining_sec / 60, remaining_sec % 60);

      if(timer_length > 0) {
        remaining_sec = timer_length * 60;
        Serial.printf("Timer length set: %d minutes. Starting...\n", timer_length);
        lcd_update_screen(remaining_sec / 60, remaining_sec % 60);
        timer_running = true;
        last_tick = current_tick;
        // lcd_start();
      }
      
    }
  } else { // timer runnning

    // check if one second has passed
    if(current_tick - last_tick >= 1000) {
      last_tick += 1000;

      // only reduce time if object is present
      if(dist < 4.5 && remaining_sec > 0) {
        remaining_sec--;
        lcd_update_screen(remaining_sec / 60, remaining_sec % 60);
      }
    }

    if(dist < 4.5) {
      int dummy = timer_length;
      
      buttons_update_system(&timer_length, &brightness);
      lcd_set_brightness(brightness);

      if(timer_length - dummy > 0 && timer_length - dummy < 4) {
        remaining_sec += (timer_length - dummy) * 60;
        lcd_update_screen(remaining_sec / 60, remaining_sec % 60);
      }
    }
    
    // sound buzzer if object not present
    if(dist > 4.5 && remaining_sec > 0) {
      Serial.print("Buzzer on\n");
      // buzzer_on();
      lcd_place_object_back();
    }


    // time out
    if (remaining_sec <= 0) {
        lcd_show_timeout();
        // buzzer_on();
        if (dist > 4.5) {
            timer_length = 0;
            timer_running = false;
        }
    }
  }

  // while(timer_length <= 25) {
  //   buttons_update_system(&timer_length, &brightness);
  //   lcd_set_brightness(brightness);
  //   lcd_update_screen(timer_length, 0);
  // }


}

