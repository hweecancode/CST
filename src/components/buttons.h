#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

// Function declarations

void buttons_init();

void buttons_update_system(int* timer_len, int* brightness);

#endif