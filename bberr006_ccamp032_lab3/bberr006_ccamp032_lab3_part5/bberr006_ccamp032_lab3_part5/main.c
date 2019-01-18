/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #3 Exercise #5 (Challenge)
*	Exercise Description:
*(Challenge): A car's passenger-seat weight sensor outputs a 9-bit value (ranging from 0 to 511) and connects to input PD7..PD0PB0 on *
*the microcontroller. If the weight is equal to or above 70 pounds, the airbag should be enabled by setting PB1 to 1. **
*If the weight is above 5 but below 70, the airbag should be disabled and an "Airbag disabled" icon should light by setting PB2 to 1. *
*(Neither B1 nor B2 should be set if the weight is 5 or less, as there is no passenger). 
*/

#include <avr/io.h>


int main(void)
{
    DDRB = 0xFE; PORTB = 0x00; // port B output
	DDRD = 0x00; PORTD = 0xFF; // port D output
	
	unsigned char tmpB = 0x00;
	unsigned char tmpD = 0x00;
	unsigned char airBagLight = 0x00;
	
	
    while (1) {
		tmpB = PINB & 0x01;
		tmpD = PIND;
		
		if((tmpD >= 70) || (tmpD >= 69 && tmpB == 1)) {
			airBagLight = 0x02;
		} else if ((tmpD > 5 && tmpD < 70 && tmpB == 0) || (tmpD >= 2 && tmpB == 1)) {
			airBagLight = 0x04;
		} else {
			airBagLight = 0x00;
		}
		PORTB = tmpB | airBagLight;
    }
}

