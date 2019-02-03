/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #4 Exercise #2
*
*	Exercise Description:
*	Buttons are connected to PA0 and PA1. Output for PORTC
*	is Initially 7. Pressing PA0 Increments PORTC once (stopping at 9).
*  Pressing PA1 decrements PORTC once (stopping at 0). If both buttons
*	are depressed (even if not Initially simultaneously), PORTC resets to 0.
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/

#include <avr/io.h>

// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

enum States {SMSTART, INIT, INCREMENT, DECREMENT, RESET} state;
	
unsigned char tempA = 0x00;
unsigned char tempC = 0x00;
	
void Tick() 
{
	switch(state)
	{
		case SMSTART:
			state = INIT;
			break;
		case INIT:
			if(tempA == 0x01)
				state = INCREMENT;
			else if(tempA == 0x02)
				state = DECREMENT;
			else if(tempA == 0x03)
				state = RESET;
			else
				state = INIT;
			break;
		case INCREMENT:
			state = INIT;
			break;
		case DECREMENT:
			state = INIT;
			break;
		case RESET:
			state = INIT;
			break;
		default:
			state = SMSTART;
			break;
	
	}
	switch(state)
	{
		case SMSTART:
			break;
		case INIT:
			break;
		case INCREMENT:
			if(tempC < 9)
				++tempC;
			break;
		case DECREMENT:
			if(tempC > 0)
				--tempC;
			break;
		case RESET:
			tempC = 0x00;
		default:
			break;
	}
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs, INITialize to 1s
    DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, INITialize to 0s
	
	tempC = 0x07;
	state = SMSTART;
	
    while (1) 
    {
		tempA = PINA;
		PORTC = tempC;
		Tick();
    }
}
