/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #3 Exercise #2
*	Exercise Description:
* A car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty) and 15 (full). 
* A series of LEDs connected to PC5..PC0 should light to graphically indicate the fuel level.
* If the fuel level is 1 or 2, PC5 lights. If the level is 3 or 4, PC5 and PC4 light. Level 5-6 lights PC5..PC3. 
* 7-9 lights PC5..PC2. 10-12 lights PC5..PC1. 13-15 lights PC5..PC0. Also, PC6 connects to a "Low fuel" icon
* ,which should light if the level is 4 or less.  (The example below shows the display for a fuel level of 3).    
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/
#include <avr/io.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTC = 0xFF;
	
	unsigned char tmpA = 0x00; // Intermediate variable used for port updates
	unsigned char tmpC = 0x00;  // Intermediate variable used for port updates
	//tmpA = PINA & 0xF0; // Mask the bits that I'm interested in
	
    while (1) 
    {		
	    tmpA = PINA & 0xF0; // Mask the bits that I'm interested in
	
		if(tmpA == 0x01 || tmpA == 0x02 )
		{
		tmpC = 0x20;
		}
		else if(tmpA == 0x03 || tmpA == 0x04)
		{
		 tmpC = 0x30;	
		}
		else if(tmpA == 0x05 || tmpA == 0x06)		
		{
			tmpC = 0x38;
		}
		else if(tmpA >= 0x07 && tmpA <= 0x09 )
		{
		tmpC = 0x3C; // lights up PC5-PC2
		}
		else if(tmpA >= 0x0A && tmpA <= 0x0C)
		{
		tmpC = 0x3E;
		}
		else if(tmpA >= 0x0D && tmpA <= 0x0F)
		{
		tmpC = 0x3F;	
		}
	    else if(tmpA <= 4 )
	    {
		 tmpC = (tmpC | 0x40);
	    }
	    PORTC = tmpC;
  }
}

