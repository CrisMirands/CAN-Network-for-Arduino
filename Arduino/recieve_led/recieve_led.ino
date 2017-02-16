#include <SPI.h>
#include "mcp_can.h"


unsigned char Flag_Recv = 0;
unsigned char len = 0;
unsigned char buf[1];
int led = 3;
int i = 0;
char str[20];
int outputValue = 0;


void setup()
{
  pinMode(led, OUTPUT);  
  Serial.begin(115200);
    

START_INIT:

    if(CAN_OK == CAN.begin(CAN_10KBPS))                   // init can bus : baudrate = 500k
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
        Serial.print(buf[0]); 
              
        analogWrite(led, buf[0]);        
        Serial.println();
    }
}

