/*	Author: rmose005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;

enum SM1_STATES { SM1_PB0On, SM1_PB1On } SM1_STATE;
void Tick_Toggle() { 
switch(SM1_STATE) { 
    case SM1_PB0On:
        if (tmpA) {
            SM1_STATE = SM1_PB1On;
        }
        else {
            SM1_STATE = SM1_PB0On;
        }
        break;
    case SM1_PB1On:
        if (tmpA) {
            SM1_STATE = SM1_PB0On;
        }
        else {
            SM1_STATE = SM1_PB1On;
        }
        break;
    default:
        SM1_STATE = SM1_PB0On;
        break;
}
switch(SM1_STATE) { 
    case SM1_PB0On:
        tmpB = 0x01; // PB0 = 1, PB1 = 0
        break;
    case SM1_PB1On:
        tmpB = 0x01; // PB0 = 0, PB1 = 1
        break;
}
}

int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs, initalize to 1s.
        DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initalize to 0s.

/* Insert your solution below */
    while (1) {
        tmpA = PINA;
        SM1_STATE = SM1_PB0On;
        Tick_Toggle();      // Execute one SM tick
    }
    return 1;

}
