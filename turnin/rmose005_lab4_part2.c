/*	Author: rmose005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
/*	Author: rmose005
 *	 *  Partner(s) Name: 
 *	  *	Lab Section:
 *	   *	Assignment: Lab #4  Exercise #2
 *	    *	Exercise Description: [optional - include for your own benefit]
 *	     *
 *	      *	I acknowledge all content contained herein, excluding template or example
 *	       *	code, is my own original work.
 *	        */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char tmpA = 0x00;
unsigned char tmpC = 0x00;

enum SM1_STATES { SM1_Init, SM1_Wait, SM1_Inc, SM1_Dec, SM1_Reset } SM1_STATE;
void Tick_Count() { 
    switch (SM1_STATE) { 
        case SM1_Init:
            SM1_STATE = SM1_Wait;
            tmpC = 0x07; // C = 7
            break;
        case SM1_Wait:
            if (tmpA == 0x00) {
                SM1_STATE = SM1_Wait;
            }
            else if (tmpA == 0x01) {
                if (tmpC < 9) {
                    SM1_STATE = SM1_Inc;
                    tmpC = tmpC + 1;
                }
                else {
                    SM1_STATE = SM1_Wait;
                }
            }
            else if (tmpA == 0x02) {
                if (tmpC > 0) {
                    SM1_STATE = SM1_Dec;
                    tmpC = tmpC - 1;
                }
                else {
                    SM1_STATE = SM1_Wait;
                }
            }
            else {
                SM1_STATE = SM1_Reset;
                tmpC = 0;
            }
            break;
        case SM1_Inc:
            if (tmpA == 0x01) {
                SM1_STATE = SM1_Inc;
            }
            else if (tmpA == 0x03) {
                SM1_STATE = SM1_Reset;
                tmpC = 0;
            }
            else {
                SM1_STATE = SM1_Wait;
            }
            break;
        case SM1_Dec:
            if (tmpA == 0x02) {
                SM1_STATE = SM1_Dec;
            }
            else if (tmpA == 0x03) {
                SM1_STATE = SM1_Reset;
                tmpC = 0;
            }
            else {
                SM1_STATE = SM1_Wait;
            }
            break;
        case SM1_Reset:
            if (tmpA == 0x03) {
                SM1_STATE = SM1_Reset;
            }
            else {
                SM1_STATE = SM1_Wait;
            }
            break;
        default:
            SM1_STATE = SM1_Init;
            break;
    }
}


int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs, initalize to 1s.
        DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initalize to 0s.

    /* Insert your solution below */
    
    SM1_STATE = SM1_Init;
    while (1) {
        tmpA = PINA;
        Tick_Count();      // Execute one SM tick
        PORTC = tmpC;
    }
    return 1;
}
