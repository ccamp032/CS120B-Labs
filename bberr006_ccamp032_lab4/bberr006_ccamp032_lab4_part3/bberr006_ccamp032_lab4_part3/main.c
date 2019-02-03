/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #4 Exercise #3
*
*	Exercise Description:
* A household has a digital combination deadbolt lock system on
* the doorway. The system has buttons on a keypad. Button 'X' connects
*to PA0, 'Y' to PA1, and '#' to PA2. Pressing and releasing '#', then
*pressing 'Y', should unlock the door by setting PB0 to 1. Any other
*sequence fails to unlock. Pressing a button from inside the house
*(PA7) locks the door (PB0=0). For debugging purposes, give each state
*a number, and always write the current state to PORTC (consider using
*the enum state variable). Also, be sure to check that only one button
*is pressed at a time.
*
*I acknowledge all content contained herein, excluding template or example
*code, is my own original work.
*/

#include <avr/io.h>

enum States {SMStart, S1, S2, S3, S4} state;

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
		else if(tempA == 0x80)
		state = S4;
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
		case S4:
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
		tempB = 0x01;
		break;
		case S4:
		tempB = 0x00;
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
