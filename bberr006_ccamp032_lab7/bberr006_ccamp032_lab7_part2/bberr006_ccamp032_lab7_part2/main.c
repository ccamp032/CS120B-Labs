/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #7 Exercise #2
*
*	Exercise Description:
* (Challenge) Extend the earlier light game to maintain a score on the LCD display. The initial score is 5.
* Each time the user presses the button at the right time, the score increments.
* Each time the user fails, the score decrements. When reaching 9, show victory somehow.
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/

#include <avr/io.h>
#include "timer.h"
#include "io.c"

enum States {start, init, play, wait1, wait2} state;

unsigned char ledCycles[] = {0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x04, 0x04, 0x04};
unsigned char button = 0x00;
unsigned char i = 0x00;
unsigned char score;

void Tick()
{
	button = (~PINA & 0x01);
	switch(state)
	{
		case start:
		state = init;
		break;
		case init:
		state = play;
		break;
		case play:
		state = (button) ? wait1 : play;
		break;
		case wait1:
		state = (button) ? wait1 : wait2;
		break;
		case wait2:
		state = (button) ? init : wait2;
		break;
		default:
		state = start;
		break;
	}
	
	switch(state)
	{
		case start:
		break;
		case init:
		i = 0;
		break;
		case play:
		i++;
		if(i == 9)
		i = 0;
		PORTB = ledCycles[i];
		break;
		case wait1:
		
		if(PORTB != 0x02)
		--score;
		else
		++score;
		break;
		case wait2:
		break;
		default:
		break;
	}
}

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00; // B outputs
	DDRA = 0x00; PORTA = 0xFF; // A inputs
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	
	state = start;
	
	// Initialize LCD display
	LCD_init();
	LCD_ClearScreen();
	score = 0x05;
	
	//100ms allows the tick rate to be fast enough to be more reliable on button presses
	// using an array that runs through each led 3 times in a row before moving to the next
	// keeps the lights lit for the requested 300 ms before moving onto the next
	TimerSet(100);
	TimerOn();
	
	while (1) {
		LCD_Cursor(1);
		if(score == 9) {
			LCD_DisplayString(1,"WINNER!!!");
			PORTB = 0x08;
		} else
		LCD_WriteData(score + '0');
		Tick();
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}

