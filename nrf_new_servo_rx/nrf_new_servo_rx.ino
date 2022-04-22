#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001"};

Servo servo1;
Servo servo2;
Servo mainEngine;

struct dato
{
  int x;
  int y;
  int throttle;
  bool button1;
  //bool button2;
};

void setup() {
  servo1.attach(9);
  servo2.attach(6);
  mainEngine.attach(3);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, addresses[0]);
  radio.setPALevel(RF24_PA_MAX);
}

void loop() {
  delay(5);
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()) {
      
      dato recievedData;
      
      radio.read(&recievedData, sizeof(recievedData));
      recievedData.x = map(recievedData.x, 0, 1024, 0, 180);
      recievedData.y = map(recievedData.y, 0, 1024, 0, 180);
      recievedData.throttle = map(recievedData.throttle, 0,1024, 0, 160);
      
      //Serial.println(recievedData.x);
      //Serial.println(recievedData.y);
      Serial.println(recievedData.throttle);
      
      if(recievedData.button1)
      {
        //servo1.write(160);
      }
      else
      {
        //servo1.write(90);
      }
      
      servo1.write(recievedData.x);
      servo2.write(recievedData.y);
      mainEngine.write(recievedData.throttle);
    }
  }
}
