/*	Partner(s) Name & E-mail: 
 * Blake Berry, bberr006@ucr.edu
 * Christian Campos , ccamp032@ucr.edu
 *	Lab Section: 022
 *	Assignment: Lab #2  Exercise #4 (Challenge)
 
 *	Exercise Description: 
 *	An amusement park kid ride cart has three seats, with 8-bit weight sensors connected to ports A, B, and C 
 *(measuring from 0-255 kilograms). Set PD0 to 1 if the cart's total passenger weight exceeds the maximum of 140 kg. 
 * Also, the cart must be balanced: Set port PD1 to 1 if the difference between A and C exceeds 80 kg. 
 * Can you also devise a way to inform the ride operator of the approximate weight using the remaining bits on D? 
 * (Interesting note: Disneyland recently redid their "It's a Small World" ride 
 * because the average passenger weight has increased over the years, causing more boats to get stuck on the bottom).
 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>


int main(void)
{
	
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs
    DDRC = 0x00; PORTC = 0xFF; // Configure port C's 8 pins as inputs
    DDRD = 0xFF; PORTD = 0x00; // Configure port D's 8 pins as outputs, initialize to 0s

	unsigned char tmpB = 0x00; // Temporary variable to hold the value of B
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
	unsigned char tmpC = 0x00; // Temporary variable to hold the value of C
	unsigned char tmpD = 0x00; // Temporary variable to hold the value of D
	
    unsigned long totalWeight = 0x00;
	unsigned long balanceAC = 0x00;
	unsigned long shiftedWeight = 0x00;
	
    while (1) 
    {
		
		tmpA = PINA;
		tmpB = PINB;
		tmpC = PINC;
		
		totalWeight = tmpA + tmpB + tmpC; 
		balanceAC = abs(tmpA - tmpC);
		shiftedWeight = totalWeight;
		if(totalWeight > 140 ) {
		tmpD = (tmpD & 0xFE) | 0x01;
		}
		
		if (balanceAC > 80) { // if balance weight over 80 set D1 to 1
			tmpD = (tmpD & 0xFD) | 0x02;
		}	
		PORTD = tmpD;
    }
}

