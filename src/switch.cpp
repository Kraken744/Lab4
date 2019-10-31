#include "switch.h"
#include <avr/io.h>


//1. Uses a switch to turn motors on and off.
//2. Switch uses an ISR and is set up for debouncing


void initSwitchPB3(){
    
    //Set switch as pull-up enabled input
    PORTB |= (1 << PORTB3);
    DDRB &= ~(1 << DDB3);
  
    //enable PCINT 0 - 7
    PCICR |= (1<< PCIE0); 
    
    //enable PCINT3
	PCMSK0 |= (1<< PCINT3); 
}