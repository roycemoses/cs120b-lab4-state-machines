/*	Author: rmose005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #5 
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
unsigned char arr[4] = {0x04, 0x01, 0x02, 0x01};
unsigned char i = 0x00;

enum SM1_STATES { SM1_Wait, SM1_IncWait, SM1_Inc, SM1_Lock, SM1_Toggle } SM1_STATE;
void Tick_Door() { 
    switch (SM1_STATE) { 
        case SM1_Wait:
            if (tmpA == arr[i]) { // you hit the mark! continue.
                SM1_STATE = SM1_IncWait;
            }
            else { // rip. you lost. reset (i = 0)
                SM1_STATE = SM1_Wait;
                i = 0;
            }
            // }
            if (tmpA == 0x80) {
                SM1_STATE = SM1_Lock;
            }  
            break;
        case SM1_IncWait:
            if (tmpA == arr[i]) {
                SM1_STATE = SM1_IncWait;
            }
            else {
                SM1_STATE = SM1_Inc; // continuing on!
                i = i + 1;
                if (i >= 4) {
                    SM1_STATE = SM1_Toggle; // you did it! toggle.
                }
            }
            break;
        case SM1_Inc:
            if (tmpA == 0x00) {
                SM1_STATE = SM1_Inc;
            }
            else {
                SM1_STATE = SM1_Wait;
            }
            break;
        case SM1_Lock:
            SM1_STATE = SM1_Wait; // Always go back to Wait
            break;
        case SM1_Toggle:
            SM1_STATE = SM1_Wait; // Always go back to Wait
            break;
        default:
            SM1_STATE = SM1_Wait;
            break;
    }

    switch(SM1_STATE) {
        case SM1_Wait:
            break;
        case SM1_IncWait:
            break;
        case SM1_Inc:
            break;
        case SM1_Lock:
            tmpB = 0x00;
            break;
        case SM1_Toggle:
            tmpB = (tmpB) ? 0x00 : 0x01;
            i = 0;
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
    
    SM1_STATE = SM1_Wait;
    while (1) {
        tmpA = PINA;
        Tick_Door();      // Execute one SM tick
        PORTB = tmpB;
    }
    return 1;
}
