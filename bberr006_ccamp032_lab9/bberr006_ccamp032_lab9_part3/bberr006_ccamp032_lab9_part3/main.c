/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*
*	Assignment: Lab #9 Exercise #3
*
*	Exercise Description:
*  Using the ATmega1284�s built in PWM functionality, design a system where a short, five-second melody,
*  is played when a button is pressed. NOTE: The melody must be somewhat complex (scaling from C to B is NOT complex).
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"


// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
void set_PWM(double frequency) {
	static double current_frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) { TCCR0B &= 0x08; } //stops timer/counter
		else { TCCR0B |= 0x03; } // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR0A = 0xFFFF; }
		
		// prevents OCR0A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR0A = 0x0000; }
		
		// set OCR3A based on desired frequency
		else { OCR0A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT0 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}

void PWM_on() {
	TCCR0A = (1 << COM0A0 | 1 << WGM00);
	// COM3A0: Toggle PB3 on compare match between counter and OCR0A
	TCCR0B = (1 << WGM02) | (1 << CS01) | (1 << CS00);
	// WGM02: When counter (TCNT0) matches OCR0A, reset counter
	// CS01 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR0A = 0x00;
	TCCR0B = 0x00;
}

enum States{init, off, play, wait1}state;


unsigned char button = 0x00;

const double melody[40] = {493.88, 523.25,329.63, 329.63, 329.63, 329.63,493.88, 523.25,329.63, 329.63, 329.63, 329.63,349.23, 349.23, 349.23, 349.23, 329.63, 329.63, 329.63, 329.63,493.88, 523.25,329.63, 329.63, 329.63, 329.63,493.88, 523.25,329.63, 329.63, 329.63, 329.63,349.23, 349.23, 349.23, 349.23, 329.63, 329.63, 329.63, 329.63};
unsigned char i = 0x00;

void tick(){
	button = ~PINA & 0x01;
	switch(state){ // Transitions
		case init:
		state = off;
		break;
		case off:
		if(button){
			state = play;
			i = 0;
		} else
		state= off;
		break;
		case play:
		if(i < 41){
			state = play;
			} else {
			state = wait1;
		}
		//i++;
		
		break;
		case wait1:
		if(button){
			state = wait1;
		}
		else
		state= off;
		break;
		default:
		break;
	}
	switch(state){ // State actions
		case init:
		break;
		case off:
		set_PWM(0);
		break;
		case play:
		set_PWM(melody[i]);
		++i;
		break;
		case wait1:
		set_PWM(0);
		break;
		default:
		break;
		
	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // A input initialized to 0xFF
	DDRB = 0xFF; PORTB = 0x00; // B output initialized to 0x00

	TimerSet(150);
	TimerOn();
	PWM_on();
	state = off;
	while(1){
		tick();
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}
