#include "pwm.h"
#include "timer.h"
#include <util/delay.h>

#include "Arduino.h"


//1. Uses 2 PWMS on timer 3 and timer 4.
//2. Has a changeDutyCycle function.


void initPWMTimer3(){   //pin 5 (OC3A) pin 5 works

//pin 5 set as output
DDRE |= (1 << DDE3);

//set as Fast Pwm 10 bit (WGM: 0111) 
TCCR3A |= (1 << WGM31) | (1 << WGM30);
TCCR3B |= (1 << WGM32);
TCCR3B &= ~(1 << WGM33);

//set as non-inverting (COM: 10)
TCCR3A |= (1 << COM3A1);
TCCR3A &= ~(1 << COM3A0);

//Set prescaler to 1 (001)
TCCR3B |= (1 << CS30);
TCCR3B &= ~(1 << CS31);
TCCR3B &= ~(1 << CS32);

//Set duty cycle to 100% (1023)
OCR3A = 1023;
}


void initPWMTimer4(){   //pin 6 (OC4A)

//pin 6 set as output
DDRH |= (1 << DDH3);

//set as Fast Pwm 10 bit (WGM: 0111)
TCCR4A |= (1 << WGM41) | (1 << WGM40);
TCCR4B |= (1 << WGM42);
TCCR4B &= ~(1 << WGM43);

//set as non-inverting (COM: 10)
TCCR4A |= (1 << COM4A1);
TCCR4A &= ~(1 << COM4A0);

//Set prescaler to 1 (001)
TCCR4B |= (1 << CS40);
TCCR4B &= ~(1 << CS41);
TCCR4B &= ~(1 << CS42);

//Set duty cycle to 100% (1023)
OCR4A = 1023;
}



void changeDutyCycle(float voltage, unsigned int motorsOn){
    
    if (motorsOn == 1){
        if (voltage < 1.5){
            //if voltage from potentiometer is near 0, left motor running at full power, right off
            OCR3A = 1023;
            OCR4A = 0;
        // Serial.println("at zero");
        // Serial.flush();
        }

        else if (voltage > 4.8){
            //Serial.println("over 4.8");
            // Serial.flush();
            //if voltage from potentiometer is near 5, left motor off, right motor running at full power
            OCR3A = 0;
            OCR4A = 1023;
        }

        else{
            //Serial.println("mid");
            //Serial.flush();
            //if voltage from potentiometer is ~2.5, both motors running at full power
            OCR3A = 1023;
            OCR4A = 1023;
        }
    }
    //if motors are off, does not do anything
    else {
        return;
    }
}