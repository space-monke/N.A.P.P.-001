#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001"};

Servo servo1;
Servo servo2;

struct dato
{
  int x;
  int y;
  //int throttle;
  bool button1;
  //bool button2;
};

void setup() {
  servo1.attach(9);
  servo2.attach(6);
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
      
      dato potValue;
      
      radio.read(&potValue, sizeof(potValue));
      potValue.x = map(potValue.x, 0,1024, 0, 180);
      potValue.y = map(potValue.y, 0,1024, 0, 180);
      
      Serial.println(potValue.x);
      Serial.println(potValue.y);
      if(potValue.button1)
      {
        //servo1.write(160);
      }
      else
      {
        servo1.write(90);
      }
      servo1.write(potValue.x);
      servo2.write(potValue.y);
    }
  }
}
