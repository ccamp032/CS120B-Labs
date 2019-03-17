/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*
*	Assignment: Lab #10 Exercise #2
*
*	Exercise Description:
* Modify the above example so the three LEDs light for 300 ms, while PB3's LED still blinks 1 second on and 1 second off.
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

enum BL_States { BL_SMStart, BL_LedOff, BL_LedOn } BL_State;
enum TL_States { TL_SMStart, TL_T0, TL_T1, TL_T2 } TL_State;
enum CL_States { CL_SMStart, Combine} CL_State;

unsigned char threeLed = 0x00;
unsigned char blinkLed = 0x00;

void TickFct_BlinkLed() {
	switch(BL_State){
		case BL_SMStart:
		BL_State = BL_LedOff;
		break;
		case BL_LedOff:
		BL_State = BL_LedOn;
		break;
		case BL_LedOn:
		BL_State = BL_LedOff;
		break;
		default:
		break;
	}
	switch(BL_State){
		case BL_SMStart:
		blinkLed = 0x00;
		break;
		case BL_LedOff:
		blinkLed = 0x00;
		break;
		case BL_LedOn:
		blinkLed = 0x01;
		break;
		default:
		break;
	}
}

void TickFct_ThreeLeds() {
	switch(TL_State){
		case TL_SMStart:
		TL_State = TL_T0;
		break;
		case TL_T0:
		TL_State = TL_T1;
		break;
		case TL_T1:
		TL_State = TL_T2;
		break;
		case TL_T2:
		TL_State = TL_T0;
		break;
		default:
		break;
	}
	switch(TL_State){
		case TL_SMStart:
		threeLed = 0x00;
		break;
		case TL_T0:
		threeLed = 0x01;
		break;
		case TL_T1:
		threeLed = 0x02;
		break;
		case TL_T2:
		threeLed = 0x04;
		break;
		default:
		break;
	}
}

void TickFct_CombineLeds() {
	switch(CL_State){
		case CL_SMStart:
		CL_State = Combine;
		break;
		case Combine:
		CL_State = Combine;
		break;
		default:
		break;
	}
	switch(CL_State){
		case CL_SMStart:
		PORTB = 0x00;
		break;
		case Combine:
		PORTB = (blinkLed << 3) | threeLed;
		break;
		default:
		break;
	}
}

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	
	unsigned long BL_elapsedTime = 1000;
	unsigned long TL_elapsedTime = 300;
	const unsigned long timerPeriod = 100;
	
	TimerSet(timerPeriod);
	TimerOn();
	BL_State = BL_SMStart;
	TL_State = TL_SMStart;
	CL_State = CL_SMStart;
	while (1) {
		if (BL_elapsedTime >= 1000) { // 1000 ms period
			TickFct_BlinkLed(); // Execute one tick of the BlinkLed synchSM
			BL_elapsedTime = 0;
		}
		if (TL_elapsedTime >= 300) { // 300 ms period
			TickFct_ThreeLeds(); // Execute one tick of the ThreeLeds synchSM
			TL_elapsedTime = 0;
		}
		TickFct_CombineLeds();
		while (!TimerFlag){}   // Wait for timer period
		TimerFlag = 0;         // Lower flag raised by timer
		BL_elapsedTime += timerPeriod;
		TL_elapsedTime += timerPeriod;
	}
}
