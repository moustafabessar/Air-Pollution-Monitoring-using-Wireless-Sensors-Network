#include <XBee.h>
#include <SoftwareSerial.h>
SoftwareSerial GPRS(10, 11); // RX, TX
XBee xbee = XBee();
int cnt=0;
XBeeResponse response = XBeeResponse();
ZBRxResponse rx = ZBRxResponse();
Rx16Response rx16 = Rx16Response();

uint8_t payload_1[] = {0x36}; //El k
uint8_t payload_2[] = {0x35};
uint8_t payload_3[] = {0x37};

// SH + SL Address of receiving XBee  0013A20040DDE291   0013A20040DDE28E  0013A20040DDE25C
XBeeAddress64 addr64_1 = XBeeAddress64(0x0013A200, 0x40DDE28E);  //with arduino
XBeeAddress64 addr64_2 = XBeeAddress64(0x0013A200, 0x40DDE268); //long button 
XBeeAddress64 addr64_3 = XBeeAddress64(0x0013A200, 0x40DDE25C);

ZBTxRequest zbTx1 = ZBTxRequest(addr64_1, payload_1, sizeof(payload_1));
ZBTxRequest zbTx2 = ZBTxRequest(addr64_2, payload_2, sizeof(payload_2));
ZBTxRequest zbTx3 = ZBTxRequest(addr64_3, payload_3, sizeof(payload_3));

String sample1, t_1, t_2, t_3;
String sample2, h_1, h_2, h_3;
String sample3, c_1, c_2, c_3;
String r = "B";
unsigned char gsm_Work= 0;
void setup() {
  
  // start serial
  Serial.begin(9600);
  Serial1.begin(9600);
  xbee.begin(Serial1);
    GPRS.begin(9600);               // the SIM900 baud rate 
  delay(1000);
     //delay(1000); 
 
     xbee.send(zbTx2);
}

void loop() {

               /******************* First node*************************/
       
  xbee.readPacket(100); 
    if (xbee.getResponse().isAvailable()) {
      cnt++; gsm_Work++;
              if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
        xbee.getResponse().getZBRxResponse(rx);
        for (int i = 0; i < rx.getDataLength(); i++) {
          sample1 += (char)rx.getData(i);
        }
        //Serial.println(sample1);
        Serial.println(sample1.substring(0,2));
        Serial.println(sample1.substring(3,5));
        Serial.println(sample1.substring(6));
        t_1 = sample1.substring(0,2);
        h_1 = sample1.substring(3,5);
        c_1 = sample1.substring(6);
                Serial.println(rx.getRemoteAddress16(),HEX);
              }
              /******************* Second node*************************/
         delay(3000);
        if(cnt==1)
        {
          cnt++; gsm_Work++;

          xbee.send(zbTx1);
          xbee.readPacket(100); 
    if (xbee.getResponse().isAvailable()) {
              if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
        xbee.getResponse().getZBRxResponse(rx);
        for (int i = 0; i < rx.getDataLength(); i++) {
          sample2 += (char)rx.getData(i);
        }
        //Serial.println(sample2);
        Serial.println(sample2.substring(0,2));
        Serial.println(sample2.substring(3,5));
        Serial.println(sample2.substring(6));
        t_2 = sample2.substring(0,2);
        h_2 = sample2.substring(3,5);
        c_2 = sample2.substring(6);
        Serial.println(rx.getRemoteAddress16(),HEX);
          }  
        }
    }
       /***************************** Third node ***********************/
         delay(3000);
    if(cnt>1)
    {  cnt  -=2 ; gsm_Work++;
      Serial.begin(9600);
           Serial1.begin(9600);
           xbee.begin(Serial1);
           xbee.send(zbTx3);
          xbee.readPacket(100); 
    if (xbee.getResponse().isAvailable()) {
              if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
        xbee.getResponse().getZBRxResponse(rx);
        for (int i = 0; i < rx.getDataLength(); i++) {
          sample3 += (char)rx.getData(i);
        }
        //Serial.println(sample3);
        Serial.println(sample3.substring(0,2));
        Serial.println(sample3.substring(3,5));
        Serial.println(sample3.substring(6));
        t_3 = sample3.substring(0,2);
        h_3 = sample3.substring(3,5);
        c_3 = sample3.substring(6);
        //Serial.println(cnt);
        Serial.println(rx.getRemoteAddress16(),HEX);
         delay(3000);   SubmitHttpRequest();
          }
        } 
      }
      /*  delay(6000);
      if(gsm_Work == 3)
       SubmitHttpRequest();  */
    }
    /**************************** Error Check********************/
    else if (xbee.getResponse().isError()) {
      Serial.println("Error reading packet.  Error code: ");  
      Serial.println(xbee.getResponse().getErrorCode());
  } 
  delay(100);
}

void SubmitHttpRequest()
{
 
  GPRS.println("AT+CSQ"); // Signal quality check

  delay(1000);
 
  ShowSerialData();// this code is to show the data from gprs shield, in order to easily see the process of how the gprs shield submit a http request, and the following is for this purpose too.
  
  GPRS.println("AT+CGATT?\r\n"); //Attach or Detach from GPRS Support
  delay(1000);
 
  ShowSerialData();
  GPRS.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SA0PBR, the connection type is using gprs
  delay(1000);
 
  ShowSerialData();
 
  GPRS.println("AT+SAPBR=3,1,\"APN\",\"CMNET\"");//setting the APN, Access point name string
  delay(2000);
 
  ShowSerialData();
 
  GPRS.println("AT+SAPBR=1,1");//setting the SAPBR
  delay(1000);
 
  ShowSerialData();
 
  GPRS.println("AT+HTTPINIT"); //init the HTTP request
  delay(1000); 
  ShowSerialData();

  GPRS.println("AT+HTTPPARA=\"CID\",1");
  delay(1000);
  ShowSerialData();


 GPRS.println("AT+HTTPPARA=\"URL\",\"http://34.209.130.165:5000/?t=["+t_1+","+t_2+","+t_3+"]"+"&h=["+h_1+","+h_2+","+h_3+"]"+"&c=["+c_1+","+c_2+","+c_3+"]"+"&r="+r+"\"");
   delay(800);
  ShowSerialData();

  GPRS.println("AT+HTTPACTION=0");//submit the request 
  delay(10000);  //the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  GPRS.println("AT+HTTPREAD"); 
  ShowSerialData();
  //GPRS.println("\"\r\n");
 
  GPRS.println("AT+HTTPTERM");// Terminate the connection
  delay(300);
  ShowSerialData();
 
  GPRS.println("");
  delay(100);
}
 
void ShowSerialData()
{
  while(GPRS.available()!=0)
    Serial.write(char (GPRS.read()));
}

