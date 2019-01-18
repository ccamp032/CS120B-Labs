/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #3 Exercise #4 (Challenge)
*	Exercise Description:
*(Challenge): Read an 8-bit value on PA7..PA0 and write that value on PB3..PB0PC7..PC4. That is to say,  
*take the upper nibble of PINA and map it to the lower nibble of PORTB, likewise take the lower nibble of PINA 
*and map it to the upper nibble of PORTC (PA7 -> PB3, PA6 -> PB2, … PA1 -> PC5, PA0 -> PC4).

*/
#include <avr/io.h>



void main() {
	DDRA = 0x00; PORTA = 0xFF; // port A input
	DDRB = 0xFF; PORTB = 0x00; // port B output
	DDRC = 0xFF; PORTC = 0x00; // port C output
	
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;
	
	while(1) {
		tmpB = (PINA & 0xF0) >> 4;
		tmpC = (PINA & 0x0F) << 4;
		
		PORTB = tmpB;
		PORTC = tmpC;
	}
}

