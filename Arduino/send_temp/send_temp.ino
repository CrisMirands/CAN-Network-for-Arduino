#include <mcp_can.h>
#include <SPI.h>
int pin1 = A1;    // select the input pin for the potentiometer
int pin2 = A2;
float tempV1, tempV2, tempK1, tempK2, tempC1, tempC2, tempM;  // variable to store the value coming from the sensor
unsigned char temps[7];


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
    // read the value from the sensor:
    tempV1 = analogRead(pin1); 
    tempK1 = (tempV1/1023)*500;
    tempC1 = tempK1 - 273.15;  
    
    tempV2 = analogRead(pin2); 
    tempK2 = (tempV2/1023)*500;
    tempC2 = tempK2 - 273.15;
    
    tempM = (tempC1 + tempC2)/2;
    
    temps[0] = (unsigned char) tempV1;
    temps[1] = (unsigned char) tempK1;
    temps[2] = (unsigned char) tempC1; 
    temps[3] = (unsigned char) tempV2;
    temps[4] = (unsigned char) tempK2;
    temps[5] = (unsigned char) tempC2;  
    temps[6] = (unsigned char) tempM;
    
    CAN.sendMsgBuf(0x00, 0, 8, temps);   // send data:  id = 0x00, standrad flame, data len = 8, stmp: data buf
    delay(1000);                          // when the delay less than 20ms, you shield use receive_interrupt
}
