
//
// FILE: isys-6030.cpp
// AUTHOR: Paolo Visnoviz
// VERSION: 0.1
// PURPOSE: Arduino sample code for isys-6030 Innosent Radar
// 
// The code send start acquisition command, than reads the measures in single target mode.
//
// Warning: when isys-6030 is in acquisition mode, can consumes included ESP32, between 230 and 360mA at 5V. 
// Using a good USB cable is therefore recommended.
//
#include <Arduino.h>

#define Uart Serial2 // Define serial to use. Serial1 or Serial2
#define RXD2 16 // Define Uart RX pin
#define TXD2 17 // Define Uart TX pin

const byte RadarBuffLenght = 16;
unsigned char RadarBuff[RadarBuffLenght + 1];
uint32_t RadarDist;
char RadarD[11];
uint8_t StartR[] = {0x68,0x05,0x05,0x68,0x64,0x01,0xD1,0x00,0x00,0x36,0x16};
uint8_t SingleTargetR[] = {0x68,0x05,0x05,0x68,0x64,0x01,0xD9,0x01,0x00,0x3F,0x16};

void StartRadar() {
  Serial.println("Send start command");
  Uart.write(StartR, sizeof(StartR));
  Uart.flush();
  delay(400);
}

void ReadRadar() {
  Serial.println("Send command to read single target distance");
  Uart.write(SingleTargetR, sizeof(SingleTargetR));
  Uart.flush();
}

void setup() {
  Serial.begin(115200);
  Uart.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Uart Txd is on pin: "+String(TXD2));
  Serial.println("Uart Rxd is on pin: "+String(RXD2));
  StartRadar();
}

void loop() {
  if (Uart.available())
  {
    ReadRadar();
    Uart.readBytesUntil(0x16, RadarBuff, RadarBuffLenght);
    if ((RadarBuff[0] == 0x68) && (RadarBuff[6] == 0xD9))
    {
      RadarDist += (RadarBuff[11] << 24);
      RadarDist += (RadarBuff[12] << 16);
      RadarDist += (RadarBuff[13] << 8);
      RadarDist += (RadarBuff[14]);
      RadarDist = RadarDist/10000; // centimeters
      dtostrf(RadarDist, 8, 2, RadarD); // If needed to send over mqtt, this can be a good choice.
      Serial.print("cm : ");
      Serial.print(RadarDist, DEC);
      Uart.read(); //Empty serial buffer
      Serial.println(" ");
      RadarDist = 0;
    }
  }
    delay(50);
}