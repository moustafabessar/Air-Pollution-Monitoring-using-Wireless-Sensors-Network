#ifndef DHT11_H_
#define DHT11_H_
// port D
#define DHT11_PIN 6
#define Green_PIN 5
#define Red_PIN   4

void timer_DELAY_18_ms();
void timer_DELAY_30_us();
void Request();
void Response();
unsigned char Receive_data();

#endif /* DHT11_H_ */
