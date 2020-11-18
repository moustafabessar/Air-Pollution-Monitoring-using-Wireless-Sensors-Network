#include <avr/io.h>
#include "ADC.h"
#include "comman.h"
#include "DIO_lcd.h"
void ADC_Init(void){
	ADMUX=ADC_ADMUX_INITVAL;  //0b00000000
	ADCSRA=ADC_ADCSR_INITVAL; //0b00000111
	
}
void ADC_Enable(void){
	Set_bit(ADCSRA,7);
}
void ADC_CLR_MUX(){
	ADMUX=ADMUX&0b11100000;
}

char ADC_Convert(char channel_num,int *ptr){
	
	ADMUX =ADMUX|channel_num;
    Set_bit(ADCSRA,6);
	while (Get_bit(ADCSRA,6)==1)// hnb2a n3mlhA b interupt bounes
	{
	}
	if (ADC_RESOLUTION==10)
	{
		switch(Get_bit(ADMUX,5)){
			case 0:
			*ptr = ADCL;
			int x =(ADCH<<8);
			*ptr|=x;
			break;
			case 1:
			*ptr=ADCL;
			int y=ADCH;
			y=(y<<2);
			*ptr=(*ptr>>6);
			*ptr|=y;
			break;
		}
	}else if (ADC_RESOLUTION==8)
	{
		switch(Get_bit(ADMUX,5)){
			case 0:
			*ptr=ADCL;
			*ptr=(*ptr>>2);
			int z=ADCH;
			z=(z<<6);
			*ptr|=z;
			break;
			case 1:
			*ptr=ADCH;
			break;
		}
		
	}
	
}
void ADC_disable(void){
	clr_bit(ADCSRA,7);
}


