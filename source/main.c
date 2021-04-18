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

enum SM1_STATES { SM1_01, SM1_Wait10, SM1_10, SM1_Wait01 } SM1_STATE;
void Tick_Toggle() { 
switch(SM1_STATE) { 
    case SM1_01:
        if (tmpA) {
            SM1_STATE = SM1_Wait10;
        }
        else {
            SM1_STATE = SM1_01;
        }
        break;
    case SM1_Wait10:
        if (tmpA) {
            SM1_STATE = SM1_Wait10;
        }
        else {
            SM1_STATE = SM1_10;
        }
        break;
    case SM1_10:
        if (tmpA) {
            SM1_STATE = SM1_Wait01;
        }
        else {
            SM1_STATE = SM1_10;
        }
        break;
    case SM1_Wait01:
        if (tmpA) {
            SM1_STATE = SM1_Wait01;
        }
        else {
            SM1_STATE = SM1_01;
        }
        break;
    default:
        SM1_STATE = SM1_01;
        break;
}
switch(SM1_STATE) { 
    case SM1_01:
        tmpB = 0x01; // B = 01
        break;
    case SM1_Wait10:
        tmpB = 0x02; // B = 10
        break;
    case SM1_10:
        tmpB = 0x02; // B = 10
        break;
    case SM1_Wait01:
        tmpB = 0x01; // B = 01
        break;
    default:
        tmpB = 0xFF;
        break;
}
}

int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs, initalize to 1s.
        DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initalize to 0s.

    /* Insert your solution below */
    
    SM1_STATE = SM1_01;
    while (1) {
        tmpA = PINA;
        Tick_Toggle();      // Execute one SM tick
        PORTB = tmpB;
    }
    return 1;
}
