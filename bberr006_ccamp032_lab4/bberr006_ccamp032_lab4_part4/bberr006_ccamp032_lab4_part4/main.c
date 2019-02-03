/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #4 Exercise # 4
*	Exercise Description:
*	Exercise Description: Extend the above door so that it can also be locked by entering the earlier code.
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/

#include <avr/io.h>

enum States {SMStart, S1, S2, S3} state;

unsigned char tempA = 0x00;
unsigned char tempB = 0x00;

void Tick()
{
	switch(state)
	{
		case SMStart:
		state = S1;
		break;
		case S1:
		if(tempA == 0x04)
		state = S2;
		else
		state = S1;
		break;
		case S2:
		if(tempA == 0x02)
		state = S3;
		else
		state = S1;
		break;
		case S3:
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
		break;
		case S3:
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
