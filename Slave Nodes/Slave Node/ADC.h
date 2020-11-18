#ifndef ADC_H_
#define ADC_H_

#define E_ADMUX *((volatile char *) 0x27)
#define E_ADCSRA *((volatile char *) 0x26)
////////////////prototyping/////////////////
void ADC_Init(void);
char ADC_Convert(char channel_num ,int *ptr);
void ADC_Enable(void) ;
void ADC_disable(void) ;
void ADC_CLR_MUX();

///////////////// configuration////////////////
#define  ADC_ADMUX_INITVAL 0b00000000
#define  ADC_ADCSR_INITVAL 0b00000111
#define  ADC_RESOLUTION 10

#endif /* ADC_H_ */
