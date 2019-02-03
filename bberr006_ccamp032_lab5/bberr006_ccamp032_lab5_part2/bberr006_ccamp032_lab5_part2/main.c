/*	Partner(s) Name & E-mail: 
 * Blake Berry, bberr006@ucr.edu
 * Christian Campos , ccamp032@ucr.edu
 *	Lab Section: 022
 *	Assignment: Lab #5 Exercise #2
 *	Exercise Description: (From an earlier lab) Buttons are connected to PA0 and PA1. 
 *						  Output for PORTB is initially 0. Pressing PA0 increments
 *						  PORTB (stopping at 9). Pressing PA1 decrements PORTB (stopping at 0). 
 *						  If both buttons are depressed (even if not initially simultaneously), 
 *						  PORTB resets to 0. If a reset occurs, both buttons should be fully 
 *						  released before additional increments or decrements are allowed 
 *					      to happen. Use LEDs (and resistors) on PORTB. Use a state machine 
 *						  (not synchronous) captured in C.  
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */ 
#include <avr/io.h>

enum States {Start, Init, wait1, Inc, wait2, Dec, wait3, Reset, wait4} state;

#define A0 (~PINA & 0x01)
#define A1 (~PINA & 0x02)

unsigned char tempB = 0x00;

void Tick()
{
	switch(state)
	{
		case Start:
			state = Init;
			break;
		case Init:
			if(A0)
				state = wait1;
			else if(A1)
				state = wait2;
			else if(A0 && A1)
				state = wait3;
			else
				state = Init;
			break;
		case wait1:
			if(!A0)
			{
				state = Inc;
			}
			else if(A1)
				state = wait3;
			break;
		case Inc:
			state = Init;
			break;
		case wait2:
			if(!A1)
				state = Dec;
			else if(A0)
				state = wait3;
			break;
		case Dec:
			state = Init;
			break;
		case wait3:
			if(!A0 || !A1)
				state = Reset;
			break;
		case Reset:
			state = wait4;
			break;
		case wait4:
			if(!A0 && !A1)
				state = Init;
			break;
		default:
			state = Start;
			break;
		
	}
	switch(state)
	{
		case Start:
			break;
		case Init:
			break;
		case wait1:
			break;
		case Inc:
			if(tempB < 9)
				++tempB;
			break;
		case wait2:
			break;
		case Dec:
			if(tempB > 0)
				--tempB;
			break;
		case wait3:
			break;
		case Reset:
			tempB = 0x00;
			break;
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs, initialize to 1s
	DDRB = 0xFF; PORTB = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
	
	tempB = 0x00;
	state = Start;
	
	while (1)
	{
		Tick();
		PORTB = tempB;
	}
}

