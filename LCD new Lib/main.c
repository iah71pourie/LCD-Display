//---------------------------------------------------------------------------
// Titel		: Beispiel LCD-Display
//---------------------------------------------------------------------------
// Funktion    	: Demo-Beispiel für LCD-Display
// Schaltung    : PORTD.2 = RS, PORTD.3 = E, PORTD.4-7 = D4-7;
//---------------------------------------------------------------------------
// Prozessor 	:
// Takt		 	: 16 MHz
// Sprache   	: C
// Datum    	: 27.01.2020
// Version   	: 1.0
// Autor     	: Nunez
// Programmer	: ...
// Port		 	: ...
//----------------------------------------------------------------------
#define F_CPU 16000000UL	// Taktfrequenz des myAVR-Boards
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "lcd-routines.h"

uint8_t date[] = "DO 30.01 - 11:40";
uint8_t outside[] = "OUT:";
uint8_t inside[] = "IN:";
uint8_t insideTemp[] = "Temp: 21 °C -- Luftfeuchte: 30%";
uint8_t outsideTemp[] = "Bewoelkt --Temp: 9 °C -- Luftfeuchte: 70% -- Niederschlag: 0% -- Wind: 16km/h";

int main(void)
{
	lcd_init();
	
	lcd_clear();
	lcd_setcursor(8 - (uint8_t)(sizeof(date) / 2), 1);
	lcd_string(date);
			
	while(1)
	{
		textlauf(inside, insideTemp, sizeof(insideTemp), 2);
		
		textlauf(outside, outsideTemp, sizeof(outsideTemp), 2);
	}

	return 0;
}

void textlauf(uint8_t location[], uint8_t temp[], uint8_t tempsize, uint8_t row)
{
	uint8_t startj = 0;
	
	for (uint8_t i = 0; i < 15 + tempsize; i++)
	{
		lcd_clr_row(row);
		
		if(i <= 16)
		{
			lcd_setcursor(16 - i, row);
		}
		else
		{
			startj++;
			lcd_setcursor(0, row);
		}
		
		for (	uint8_t j = startj; j < tempsize - 1; j++)
		{
			if(j - startj <= 16)
			{
				if(temp[j] == '°')
				{
					lcd_data(0b11011111);
				}
				else
				{
					lcd_data(temp[j]);
				}
			}
		}
		
		lcd_setcursor(0,row);
		lcd_string(location);
		
		_delay_ms(500);
	}
}

void lcd_clr_row(uint8_t row)
{
	uint8_t clear[16] = "                ";
	lcd_setcursor(0, row);
	lcd_string(clear);
}