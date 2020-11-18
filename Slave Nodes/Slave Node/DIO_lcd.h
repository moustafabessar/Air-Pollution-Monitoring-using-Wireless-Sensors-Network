#ifndef INCFILE1_H_
#define INCFILE1_H_
#define E_portA *((volatile char *) 0x3B)
#define E_DDRA *((volatile char *) 0x3A)
#define E_PINA *((volatile char *) 0x39)

#define E_portB *((volatile char *) 0x38)
#define E_DDRB *((volatile char *) 0x37)
#define E_PINB *((volatile char *) 0x36)

#define E_portC *((volatile char *) 0x35)
#define E_DDRC *((volatile char *) 0x34)
#define E_PINC *((volatile char *) 0x33)

#define E_portD *((volatile char *) 0x32)
#define E_DDRD *((volatile char *) 0x31)
#define E_PIND *((volatile char *) 0x30)

/////////////protyping//////////////////
char DIO_WritePinVal(char PIN_NUM , char Val);
char DIO_WritePinDir(char PIN_NUM , char Val);
char DIO_ReadPinVal(char PIN_NUM , char *Val);
char DIO_WritePortVal(char PORT_NUM , char Val);
char DIO_ReadPortVal(char PORT_NUM,char *Val);
char DIO_WritePortDir(char PORT_NUM , char Val);
char DIO_TogglePinVal(char PIN_NUM);


/////////////configration////////////////
#define PORTA_init      0b00000000
#define PORTB_init      0b00000000
#define PORTC_init      0b00000000
#define PORTD_init      0b00000000

#define DDRA_init       0b11111111
#define DDRB_init       0b01111111
#define DDRC_init       0b00000001
#define DDRD_init       0b00000000

#endif /* INCFILE1_H_ */
