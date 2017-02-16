#include <SPI.h>
#include "mcp_can.h"
#include <SoftwareSerial.h>

#define txPin 2
#include <Servo.h> 
 
Servo myservo;  
int pos = 0;

SoftwareSerial LCD = SoftwareSerial(0, txPin);

const int LCDdelay=2;

// wbp: goto with row & column
void lcdPosition(int row, int col) {
  LCD.write(0xFE);   //command flag
  LCD.write((col + row*64 + 128));    //position 
  delay(LCDdelay);
}
void clearLCD(){
  LCD.write(0xFE);   //command flag
  LCD.write(0x01);   //clear command.
  delay(LCDdelay);
}
void backlightOn() {  //turns on the backlight
  LCD.write(0x7C);   //command flag for backlight stuff
  LCD.write(157);    //light level.
  delay(LCDdelay);
}
void backlightOff(){  //turns off the backlight
  LCD.write(0x7C);   //command flag for backlight stuff
  LCD.write(128);     //light level for off.
   delay(LCDdelay);
}
void serCommand(){   //a general function to call the command flag for issuing all other commands   
  LCD.write(0xFE);
}

unsigned char Flag_Recv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];



void setup()
{
    Serial.begin(115200);
    pinMode(txPin, OUTPUT);
    LCD.begin(9600);
    clearLCD();
    

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

        Serial.println("Temperature C1"); 
        Serial.println(buf[2]);
                
        Serial.println("Temperature C2"); 
        Serial.println(buf[5]);   
       
        Serial.println("Temperature Mean"); 
        Serial.println(buf[6]);
     }
     
        lcdPosition(0,0);
        LCD.print("Temperature:");
        lcdPosition(0,14);
        LCD.print(buf[6]);

        delay(100);
}


