/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab # 2 Exercise # 1
*	Exercise Description:
*Garage open at night-- A garage door sensor connects to PA0 (1 means door open),
* and a light sensor connects to PA1 (1 means light is sensed).
* Write a program that illuminates an LED connected to PB0 (1 means illuminate) if the garage door is open at night.
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	
	unsigned char tmpA0 = 0x00; // Temporary variable to hold the value of A0
	unsigned char tmpA1 = 0x00; // Temporary variable to hold the value of A1
	unsigned char tmpB = 0x00; // Temporary variable to hold the value of B

	
	while (1)
	{
		
		tmpA0 = PINA & 0x01;
		tmpA1 = PINA & 0x02;
		
		if( tmpA0 == 0x01 && tmpA1 == 0x00)
		{
			tmpB = (tmpB & 0xFE) | 0x01;
		}
		else
		{
			tmpB = (tmpB & 0xFE) | 0x00;
		}
		PORTB = tmpB;
	}
}


