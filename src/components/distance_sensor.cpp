#include "distance_sensor.h"
#include "config.h"

void distance_init() {
    pinMode(PIN_ULTRASONIC_TRIG, OUTPUT);
    pinMode(PIN_ULTRASONIC_ECHO, INPUT);
    Serial.println("Distance sensor initialized");
}

float get_distance() {
    // start trigger low
    digitalWrite(PIN_ULTRASONIC_TRIG, LOW);
    delayMicroseconds(2);

    // send 10 microsecond high pulse
    digitalWrite(PIN_ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_ULTRASONIC_TRIG, LOW);

    
    long duration = pulseIn(PIN_ULTRASONIC_ECHO, HIGH);

    // datasheet equation: duration * speed of sound (0.0343 cm/us) / 2 
    float distance = (duration * 0.0343) / 2.0;

    return distance;
}