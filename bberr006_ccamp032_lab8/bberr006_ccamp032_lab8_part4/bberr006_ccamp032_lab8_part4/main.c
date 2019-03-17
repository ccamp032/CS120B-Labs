/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #8 Exercise #4
*
*	Exercise Description:
* Design a system, using a bank of eight LEDs, where the number of LEDs illuminated is a representation of how much light is detected.
* For example, when more light is detected, more LEDs are illuminated.
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}



int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // A to
	DDRB = 0xFF; PORTB = 0x00; // B to output
	DDRD = 0xFF; PORTD = 0x00; // D to output
	ADC_init();
	unsigned short max = 200;
	unsigned char tmpB = 0x00;
	while(1){
		unsigned short x = ADC; //Value of ADC register is now stored in variable x
		if( x <= 0){
			tmpB = 0x00;
		}
		else if (x >= max){
			tmpB = 0x80;
		}
		else if( x >= 175){
			tmpB = 0x40;
		}
		else if( x >= 150){
			tmpB = 0x20;
		}
		else if( x >= 125){
			tmpB = 0x10;
		}
		else if( x >= 100){
			tmpB = 0x08;
		}
		else if( x >= 75){
			tmpB = 0x04;
		}
		else if( x >= 50){
			tmpB = 0x02;
		}
		else if( x < 50 ){
			tmpB = 0x01;
		}

		PORTB = tmpB;

	}
	
}

