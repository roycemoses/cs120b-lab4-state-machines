/*	
 	Author: rmose005
	Partner(s) Name: 
 *	Lab Section:
 *	 *	Assignment: Lab #4  Exercise #4
 *	  *	Exercise Description: [optional - include for your own benefit]
 *	   *
 *	    *	I acknowledge all content contained herein, excluding template or example
 *	     *	code, is my own original work.
 *	      */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;

enum SM1_STATES { SM1_Wait, SM1_A2, SM1_ReleaseA2, SM1_A1, SM1_Lock } SM1_STATE;
void Tick_Lock() { 
    switch (SM1_STATE) { 
        case SM1_Wait:
            if (tmpA == 0x04) { // Y
                SM1_STATE = SM1_A2;
            }
            else if (tmpA == 0x80) { // Lock
                SM1_STATE = SM1_Lock;
                tmpB = 0x00;
            }
            else { // Back to itself
                SM1_STATE = SM1_Wait;
            }
            break;
        case SM1_A2:
            if (tmpA == 0x04) { // Y
                SM1_STATE = SM1_A2; // Stay
            }
            else if (tmpA == 0x00) { // Released Y
                SM1_STATE = SM1_ReleaseA2;
            }
            else if (tmpA == 0x80) { // Lock
                SM1_STATE = SM1_Lock;
                tmpB = 0x00;
            }
            else { // Wrong sequence, go back.
                SM1_STATE = SM1_Wait;
            }
            break;
        case SM1_ReleaseA2:
            if (tmpA == 0x00) { // Released
                SM1_STATE = SM1_ReleaseA2; // Stay
            }
            else if (tmpA == 0x02) { // A1. You win.
                SM1_STATE = SM1_A1;
            }
            else if (tmpA == 0x80) { // Lock
                SM1_STATE = SM1_Lock;
                tmpB = 0x00;
            }
            else { // Wrong sequence, go back.
                SM1_STATE = SM1_Wait;
            }
            break;
        case SM1_A1:
            SM1_STATE = SM1_Wait; // Always go back to Wait
            break;
        case SM1_Lock:
            SM1_STATE = SM1_Wait; // Always go back to Wait
            break;
        default:
            SM1_STATE = SM1_Wait;
            break;
    }

    switch(SM1_STATE) {
        case SM1_Wait:
            break;
        case SM1_A2:
            break;
        case SM1_ReleaseA2:
            break;
        case SM1_A1:
            tmpB = (tmpB) ? 0x00 : 0x01;
            break;
        case SM1_Lock:
            tmpB = 0x00;
            break;
    }
}


int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs, initalize to 1s.
        DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initalize to 0s.

    /* Insert your solution below */
    
    SM1_STATE = SM1_Wait;
    while (1) {
        tmpA = PINA;
        Tick_Lock();      // Execute one SM tick
        PORTB = tmpB;
    }
    return 1;
}
