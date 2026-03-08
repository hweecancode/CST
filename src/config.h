#ifndef CONFIG_H
#define CONFIG_H

// LCD Pins 
#define PIN_LCD_RS 23
#define PIN_LCD_E  22
#define PIN_LCD_D4 21
#define PIN_LCD_D5 19   
#define PIN_LCD_D6 18
#define PIN_LCD_D7 5

// LCD backlight and brightness
#define PIN_LCD_BACKLIGHT 2
#define LCD_PWM_FREQ 5000
#define LCD_PWM_RES 8

// HC-SR04 Distance Sensor
#define PIN_ULTRASONIC_TRIG 32
#define PIN_ULTRASONIC_ECHO 33

// 4-Button Module
#define PIN_BUTTON_K1 12
#define PIN_BUTTON_K2 14
#define PIN_BUTTON_K3 27
#define PIN_BUTTON_K4 26

// Buzzer
#define PIN_BUZZER 23
#define BUZZER_FREQ 440
#define BUZZER_RESOLUTION 8

#endif