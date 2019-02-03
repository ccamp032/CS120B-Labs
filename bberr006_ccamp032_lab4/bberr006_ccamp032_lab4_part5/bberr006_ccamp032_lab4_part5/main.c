/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #4 Exercise #5
*
*	Exercise Description:
*Extend the above door to require the 4-button sequence #-X-Y-X rather
*than the earlier 2-button sequence. To avoid excessive states, store
*the correct button sequence in an array, and use a looping SM.
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/
 
#include <avr/io.h>

enum States {SMStart, S1, S2} state;

unsigned char tempA = 0x00;
unsigned char tempB = 0x00;

unsigned char theSequence[] = {0x04, 0x01, 0x02, 0x01};
unsigned char i = 0x00;

void Button_Sequence()
{
	if(tempA == theSequence[i])
	{
		++i;
	}
	else if(i != 0 && tempA == theSequence[i - 1])
	{
		//do nothing since user has not let go of previous input
	}
	else
	i = 0x00;
}

void Tick()
{
	switch(state)
	{
		case SMStart:
			state = S1;
			break;
		case S1:
			if(i == 4)
			{
				state = S2;
				i = 0;
			}
			else
				Button_Sequence();
			break;
		case S2:
			state = S1;
			break;
		default:
			state = SMStart;
			break;

	}
	switch(state)
	{
		case SMStart:
			break;
		case S1:
			break;
		case S2:
			if(tempB == 0x01)
				tempB = 0x00;
			else
				tempB  = 0x01;
			break;
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs, initialize to 1s
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s

	state = SMStart;

	while (1)
	{
		tempA = PINA;
		PORTB = tempB;
		Tick();
		PORTC = state;
	}
}