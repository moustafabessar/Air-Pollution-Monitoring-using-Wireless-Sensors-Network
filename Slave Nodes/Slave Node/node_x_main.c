/*
 * node_x_main.c
 *
 * Created: 3/11/2017 10:42:38 PM
 *  Author: Moustafa Besar
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "xbee.h"
#include "DHT11.h"
#include "util/delay.h"
#include "UART.h"
#include "ADC.h"


int main(void)
{	
	ADC_Init();
	ADC_Enable();
	int x=0;
	uint8_t I_RH,D_RH,I_Temp,D_Temp,CheckSum;
	char data[5];
	DDRD |= (1<<Green_PIN) | (1<<Red_PIN);
	
	
	unsigned char SHOW [10];
	uart_init();
	_delay_ms(200);
	BufferInit(&buf);
	_delay_ms(200);
	uart_receive();
	_delay_ms(200);
	sei();
	
	struct xbee_tx_request r;
	unsigned char flag=0;
	while(1)
	{
		  timer_DELAY_18_ms();
		  timer_DELAY_18_ms();
		  timer_DELAY_18_ms();
		  timer_DELAY_18_ms();
		
		if(packet[16] == 0x35)
		{
			flag=1;
		}
		
		while(flag == 1)
		{
	    UCSRB &= ~(1<<RXCIE);
		ADC_Convert(1,&x);	
		Request();  /* send start pulse */
		Response();	 /* receive response */
		I_RH=Receive_data();  /* store first eight bit in I_RH */
		D_RH=Receive_data();  /* store next eight bit in D_RH */
		I_Temp=Receive_data();  /* store next eight bit in I_Temp */
		D_Temp=Receive_data();  /* store next eight bit in D_Temp */
		CheckSum=Receive_data();  /* store next eight bit in CheckSum */
		
		if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			PORTD |= 1<<Red_PIN;
			_delay_ms(500);
			PORTD &= ~(1<<Red_PIN);
			_delay_ms(500);
		}
		r.addr = 0x0013A20040DDE291 ;  //64 bit address xbee
		r.network = 0xFFFE;
		r.opts = 0x00;
		r.radius = 0x00;

		  itoa(I_Temp, SHOW, 10);
		  SHOW[2] = ' ';
		  itoa(I_RH, SHOW+3, 10);
		   SHOW[5] = ' ';
		  itoa(x, SHOW+6, 10);
		  r.data = (unsigned char*)strdup(SHOW);
		  r.len = strlen(SHOW);
		  
		  struct xbee_frame *f;
		  f = xbee_create_tx_request_frame(0x01, &r);
		  free(r.data);
		  
		  unsigned int size;
		  unsigned char *bytes;
		  bytes = xbee_frame_to_bytes(f, &size);
		  free(f);

		  int i =0;
		  while (i < size){
		  uart_send(bytes[i]);
		  i++;

          for (unsigned char j =0; j < counter; ++j)
          {
			packet[j] =0;
          }
		  
		  
		  counter = 0;
		  uart_receive();
		}
	}
	}
}
