#include <mcp_can.h>
#include <SPI.h>
unsigned char stmp1[8] = {0, 200, 150, 250, 100, 50, 180, 190};
String str;
unsigned char stmp0[1];
int pot = A0;
int out_pot, pot_value;


void setup()
{
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
       
    pot_value = analogRead(pot);
    out_pot = map(pot_value, 0, 1023, 0, 255);
    stmp0[0] = (unsigned char) out_pot;
    Serial.print(stmp0[0]);
    Serial.print("\n");
    CAN.sendMsgBuf(0x00, 0, 1, stmp0);   // send data:  id = 0x00, standrad flame, data len = 8, stmp: data buf
                              // when the delay less than 20ms, you shield use receive_interrupt
    delay(1);

   
}
