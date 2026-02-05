/*
 * test_code: Used to test the code block. Utilizes the Serial Monitor where
 *            users input a distance and a 4-bit binary number for the buttons.
 *            Will only run 4 test cases, and then the timer ends. This does
 *            not test the buzzer frequency.
 */

 // Initializations
int testCases = 0;           // Counter for test cases
int usr_start1 = -1;         // Confirm placement
int timerMinutes = 0;        // 5 or 10 min selected
int brightnessLevel = 1;     // Initial brightness
bool buzzerOn = false;       // Initial buzzer condition
float distance_cm;
int buttons_code_dsig;

void setup() {
  Serial.begin(9600);
  delay(3000);
  Serial.println("Code Block Interactive Validation");
  Serial.println("Thank you for using the Custom Study Timer!\n");
  Serial.println("Please place the phone down and enter 0 to confirm:");
}

void loop() {
  // User confirmation
  if (usr_start1 != 0) {
    while (Serial.available() == 0);
    usr_start1 = Serial.parseInt();
    Serial.readStringUntil('\n'); // clear buffer

    if (usr_start1 != 0) {
      Serial.println("Invalid input. Enter 0 to confirm placement.");
      Serial.println("Please place the phone down and enter 0 to confirm:");
      return; // wait again
    }

    // Ask for timer selection
    Serial.println("Select timer (5 or 10 minutes):");
    while (Serial.available() == 0);
    timerMinutes = Serial.parseInt();
    Serial.readStringUntil('\n'); // clear buffer

    if (timerMinutes != 5 && timerMinutes != 10) {
      Serial.println("Invalid selection. Enter 5 or 10.");
      usr_start1 = -1; // reset to ask placement again
      return;
    }

    Serial.print("Timer set to: ");
    Serial.print(timerMinutes);
    Serial.println(" minutes.\n");
    return; // Done setup, will start test cases next loop
  }

  // Test cases
  if (testCases >= 4) {
    buzzerOn = true;
    Serial.println("All test cases DONE!");
    Serial.println("Buzzer: ON");
    Serial.print("Brightness level: ");
    Serial.println(brightnessLevel);
    while (true); // stop program
  }

  testCases++;
  Serial.print("\n--- Test case ");
  Serial.print(testCases);
  Serial.println(" ---");

  // Input distance
  Serial.println("Enter distance (cm):");
  while (Serial.available() == 0);
  distance_cm = Serial.parseFloat();
  Serial.readStringUntil('\n'); // clear buffer

  if (distance_cm < 3 || distance_cm > 10) {
    Serial.println("ERROR: Distance must be between 3 and 10 cm");
    testCases--; // don't count invalid test
    return;
  }

  // Binary input for buttons
  Serial.println("Enter 4-bit buttons (e.g. 0110):");
  while (Serial.available() == 0);
  String buttonStr = Serial.readStringUntil('\n');
  buttonStr.trim();

  if (buttonStr.length() != 4) {
    Serial.println("ERROR: Must be exactly 4 bits");
    testCases--;
    return;
  }

  buttons_code_dsig = 0;
  for (int i = 0; i < 4; i++) {
    if (buttonStr[i] == '0' || buttonStr[i] == '1') {
      buttons_code_dsig = (buttons_code_dsig << 1) | (buttonStr[i] - '0');
    } else {
      Serial.println("ERROR: Only 0s and 1s allowed");
      testCases--;
      return;
    }
  }

  // Inputs being displayed
  Serial.print("Distance: "); Serial.print(distance_cm); Serial.print(" cm, Buttons: ");
  for (int i = 3; i >= 0; i--) Serial.print((buttons_code_dsig >> i) & 1);
  Serial.println();

  // Buzzer status
  buzzerOn = (distance_cm >= 5);

  // Timer status
  if (buzzerOn) {
    Serial.println("Timer: STOPPED");
  }
  else if (buttons_code_dsig == 0b1111 || buttons_code_dsig == 0b1110) {
    Serial.println("Timer: Counting down");
  }

  if (((buttons_code_dsig >> 3) & 1) == 0) {
    Serial.println("Timer: 5:00");
  }

  if (((buttons_code_dsig >> 2) & 1) == 0) {
    Serial.println("Timer: 10:00");
  }

  if (((buttons_code_dsig >> 1) & 1) == 0) {
    Serial.println("Timer: Increased by 1 min");
  }

  if (((buttons_code_dsig >> 0) & 1) == 0) {
    brightnessLevel++;
    if (brightnessLevel > 3) brightnessLevel = 1;
  }

  // Brightness display
  Serial.print("Brightness level: ");
  Serial.println(brightnessLevel);

  // Buzzer display
  Serial.print("Buzzer: "); Serial.println(buzzerOn ? "ON" : "OFF");
  Serial.println("-------------------------------");

  delay(500); // small delay before next test case
}
