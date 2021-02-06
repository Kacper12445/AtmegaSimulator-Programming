
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


void diodaInit()
{
	sbi(DDRD, PD3);	//inicjalizowanie portod z diodami do pracy na wyjsciu
	sbi(DDRD, PD4);
	sbi(DDRD, PD5);
	sbi(DDRD, PD6);
}
void Reg_2_pol(uint8_t wartoscZadana, uint8_t wartoscRzeczywista)
{
	if(wartoscZadana > wartoscRzeczywista)
	{
		sbi(PORTD,PD6);
	}
	else if(wartoscZadana <= wartoscRzeczywista)
	{
		cbi(PORTD, PD6);
	}
	
}

void Reg_2_pol_his(uint8_t wartoscZadana, uint8_t wartoscRzeczywista)
{
	if((wartoscZadana - 10) > wartoscRzeczywista)
	{
		sbi(PORTD, PD5);
	}
	else if((wartoscZadana + 10) < wartoscRzeczywista)
	{
			cbi(PORTD, PD5);
	}
}

void Reg_3_pol(uint8_t wartoscZadana, uint8_t wartoscRzeczywista)
{
	if(wartoscZadana > wartoscRzeczywista)
	{
		cbi(PORTD,PD4);
		sbi(PORTD,PD3);
	}
	else if(wartoscZadana < wartoscRzeczywista)
	{
		cbi(PORTD, PD3);
		sbi(PORTD, PD4);
	}
	else if(wartoscZadana == wartoscRzeczywista)
	{
		cbi(PORTD, PD3);
		cbi(PORTD, PD4);
	}
}


int Regulator_PID(uint8_t wartoscZadana, uint8_t wartoscRzeczywista)
{
	int uchyb = wartoscZadana-wartoscRzeczywista;

	double Kp = 0.5;
	int wartSter;
	
		wartSter =  50+round(uchyb*Kp);
		if(wartSter > 100)
		{
			wartSter = 100;
		}
		else if(wartSter < 0)
		{
			wartSter = 0;
		}
		if(uchyb == 0)
		{
			wartSter = 50;
		}

	return wartSter;	
}

int main() 
{
	LCD_Initalize();					//inicjalizjacja kontrolera HDD44780
	LCD_Home();							//Przywrócenie wartoœci wspó³rzêdnych wyœwietlacza
	ADC_init();
		
	char text[30];						//bufor na tresc do wyœwietlenia
	char text1[30];						//bufor na tresc do wyœwietlenia
	char text2[30];						//bufor na tresc do wyœwietlenia
		
	int vol_1;		//napiecie na potencjometrze 1
	int vol_2;		//napiecie na potencjometrze 2
	
	diodaInit();
	int x;
		
	sbi(PORTA, PA0);	//ustawiamy stan wysoki na wyjsciach do ktorych podlaczone sa potencjometry
	sbi(PORTA, PA1);	//ustawiamy stan wysoki na wyjsciach do ktorych podlaczone sa potencjometry

	LCD_GoTo(0, 0);		//pierwsza linijka
	sprintf(text, "0.0V , 0%%");
	LCD_WriteText(text);
		
	LCD_GoTo(0, 1);		//dtuga linijka
	sprintf(text1, "0.0V , 0%%");
	LCD_WriteText(text1);
	_delay_ms(2500);		
	
	while(1) 
	{	
		cbi(ADMUX, MUX0);	//ustawiamy pomiar na kanal 0 
		vol_1 = Voltage_Meas(ADC_10bit());	//przypisujemy ten pomiar do zmiennej
		_delay_ms(100);
		
		sbi(ADMUX, MUX0);	//ustawiamy pomiar na kanal 1
		vol_2 = Voltage_Meas(ADC_10bit()); //przypisujemy ten pomiar do zmiennej
			
		
		sprintf(text, "%d.%d V , %d %%", vol_1/100, vol_1%100, vol_1/5); //wypisywanie wartosci pierwszego miernika
		sprintf(text1, "%d.%d V , %d %%", vol_2/100,vol_2%100, vol_2/5); //wypisywanie wartosci drugiego miernika
		LCD_Clear();
		LCD_GoTo(0,0);
		LCD_WriteText(text);
		LCD_GoTo(0,1);
		LCD_WriteText(text1);
		LCD_GoTo(20, 0);
		LCD_WriteText(text2);
	
		
		Reg_2_pol(vol_1/5, vol_2/5);		
		Reg_2_pol_his(vol_1/5, vol_2/5);
		Reg_3_pol(vol_1/5, vol_2/5);
		
		x = Regulator_PID(vol_1, vol_2);
		sprintf(text2, "%d%%", x);
		
	}

}