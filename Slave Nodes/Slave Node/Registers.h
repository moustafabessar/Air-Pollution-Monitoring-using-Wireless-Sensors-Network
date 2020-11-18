/*
 * Hw_Reg.h
 *
 *  Created on: Mar 19, 2017
 *      Author: Dark
 */
#include "DataTypes.h"
#ifndef HW_REG_H_
#define HW_REG_H_
#define DDRA *((volatile U8*) 0x3A)
#define DDRB *((volatile U8*) 0x37)
#define DDRC *((volatile U8*) 0x34)
#define DDRD *((volatile U8*) 0x31)
#define DDR  ((volatile U8*) 0x3A)
#define PORTA *((volatile U8*) 0x3B)
#define PORTB *((volatile U8*) 0x38)
#define PORTC *((volatile U8*) 0x35)
#define PORTD *((volatile U8*) 0x32)
#define PORT ((volatile U8*) 0x3B)
#define PINA *((volatile U8*) 0x39)
#define PINB *((volatile U8*) 0x36)
#define PINC *((volatile U8*) 0x33)
#define PIND *((volatile U8*) 0x30)
#define PIN ((volatile U8*) 0x39)
#define MCUCR *((volatile U8*) 0x55)
#define GICR *((volatile U8*) 0x5B)
#undef SREG
#define SREG *((volatile U8*) 0x3F)
#define ADMUX *((volatile U8*) 0x27)
#define ADCSRA *((volatile U8*) 0x26)
#define ADCH *((volatile U8*) 0x25)
#define ADCL *((volatile U8*) 0x24)
#define ADCHL *((volatile U16*) 0x24)
#define SFIOR *((volatile U8*) 0x50)
#define TCCR0 *((volatile U8*) 0x53)
#define TCNT0 *((volatile U8*) 0x52)
#define TIMSK *((volatile U8*) 0x59)
#define OCR0 *((volatile U8*) 0x5C)
#define TIFR *((volatile U8*) 0x58)
#define TCCR1A *((volatile U8*) x04F)
#define TCCR1B *((volatile U8*) x04E)
#define OCCR1ALH *((volatile U16*) 0x4A)
#define ICR1LH *((volatile U16*) 0x46)
#define TCCR2 *((volatile U8*) 0x45)
#define UCSRA *((volatile U8*) 0x2B)
#define UCSRB *((volatile U8*) 0x2A)
#define UBRRL *((volatile U8*) 0x29)
#define UBRRH *((volatile U8*) 0x40)
#define UCSRC *((volatile U8*) 0x40)
#define UDR *((volatile U8*) 0x2C)
#define SPCR *((volatile U8*) 0x2D)
#define SPSR *((volatile U8*) 0x2E)
#define SPDR *((volatile U8*) 0x2F)
#endif /* HW_REG_H_ */
