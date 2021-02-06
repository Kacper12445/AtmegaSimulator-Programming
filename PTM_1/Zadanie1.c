/*
 * Zadanie1.c
 *
 *  Created on: Oct 19, 2020
 *      Author: Kacper
 */

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include <avr/sfr_defs.h>
#include <math.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#ifndef _BV
#define _BV(bit)				(1<<(bit))
#endif
#ifndef sbi
#define sbi(reg,bit)		reg |= (_BV(bit))
#endif

#ifndef cbi
#define cbi(reg,bit)		reg &= ~(_BV(bit))
#endif

#ifndef tbi
#define tbi(reg,bit)		reg ^= (_BV(bit))
#endif


#define 	bit_is_clear(sfr, bit)   (!(_SFR_BYTE(sfr) & _BV(bit)))



void First_mode()
{
	tbi(PORTD, PD6);
	_delay_ms(500);

}

void Second_mode()
{
	sbi(PORTD, PD6);
	_delay_ms(100);
}

void Third_mode()
{
	cbi(PORTD, PD6);
	_delay_ms(100);
}




int main()
{
	sbi(DDRD, PD6);
	sbi(PORTD, PD5);

	int mode = 1;

	while(1)
	{
		if (bit_is_clear(PIND, PD5))
		{
			while(bit_is_clear(PIND, PD5))
				_delay_ms(10);
			mode++;
		}

		switch(mode)
		{
		case 1:
			First_mode();
			break;

		case 2:
			Second_mode();
			break;

		case 3:
			Third_mode();
			break;
		default:
			mode = 1;
			break;
		}
	}
}

