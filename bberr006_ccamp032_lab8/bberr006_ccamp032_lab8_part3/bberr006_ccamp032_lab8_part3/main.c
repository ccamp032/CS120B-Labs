/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #8 Exercise #3
*
*	Exercise Description:
* Design a system where an LED is illuminated if enough light is detected from the photo resistor.
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
		if(x > max){
			max = x;
		}
		if (x >= max/2){
			tmpB = 0x01;
		}
		else{
			tmpB = 0x00;
		}

		PORTB = tmpB;

	}
}

