 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "DHT11.h"

unsigned char c=0;
void timer_DELAY_18_ms()
{
	
	//17.5 ms
	// clk/1024 prescaler normal mode
	TCCR0 |= (1<<CS00);
	TCCR0 &= ~(1<<CS01);
	TCCR0 |= (1<<CS02);
	TCNT0 = 114;
	while((TIFR & (1<<TOV0)) ==0);
	TCCR0 = 0;
	TIFR = 0x01;
}

void timer_DELAY_30_us()
{
	// clk/8 prescaler normal mode
	TCCR0 &= ~(1<<CS00);
	TCCR0 |= (1<<CS01);
	TCCR0 &= ~(1<<CS02);
	TCNT0 = 225;
	while((TIFR & (1<<TOV0)) ==0);
	TCCR0 = 0;
	TIFR = 0x01;
}

void Request()  /* Microcontroller send start pulse or request */
{
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN);  /* set to low pin */
	timer_DELAY_18_ms();
	//_delay_ms(20);  /* wait for 20ms */
	PORTD |= (1<<DHT11_PIN);  /* set to high pin */
}

void Response()  /* receive response from DHT11 */
{
	DDRD &= ~(1<<DHT11_PIN);
	while(PIND & (1<<DHT11_PIN));
	while((PIND & (1<<DHT11_PIN))==0);
	while(PIND & (1<<DHT11_PIN));
}

unsigned char Receive_data()  /* receive data */
{
	for (int q=0; q<8; q++)
	{
		while((PIND & (1<<DHT11_PIN)) == 0);  /* check received bit 0 or 1 */
		timer_DELAY_30_us();
		//_delay_us(30);
		if(PIND & (1<<DHT11_PIN))  /* if high pulse is greater than 30ms */
		c = (c<<1)|(0x01);  /* then its logic HIGH */
		else                       /* otherwise its logic LOW */
		c = (c<<1);
		while(PIND & (1<<DHT11_PIN));
	}
	return c;
}
