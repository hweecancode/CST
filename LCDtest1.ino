#include <LiquidCrystal.h>

// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(14, 27, 26, 25, 33, 32);

// Set countdown start time here
int minutes = 1;
int seconds = 30;

unsigned long lastUpdate = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Countdown:");
}

void loop() {
  unsigned long now = millis();

  // Update every 1000 ms
  if (now - lastUpdate >= 1000) {
    lastUpdate = now;

    // Display time
    lcd.setCursor(0, 1);

    if (minutes < 10) lcd.print("0");
    lcd.print(minutes);
    lcd.print(":");
    if (seconds < 10) lcd.print("0");
    lcd.print(seconds);
    lcd.print("   ");   // clear leftover chars

    // Decrement time
    if (seconds == 0) {
      if (minutes == 0) {
        // Countdown finished
        lcd.setCursor(0, 1);
        lcd.print("TIME UP!       ");
        while (1); // stop
      } else {
        minutes--;
        seconds = 59;
      }
    } else {
      seconds--;
    }
  }
}
