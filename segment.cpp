// Authors: Nawaf ALmutairi, Vaishnavi Narayanan
// Date:04/06/2023
// Assignment: Lab 4
//
#include <avr/io.h>
#include <util/delay.h>
#include "segment.h"

void initsegment(){
DDRC |= (0<<PORTC0) |(0<<PORTC1) |(0<<PORTC2) |(0<<PORTC3) |(0<<PORTC4) |(0<<PORTC5) |(0<<PORTC6) |(0<<PORTC7);
}

void turnOnSEGMENT(unsigned int segment){
switch (segment){
//0DONE
case 0:
PORTC |= (1<<PORTC0) |(1<<PORTC1) |(1<<PORTC2) |(1<<PORTC3) |(1<<PORTC4) |(1<<PORTC5);
PORTC &= ~(1<<PORTC6);
break;
//1DONE
case 1:
PORTC &= ~((1<<PORTC0) | (1<<PORTC3) | (1<<PORTC4) | (1<<PORTC5) | (1<<PORTC6));
PORTC |= ((1<<PORTC1) | (1<<PORTC2)) ;
break;
//2DONE
case 2:
PORTC &= ~((1<<PORTC2) |(1<<PORTC5));
PORTC |= ((1<<PORTC0) | (1<<PORTC1) | (1<<PORTC3) |(1<<PORTC4) | (1<<PORTC6));
break;
//3DONE
case 3:
PORTC &= ~((1<<PORTC4) |(1<<PORTC5));
PORTC |= ((1<<PORTC0) |(1<<PORTC1) |(1<<PORTC2) |(1<<PORTC3) |(1<<PORTC6));
break;
//4DONE
case 4:
PORTC &= ~((1<<PORTC0) |(1<<PORTC3) |(1<<PORTC4));
PORTC |= ((1<<PORTC1) |(1<<PORTC2) | (1<<PORTC5) | (1<<PORTC6));
break;
//5DONE
case 5:
PORTC &= ~((1<<PORTC1)|(1<<PORTC4));
PORTC |= ((1<<PORTC0) | (1<<PORTC2) | (1<<PORTC3) | (1<<PORTC5) | (1<<PORTC6));
break;
//6DONE
case 6:
PORTC &= ~(1<<PORTC1);
PORTC |=  ((1<<PORTC0) | (1<<PORTC2) | (1<<PORTC3) | (1<<PORTC4) | (1<<PORTC5) | (1<<PORTC6));
break;
//7DONE
case 7:
PORTC &= ~((1<<PORTC3) |(1<<PORTC4) |(1<<PORTC5) | (1<<PORTC6));
PORTC |= ((1<<PORTC0) |(1<<PORTC1) |(1<<PORTC2));
break;
//8DONE
case 8:
//PORTC |= ;
PORTC |= ((1<<PORTC0) |(1<<PORTC1) |(1<<PORTC2) |(1<<PORTC3) |(1<<PORTC4) |(1<<PORTC5)|(1<<PORTC6));
break;
//9DONE
case 9:
PORTC &= ~(1<<PORTC4);
PORTC |= ((1<<PORTC0) |(1<<PORTC1) |(1<<PORTC2) |(1<<PORTC3) | (1<<PORTC5)|(1<<PORTC6));
break;
default:
break;
}
}
