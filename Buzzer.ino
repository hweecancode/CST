/*
 * CST: Buzzer.ino
 * 2/1: Current code is assigned to Pin 23, and frequency is set to 440Hz for
 * the ER requirement. Utilizes ledc code, while buzzing off and on every second.
 *
 */

const int buzzerPin = 23;
const int frequency = 440;   // 440 Hz
const int resolution = 8;    // 8-bit PWM (0–255)

void setup() {
  // Attach PWM directly to the pin
  ledcAttach(buzzerPin, frequency, resolution);
}

void loop() {
  // Buzzer ON
  ledcWrite(buzzerPin, 128); // 50% duty cycle
  delay(1000);

  // Buzzer OFF
  ledcWrite(buzzerPin, 0);
  delay(1000);
}
