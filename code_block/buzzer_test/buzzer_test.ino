/*
 * buzzer_test: Used to test the code block. Utilizes the Serial Monitor but also a
 *              passive buzzer that can adjust frequencies played from it. The
 *              program asks the user to enter a frequency, plays it through the buzzer
 *              and repeats.
 */

// Initializations
const int buzzerPin = 23;
int frequency;

void setup() {
  Serial.begin(9600);
  delay(3000);

  Serial.println("Enter frequency:");
}

void loop() {

  if (Serial.available() > 0) {

    frequency = Serial.parseInt();
    while (Serial.available()) Serial.read(); // clear buffer

    Serial.print("Playing: ");
    Serial.print(frequency);
    Serial.println(" Hz");

    // Changes tone
    tone(buzzerPin, frequency);

    delay(1000);

    // Stop buzzer
    noTone(buzzerPin);

    Serial.println("Enter another frequency:");
  }
}
