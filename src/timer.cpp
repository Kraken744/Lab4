// Description: This file implements functions that utilize the timers
//----------------------------------------------------------------------//

#include "timer.h"
#include <avr/io.h>

//1. Uses a timer (0 or 1) to debounce states

/* Initialize timer 0, does not turn on timer */
void initTimer0(){
    //timer0 to CTC Mode (010)
    TCCR0A &= ~(1<< WGM00);
    TCCR0A |= (1 << WGM01);
    TCCR0B &= ~(1<< WGM02); 
}

/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. 
*/
void delayMs(unsigned int delay){
    unsigned int count = 0;
      while(count < delay){ //while statement repeats 1ms delay by 100 or 200

        OCR0A = 250; //for 1ms

        // set the flagdown
        TIFR0 |= (1 << OCF0A);

        // clear the timer
        TCNT0 = 0;

        // turn on timer with prescaler as 64
        TCCR0B |= (1 << CS01)| (1 << CS00); TCCR0B &= ~(1<< CS02);

        // while flag is down do not do anything
        while(!(TIFR0 & (1 << OCF0A)));

        // turn clock off
        TCCR0B &= ~((1<< CS02) | (1 << CS01) | (1 << CS00));
        count++;
      }
}
