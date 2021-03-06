#include <SPI.h>
#include "mcp_can.h"
#include <Servo.h> 
 
Servo myservo;  
int i=10, pos = 0;     


unsigned char Flag_Recv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];



void setup()
{
    Serial.begin(115200);
    myservo.attach(9); 

START_INIT:

    if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
        goto START_INIT;
    }
}


void loop()
{
    
    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
      CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf
      Serial.println(buf[6]); 
   }
   if (buf[6] >= 40)
   { 
      if (pos>0 || pos<180)
      {
          pos=pos+i;    
          myservo.write(pos);               
          delay(250);                       
      }
      if (pos == 180)
          i=(-10);
      if (pos == 0)
          i=10;
   }
     myservo.write(pos); 
     delay(5);
}

