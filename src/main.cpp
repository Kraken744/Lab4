// Author:         
// Net ID:         
// Date:           
// Assignment:     Lab 4
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"
#include "adc.h"
#include "switch.h"
#include "pwm.h"

//#include "Arduino.h"


typedef enum stateType_enum {
  waitPress, debouncePress,
  waitRelease, debounceRelease
} stateType;

volatile stateType state = waitPress;

int main(){
  //Serial.begin(9600);
  initSwitchPB3();
  initADC0();
  initPWMTimer3();
  initPWMTimer4();
  sei();

  unsigned int result = 0;
  unsigned int motorsOn = 1;
  float voltage = 0;
  while(1){
    
    // read in ADCL first then read ADCH
    result = ADCL;
    result += ((unsigned int) ADCH) << 8;

    //need to check voltage for VCC
    voltage = result * (5.19/1024.0);

    //change duty cycles going to motors
    changeDutyCycle(voltage, motorsOn);
    

    switch(state) {
      case waitPress:         
     // Serial.println("waitPress");
     // Serial.flush();
        break;

      case debouncePress:
      //Serial.println("debouncepress");
      //Serial.flush();
        delayMs(10);
        state = waitRelease;
        break;

      case waitRelease:
      //Serial.println("waitRelease");
      //Serial.flush();
        break;

      case debounceRelease:
      //Serial.println("debounceRelease");
      //Serial.flush();
        delayMs(10);
        // if motors off, turn on
        if (motorsOn == 0){
          //turn motors on by switching motorsOn to high, and using changeDutyCycle
          motorsOn = 1;
          changeDutyCycle(voltage, motorsOn);
        }
        //if motors on, turn off
         else {
          //turn motors off by switching motorsOn to low, and using changeDutyCycle
          motorsOn = 0;
          changeDutyCycle(voltage, motorsOn);
         } 
        state = waitPress;
        break;
    }

  }

  return 0;
}

/* Implement an Pin Change Interrupt which handles the switch being
* pressed and released. When the switch is pressed and released, the motors turn on. If the motors were already on, they turn off.
*/
ISR(PCINT0_vect){

  if(state == waitPress) {
    state = debouncePress;
  }

  else if (state == waitRelease) {
    state = debounceRelease;
  }
}
