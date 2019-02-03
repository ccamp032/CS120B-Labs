/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #5 Exercise #1
*	Exercise Description:
*
*/

#include <avr/io.h>
enum States {Start, st_1, wait1, st_2, wait2, st_3, wait3} state;

unsigned char firstShow[] = {0x01, 0x01, 0x02, 0x02, 0x04, 0x04,  0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x10, 0x08, 0x04, 0x02};
unsigned char secondShow[] = {0x3F, 0x3F, 0x00, 0x2D, 0x2D, 0x00, 0x21, 0x21, 0x00};
unsigned char thirdShow[] = {0x21, 0x12, 0x08, 0x04, 0x08, 0x04, 0x08, 0x04, 0x08, 0x04, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x12};

unsigned char button = 0x00;

unsigned long i = 0x00;
unsigned char j = 0x00;

void Run_Pattern(unsigned char show[], unsigned char nElements)
{
	if(j == nElements)
	j = 0x00;
	
	for(i = 0; i < 2500; ++i)
	PORTB = show[j];
	
	++j;
}

void Tick()
{
	switch(state)
	{
		case Start:
		state = st_1;
		break;
		case st_1:
		if(button)
		{
			state = wait1;
		}
		break;
		case wait1:
		if(!button)
		{
			j = 0x00;
			state = st_2;;
		}
		break;
		case st_2:
		if(button)
		{
			state = wait2;
		}
		break;
		case wait2:
		if(!button)
		{
			j = 0x00;
			state = st_3;
		}
		break;
		case st_3:
		if(button)
		{
			state = wait3;
		}
		break;
		case wait3:
		if(!button)
		{
			j = 0x00;
			state = st_1;
		}
		break;
		default:
		state = Start;
		break;
		
	}
	switch(state)
	{
		case Start:
		break;
		case st_1:
		Run_Pattern(firstShow, 16);
		break;
		case st_2:
		Run_Pattern(secondShow, 9);
		break;
		case st_3:
		Run_Pattern(thirdShow, 23);
		break;
		default:
		break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs, initialize to 1s
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	
	state = Start;
	
	while (1)
	{
		button = ~PINA & 0x01;
		Tick();
	}
}
