#include <SPI.h>
#include "mcp_can.h"


unsigned char Flag_Recv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];
int ID;


void setup()
{
    Serial.begin(115200);

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
        
        ID = CAN.getCanId();
         Serial.print (ID);
        if (ID == 0x01) 
        {
            for(int i = 0; i<len; i++)    // print the data
            {
            Serial.print(buf[i]);Serial.print("\t");
            }
        }
        else
          Serial.print ("Wrong ID \n");
          
        Serial.println();
    }
}
