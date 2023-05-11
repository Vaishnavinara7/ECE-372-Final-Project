// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//


#include <avr/io.h>
#include "switch.h"

/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 */
void initSwitchPB5(){

DDRB &= ~(1 << DDB5);
PORTB |= (1 << PORTB5);


PCICR |= (1 << PCIE0); // enable PCINT 0 - 7
PCMSK0 |= (1 << PCINT5); // enable PCINT3
}