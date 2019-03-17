/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #8 Exercise #2
*: Revise Part 1 by replacing the potentiometer with a photoresistor and 330
*ohm resistor. Take note of the highest ADC value displayed when the photoresistor is exposed to light, 
*and the lowest ADC value displayed when the photoresistor is deprived of all light. These values will be used for the remaining lab exercises.
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
	while(1){
		unsigned short x = ~ADC; //Value of ADC register is now stored in variable x
		unsigned char first8 = (char)x;
		PORTB = first8;
		unsigned char last2 = (char)(x >> 8);
		PORTD = last2;

	}
}

