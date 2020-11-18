#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/sleep.h>
#include "UART.h"

//unsigned char *frame = malloc(2*sizeof(unsigned char));

//initialize buffer
void BufferInit(u8buf *buf)
{
	LED_Direction |=1<<LED_PIN;
	counter=0;
	//set index to start of buffer
	buf->index=0;
}

unsigned char BufferWrite(u8buf *buf, unsigned char u8data)
{
	if (buf->index < BUF_SIZE)
	{
		buf->buffer[buf->index] = u8data;
		//increment buffer index
		buf->index++;
		return 0;
	}
	else return 1;
}	

unsigned char BufferRead(u8buf *buf, unsigned char u8data[])
{
	if(buf->index > 0)
	{
		buf->index--;
		u8data[cnt] = buf->buffer[buf->index];
		 //frame[cnt] = buf->buffer[buf->index];
		 cnt++;
		return 0;
	}
	else return 1;
}

ISR(USART_RXC_vect)
{
	  packet[counter]=UDR;
	  counter++;
	  //check if period char or end of buffer
}

void uart_init()
{
	UCSRB |= 1<<TXEN | 1<<RXEN ;            // Enable Transmitter & Receiver 

	UCSRC |= 1<<UCSZ1 | 1<<UCSZ0 |1<<URSEL; // No parity / activate UCSRC
	UBRRL = 0x33;
}


unsigned char uart_receive()
{
	UCSRB |= 1<<RXCIE;                // Enable RX Complete Interrupt
	
	//while(!(UCSRA & (1<<RXC)));
	//return UDR;
  return 0;
}

void uart_send(unsigned char ch)
{
	while(!(UCSRA & (1<<UDRE)));
	UDR = ch;
}
