/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #8 Exercise #1
*
*	Exercise Description:
* Make sure your breadboard is wired according to the pre-lab.
* The potentiometer is used to adjust the voltage supplied to the micro controller for ADC.
* Design a system that reads the 10-bit ADC result from the ADC register, and displays the result on a bank of 10 LEDs.
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
while(1){
unsigned short x = ADC; //Value of ADC register is now stored in variable x
unsigned char first8 = (char)x;
PORTB = first8;
unsigned char last2 = (char)(x >> 8);
PORTD = last2;

}
}

