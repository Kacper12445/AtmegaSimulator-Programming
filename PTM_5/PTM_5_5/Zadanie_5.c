
/*
 * Kacper Kolodynski
 * 249018
 */

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

#ifndef sbi
#define sbi(reg,bit)		reg |= (_BV(bit))
#endif

#ifndef cbi
#define cbi(reg,bit)		reg &= ~(_BV(bit))
#endif

#ifndef tbi
#define tbi(reg,bit)		reg ^= (_BV(bit))
#endif

 //  Gotowe zaimplementowane;
 #define 	bit_is_set(sfr, bit)   (_SFR_BYTE(sfr) & _BV(bit))
 #define 	bit_is_clear(sfr, bit)   (!(_SFR_BYTE(sfr) & _BV(bit)))
 #define 	loop_until_bit_is_set(sfr, bit)   do { } while (bit_is_clear(sfr, bit))
 #define 	loop_until_bit_is_clear(sfr, bit)   do { } while (bit_is_set(sfr, bit))

#include "HD44780.h"

//komentarz
// MIN/MAX/ABS macros
#define MIN(a,b)			((a<b)?(a):(b))
#define MAX(a,b)			((a>b)?(a):(b))
#define ABS(x)				((x>0)?(x):(-x))

void ADC_init()
{
	sbi(ADMUX,REFS0);	//wybrane napiêcie AVCC
	sbi(ADCSRA,ADPS0);	//te 3 bity ustawiaj¹ podzielnik
	sbi(ADCSRA,ADPS1);	//czêstotliwoœci, dzielnik ustawiony
	sbi(ADCSRA,ADPS2);	// na 128
	sbi(ADCSRA,ADEN);	//uruchomienie uk³adu przetwornika
	//sbi(ADMUX,MUX3);	//pomiar dokonywany na ADC0

}

uint16_t ADC_10bit()
{
	sbi(ADCSRA,ADSC);
	loop_until_bit_is_clear(ADCSRA, ADSC);
	return ADC;
}

int Voltage_Meas(uint16_t result)
{
	return ((5.0*result)/1024.0)*100.0;		//przeliczanie wartosci otrzymanej z funkcji adc_10bit na wolty
}


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

uint8_t pomiary[20] EEMEM;			//tablica eeprom
int decy_sekundy = 0;				//decysekundy

int main() 
{
	TimerInit();						//ustawianie dzialanie timera
	LCD_Initalize();					//inicjalizjacja kontrolera HDD44780
	LCD_Home();							//Przywrócenie wartoœci wspó³rzêdnych wyœwietlacza
	ADC_init();
	sbi(PORTA, PA0);	//ustawiamy stan wysoki na wyjsciach do ktorych podlaczone sa potencjometry

	char text[30];						//bufor na tresc do wyœwietlenia
	char text2[30];						//bufor na tresc do wyœwietlenia
	int x = 0;		//zmienna pomocnicza w poruszaniu sie po tablicy eeprom
	int vol_1 = 0;		//napiecie na potencjometrze 1

	LCD_GoTo(0, 0);		//pierwsza linijka
	sprintf(text, "Welcome !");
	LCD_WriteText(text);
	double wyniki[10];
	int sekundy = 0;

	uint8_t l_pom = 0;
	sei();
	decy_sekundy = 0;
	while((l_pom/2) < 3)
	{	
		if(sekundy % 5 == 0 && sekundy > 0)				//wykonywanie co 5 sekund
		{
			sprintf(text, "Zapisano: %d.%d V", vol_1/100, vol_1%100); //wypisywanie wartosci pierwszego miernika
			wyniki[l_pom/2] = vol_1;		//zapisanie wyniki do tablicy
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteText(text);
			l_pom++;						// inkrementacja liczby pomiarów
			sekundy = decy_sekundy/20;		//obliczanie sekund
			_delay_ms(2000);

		}
		else
		{
			cbi(ADMUX, MUX0);	//ustawiamy pomiar na kanal 0
			vol_1 = Voltage_Meas(ADC_10bit());	//przypisujemy ten pomiar do zmiennej
			_delay_ms(50);

			sekundy = decy_sekundy/20;
			sprintf(text, "%d.%d V", vol_1/100, vol_1%100); //wypisywanie wartosci pierwszego miernika
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteText(text);

			LCD_GoTo(0,1);
			sprintf(text2, "%d s, l_pom: %d", sekundy, (l_pom/2)); //numeru pomiaru
			LCD_WriteText(text2);

		}
	}

	for(int i = 0; i < (l_pom/2); i++)
	{
		eeprom_write_byte(&pomiary[x], (int)(wyniki[i])/100);		//zapis w eeprom, liczba jednosci
		eeprom_write_byte(&pomiary[x+1],(int)(wyniki[i])%100);		//zapis w eeprom , liczba po przecinku
		LCD_Clear();
		LCD_GoTo(0,0);
		sprintf(text, "Zapisane Pomiary:"); //wypisywanie wartosci pierwszego miernika
		LCD_WriteText(text);
		LCD_GoTo(0,1);
		sprintf(text2, "Pomiar %d: %d.%dV",(i+1),(int)wyniki[i]/100, (int)wyniki[i]%100);
		LCD_WriteText(text2);
		x = x+2;
		_delay_ms(1000);
	}

}

ISR(TIMER1_COMPA_vect)
{
	decy_sekundy++;			//liczenie w zmiennej decysekund
}
