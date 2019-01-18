/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #3 Exercise #3
*	Exercise Description:
*
*In addition to the above, PA4 is 1 if a key is in the ignition, PA5 is one if a driver is seated, and 
*PA6 is 1 if the driver's seatbelt is fastened. PC7 should light a "Fasten seatbelt" icon
* if a key is in the ignition, the driver is seated, but the belt is not fastened. */
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
	unsigned char tmpA2 = 0x00;
	unsigned char tmpC = 0x00;  // Intermediate variable used for port updates
	//tmpA = PINA & 0xF0; // Mask the bits that I'm interested in

	
	while (1)
	{
		tmpA = PINA & 0x0F; // Mask the bits that I'm interested in
		tmpA2 = PINA & 0xF0; // Mask the bits that I'm interested in
		
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
		//// Part 3 below
		if(GetBit(tmpA2,4) && GetBit(tmpA2,5) && !GetBit(tmpA2,6))
		{
			tmpC = tmpC | 0x80;
		}
		PORTC = tmpC;
	}
}



