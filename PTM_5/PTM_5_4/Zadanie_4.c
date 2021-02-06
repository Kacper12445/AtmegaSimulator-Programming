#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <math.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "HD44780.h"

#ifndef _BV
#define _BV(bit)				(1<<(bit))
#endif
#ifndef sbi
#define sbi(reg,bit)		reg |= (_BV(bit))
#endif

#ifndef cbi
#define cbi(reg,bit)		reg &= ~(_BV(bit))

#endif

void TimerInit() {
	//Wybranie trybu pracy CTC z TOP OCR1A
	sbi(TCCR1B,WGM12);
	//Wybranie dzielnika czestotliwosci
	sbi(TCCR1B,CS12);
	//Zapisanie do OCR1A wartosci odpowiadajacej 0.1
	OCR1A = 3125;
	//Uruchomienie przerwania
	sbi(TIMSK,OCIE1A);
}

int decy_sekundy = 0;

int main()
{
	TimerInit();						//ustawianie dzialanie timera
	LCD_Initalize();
	LCD_Home();

	char text[20];
	char text2[20];
	int tablica[20];

	sei();
	decy_sekundy = 0;
	LCD_Clear();
	LCD_GoTo(0, 0);

	for(int i = 0; i < 20; i++)
	{
		tablica[i] = eeprom_read_byte((const uint8_t*)i);	//przepisywanie zawartosci pliku do tablicy
	}

	int adres = 0;
	while (tablica[adres] != 255)
	{
			LCD_Clear();
			LCD_GoTo(0, 0);
			sprintf(text, "%d", tablica[adres]);
			LCD_WriteText(text);

			LCD_GoTo(0, 1);
			sprintf(text2, "%d", adres);
			LCD_WriteText(text2);
			adres = decy_sekundy/10;		//zmienna przechowujaca adres komorki
			_delay_ms(50);
	}

	LCD_Clear();
	LCD_GoTo(0, 0);
	sprintf(text, "255");
	LCD_WriteText(text);
	LCD_GoTo(0, 1);
	sprintf(text2, "Koniec czytania z pliku");
	LCD_WriteText(text2);
}

ISR(TIMER1_COMPA_vect)
{
	decy_sekundy++;			//liczenie w zmiennej decysekund
}
