/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab # 2 Exercise # 2
*	Exercise Description:
*Port A's pins 3 to 0, each connect to a parking space sensor, 1 meaning a car is parked in the space,
*of a four-space parking lot. Write a program that outputs in binary on port C the number of available spaces
*(Hint: declare a variable "unsigned char cntavail"; you can assign a number to a port as follows:
* PORTC = cntavail;).
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/


#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	
	unsigned char tempA0 = 0x00;
	unsigned char tempA1 = 0x00;
	unsigned char tempA2 = 0x00;
	unsigned char tempA3 = 0x00;
	unsigned char cntavail = 4;
	
	while(1) {
		//read input
		tempA0 = PINA & 0x01; //read PA0
		tempA1 = PINA & 0x02; //read PA1
		tempA2 = PINA & 0x04; //read PA2
		tempA3 = PINA & 0x08; //read PA3
		
		//if PA0 is 1, decrement cntavail by 1 // Parking space 1 is taken
		if(tempA0 == 0x01) {
			--cntavail;
		}
		//if PA1 is 1, decrement cntavail by 1 // Parking space 2 is taken
		if(tempA1 == 0x02) {
			--cntavail;
		}
		//if PA2 is 1, decrement cntavail by 1 // Parking space 3 is taken
		if(tempA2 == 0x04) {
			--cntavail;
		}
		//if PA3 is 1, decrement cntavail by 1  // Parking space 4 is taken
		if(tempA3 == 0x08) {
			--cntavail;
		}
		//write input
		PORTC = cntavail;
		cntavail = 4; //reset cntavail
	}

}



