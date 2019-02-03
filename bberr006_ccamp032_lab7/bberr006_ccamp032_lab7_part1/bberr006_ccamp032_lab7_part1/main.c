/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #7 Exercise #1
*
*	Exercise Description:
* Buttons are connected to PA0 and PA1. Output PORTC and PORTD drive the LCD display,
*initially displaying 0. Pressing PA0 increments the display (stopping at 9). Pressing PA1 decrements the display (stopping at 0).
*If both buttons are depressed (even if not initially simultaneously), the display resets to 0. If a button is held,
*then the display continues to increment (or decrement) at a rate of once per second.
*Use a synchronous state machine captured in C.
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/

#include <avr/io.h>
#include "io.c"
#include "timer.h"

enum States {start, wait, increment, decrement, reset} state;

unsigned char buttonA0;
unsigned char buttonA1;
unsigned char count;

void Tick() {
	buttonA0 = (~PINA & 0x01);
	buttonA1 = (~PINA & 0x02);
	
	switch (state) {
		case start:
		state = wait;
		break;
		case wait:
		if(buttonA0 && !buttonA1) {
			state = increment;
			} else if(!buttonA0 && buttonA1) {
			state = decrement;
			} else if(buttonA0 && buttonA1) {
			state = reset;
		} else
		state = wait;
		break;
		case increment:
		if(buttonA0 && !buttonA1) {
			state = increment;
			} else if(buttonA0 && buttonA1) {
			state = reset;
		} else
		state = wait;
		break;
		case decrement:
		if(!buttonA0 && buttonA1) {
			state = decrement;
			} else if(buttonA0 && buttonA1) {
			state = reset;
		} else
		state = wait;
		break;
		case reset:
		state = (buttonA0 && buttonA1) ? reset : wait;
		break;
		default:
		state = start;
		break;
	}
	switch (state) { // State actions
		case wait:
		break;
		case increment:
		if(count < 9)
		++count;
		break;
		case decrement:
		if(count > 0)
		--count;
		break;
		case reset:
		count = 0;
		break;
		default:
		state = start;
		break;
		
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // A input
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines

	TimerSet(1000);
	TimerOn();
	
	// Initializes the LCD display
	LCD_init();
	LCD_ClearScreen();
	
	state = start;
	count = 0x00;
	
	while(1){
		LCD_Cursor(1);
		Tick();
		LCD_WriteData(count + '0');
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}

