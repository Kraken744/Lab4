#ifndef PWM_H
#define PWM_H

#include <avr/io.h>

void initPWMTimer3();
void initPWMTimer4();
void changeDutyCycle(float voltage, unsigned int motorsOn);

#endif