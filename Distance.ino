/*
 * CST: Distance.ino
 * 2/1: Code from https://projecthub.arduino.cc/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-7cabe1
 */

  // Initiate variables
  // const int trigPin =;
  // const int echoPin =;
  float duration, distance;

void setup() {
  // put your setup code here, to run once:
  // HC-SR04 pin assignments here
  // pinMode(trigPin, OUTPUT);
  // pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}
