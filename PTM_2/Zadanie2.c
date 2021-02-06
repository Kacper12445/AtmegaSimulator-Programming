/*
 * Zadanie2.c
 *
 *  Created on: Oct 21, 2020
 *      Author: Kapi
 */

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>

#ifndef _BV
#define _BV(bit)				(1<<(bit))
#endif

#ifndef sbi
#define sbi(reg,bit)		reg |= (_BV(bit))
#endif

#ifndef cbi
#define cbi(reg,bit)		reg &= ~(_BV(bit))
#endif



#define 	bit_is_clear(sfr, bit)   (!(_SFR_BYTE(sfr) & _BV(bit)))
#define 	bit_is_set(sfr, bit)   (_SFR_BYTE(sfr) & _BV(bit))




char dioda_tab[8] = {PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7};

void setLED(uint8_t led, uint8_t stan)
{
	if(stan == 1)
	{
		sbi(PORTD, dioda_tab[led]);
	}
	else if(stan == 0)
	{
		cbi(PORTD, dioda_tab[led]);
	}
}

void setAll(uint8_t stan)
{
	for(int k = 0; k < 8; k++)
	{
		setLED(k, stan);
	}
}

int columnBoard[] = {PC0, PC1, PC2, PC3};
int rowBoard[] = {PC5, PC6, PC7, PC4};

int getButton()
{

	int index = 0;
	for(int i = 0; i < 4; i++)
	{
		sbi(PORTC, rowBoard[i]);

		for(int j = 0; j < 4; j++)
		{
			if(bit_is_set(PINC, columnBoard[j]))
			{
				_delay_ms(50);
				if(bit_is_set(PINC, columnBoard[j]))
				{
					while(bit_is_set(PINC, columnBoard[j]))
					{
						_delay_ms(1);
					}
					if(columnBoard[j] == PC3)
					{
						cbi(PORTC, rowBoard[i]);
					}
					else
					{
						cbi(PORTC, rowBoard[i]);

						return index;
					}
				}
			}
				if(columnBoard[j] != PC3)
				{
					index++;
				}

		}
		cbi(PORTC, rowBoard[i]);
	}
	return -1;
}


void diodaInit()
{
	for(int i = 0; i < 8; i++)
	{
		sbi(DDRD, dioda_tab[i]);
	}
}

int main()
{
	diodaInit();
	int index;
	index = getButton();



	while(1)
	{
		index = getButton();

		if(index != -1)
		{
			if(index >= 0 && index < 8)
			{
				if(bit_is_set(PIND,dioda_tab[index]))
					setLED(index, 0);
				else
					setLED(index, 1);
			}
			if(index == 9)
				setAll(1);
			else if(index == 11)
				setAll(0);
		}
		_delay_ms(100);
	}
}



