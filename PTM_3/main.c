#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <math.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

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


int columnBoard[] = {PD0, PD1, PD2, PD3}; 	//Tablica kolumn klawiatury
int rowBoard[] = {PD5, PD6, PD7, PD4};		//tablica wierszy klawiatury

int getButton()								//Funkcja przechwytujaca przycisk i numer mu przypisany
{

	int index = 0;							// poruszanie sie po klawiaturze w pierwszych 3 kolumnach
	int index2 = 12;						//sluzy do przypisania numeru 4 kolumnie klawiatury
	for(int i = 0; i < 4; i++)				//poruszanie sie po wierszach
	{
		sbi(PORTD, rowBoard[i]);			//ustawiamy stan wysoki na dany wiersz

		for(int j = 0; j < 4; j++)				//poruszanie sie po kolumnach
		{
			if(bit_is_set(PIND, columnBoard[j]))
			{
				_delay_ms(50);						//debouncing
				if(bit_is_set(PIND, columnBoard[j]))	//ustawiamy stan wysoki kolumny aby wiedziec gdzie dokladnie nastapilo klikniecie
				{
					LCD_GoTo(0, 1);
					while(bit_is_set(PIND, columnBoard[j]))			//debouncing
					{
						_delay_ms(1);
					}
					if(columnBoard[j] == PD3)						// jesli trzecia kolumna przypisujemy numer poprzez index2 ( >12)
					{
						cbi(PORTD, rowBoard[i]);
						return index2+1;
					}
					else
					{
						cbi(PORTD, rowBoard[i]);
						if(index == 10)
							return 0;
						else
							return index+1;							//indeksowanie od 1 a nie od 0
					}

				}
			}
				if(columnBoard[j] != PD3)							// nie chcemy indeksowac trzeciej kolumny
				{
					index++;
				}
				else
				{
					index2++;								//inkrementujemy za to index2
				}
		}
		cbi(PORTD, rowBoard[i]);
	}

	sbi(PORTC, PC0);										//uziemiony guzik
	if(bit_is_clear(PINC, PC0))
	{
		_delay_ms(100);
		return 20;
	}
	//cbi(PORTC, PC0);
	return -1;
}


int read_Result(int wynik[], char operacje[], int k)		// funkcja obliczajaca wynik
{
	int result = 0;
	int result2 = 0;

	int i;
	int j = 0;
	if (k == 1)			//gdy sa tylko dwie liczby
	{					//dzialania w przypadku wystepowania w tablicy tylko dwoch liczb
	    switch(operacje[j])
    		{
    		case '*':
    		    result = wynik[k-1] * wynik[k];
    			break;
    		case '+':
    			result = wynik[k-1] + wynik[k];

    			break;
    		case '-':
    			result = wynik[k-1] - wynik[k];
    			break;

    		}
    	return result;
	}
	else				//dzialania w przypadku gdy jest wiecej niz 2 liczby
	{
    	for(i = 1; i <= k; i++)
    	{
    		if (i == 1)						//dzialanie dla pierwszej petli
    		{
        		switch(operacje[j])			//rowniez przypisujemy znakom operacje
        		{							//dzialanie na dwoch pierwszych liczbach
        		case '*':
        		    result = wynik[i-1] * wynik[i];
        			break;
        		case '+':
        			result = wynik[i-1] + wynik[i];

        			break;
        		case '-':
        			result = wynik[i-1] - wynik[i];
        			break;

        		}
    		}
        		switch(operacje[j+1])			//dzialania na wyniku dwoch pierwszych liczb z trzecia liczba w tablicy
        		{
        		case '*':
        			result2 = result * wynik [i+1];
        			break;
        		case '+':
        			result2 = result + wynik [i+1];
        			break;

        		case '-':
        			result2 = result - wynik [i+1];
        			break;
        		}
        		//if(i != 1)
        	    result = result2;		// przypisujemy wartosc wyniku trzech liczb do zmiennej
    		j++;		//poruszamy sie po tablicy znakow + - *
    	}

            return result2;

	}

}









  int main() {
	LCD_Initalize();
	LCD_Home();

	char result[20];			//do wyswietlania na LCD
	int key;
	int number = 0;

	char operation = '0';

	int k = 0;
	int i = 0;
	int key_number = 0;
	int wynik[20]= {};				//tablica liczb przykladowy rozmiar
	char operacje[(int)sizeof(wynik)/sizeof(wynik[0])-1] = {};			//liczba znakow o jeden mniejsza niz liczba liczb w tablicy liczb



	while (1)
	{
		key = getButton();

		if(key != -1 && key !=20)
		{
			switch(key)
			{
			case 10:
				operation = '*';
				operacje[i] = operation;			//zapisujemy znak mnozenia do tablicy znakow operacji
				i++;								//przechodzimy na kolejne miejsce w tablicy
				k++;								//liczba o jeden mniejsza od liczby liczb w tablicy liczb ktora przekazujemy do funkcji read_result
				number = 0;							//po wpisaniu znaku, zerujemy numer wpisay wczesniej
				key_number = 0;						// nie naliczamy juz ilosci cyfr w jednej liczbie
				break;
			case 15:
				operation = '-';
				operacje[i] = operation;
				i++;
				k++;
				number = 0;
				key_number = 0;

				break;
			case 14:
				operation= '+';
				operacje[i] = operation;
				i++;
				k++;
				number = 0;
				key_number = 0;

				break;
			case 13:
				operation= 'C';
				for(int j = 0; j < (int)sizeof(wynik)/sizeof(wynik[0]); j++) //zerujemy funkcje znakow oraz liczb
				{
					wynik[j] = 0;
					operacje[j] = '0';
				}

				number = 0;		// zerujemy liczbe
				k = 0;		// zaczynamy zapelniac tablice liczb od poczatku
				i = 0;		// tak samo tablica znakow
				key_number = 0;	//zerujemy rowniez liczbe cyfr z ktorych sklada sie liczba

				break;
			case 16:		//gdy klikniemy "="
				number = read_Result(wynik, operacje, k);		//przypisujemy zmiennej wynik
				for(int j = 0; j < (int)sizeof(wynik)/sizeof(wynik[0]); j++)	//zerujemy wszystko ponownie
				{
					wynik[j] = 0;
					operacje[j] = '0';
				}

				k = 0;
				i = 0;
				wynik[k] = number;			//zapisujemy do tablicy liczb wynik aby moc  operowac na otrzymanym wyniku
				key_number = 0;
				break;
			default:			//gdy klikniemy jakas liczbe
				number = number*10+key;
				wynik[k] = number;		//zapisujemy do tablicy
				key_number++;			//z ilu cyfrowa jest liczba
				break;
			}
			LCD_Clear();
			LCD_GoTo(0, 0);

			if(key_number <= 3)		//jesli liczba jest >= 1000 to wyskoczy OVL
			{
				sprintf(result, "%u", number);		//wyswietlanie zmiennej przechowujacej liczbe wpisane lub wynik
				LCD_WriteText(result);
				LCD_GoTo(0, 1);
			}
			else
			{
				sprintf(result, "OVL");
				LCD_WriteText(result);
			}
		}
	}

		_delay_ms(150);
}
