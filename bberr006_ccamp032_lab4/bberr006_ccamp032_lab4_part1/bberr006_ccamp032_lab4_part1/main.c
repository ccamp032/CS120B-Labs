/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #4 Exercise #1 
*	Exercise Description:
* PB0 and PB1 each connect to an LED, and PB0's LED is initially on. Pressing a button connected to PA0 turns 
* off PB0's LED and turns on PB1's LED, staying that way after button release. Pressing the button again turns off PB1's 
* LED and turns on PB0's LED. 
*/

#include <avr/io.h>

enum States { LED_SMStart, LED_s0, LED_s1 } State;

unsigned char button;
unsigned char tmpB;

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}




void Tick()
{
	switch(State) {   // Transitions
		case LED_SMStart:  // Initial transition
		State = LED_s0;
		break;

		case LED_s0:
		if (!button) {
			State = LED_s0;
		}
		else if (button) {
			State = LED_s1;
		}
		break;

		case LED_s1:
		if (!button) {
			State = LED_s0;
		}
		else if (button) {
			State = LED_s1;
		}
		break;

		default:
		State = LED_SMStart;
		break;
	} // Transitions

	switch(State) {   // State actions
		case LED_s0:
		SetBit(tmpB,0,1);
		SetBit(tmpB,1,0);
		break;

		case LED_s1:
		SetBit(tmpB,0,0);
		SetBit(tmpB,1,1);
		break;

		default:
		break;
	} // State actions
}

void main() {
	DDRA = 0x00; PORTA = 0xFF; // port A input
	DDRB = 0xFF; PORTB = 0x01; // B output
	State = LED_SMStart; // Indicates initial call

	while(1) {
		button = PINA & 0x00;
		Tick();
		PORTB = tmpB;
	}
}
