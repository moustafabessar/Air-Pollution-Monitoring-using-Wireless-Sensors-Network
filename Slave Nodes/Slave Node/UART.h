#ifndef UART_H_
#define UART_H_

//define max buffer size
#define BUF_SIZE 25
#define LED_Direction DDRA
#define LED_PRT  PORTA
#define LED_PIN PA2
#define LED_PIN2 PA3
volatile unsigned char u8temp ,counter;
unsigned char cnt;
volatile unsigned char packet[BUF_SIZE];
//type definition of buffer structure
typedef struct{
	//Array of chars
	unsigned char buffer[BUF_SIZE];
	//array element index
	unsigned char index;
}u8buf;

//declare buffer
u8buf buf;


void BufferInit(u8buf *buf);
unsigned char BufferRead(u8buf *buf, unsigned char *u8data);
unsigned char BufferWrite(u8buf *buf, unsigned char u8data);

void uart_init(void);
void uart_send(unsigned char ch);
unsigned char uart_receive(void);

//void end_Receive();

#endif /* UART_H_ */
