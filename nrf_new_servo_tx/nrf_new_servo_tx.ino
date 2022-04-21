#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001"};

struct dato
{
  int x;
  int y;
  //int throttle;
  bool button1;
  //bool button2;
};
bool getButtonState(int num)
{
   return digitalRead(num);
}

void setup() {
  pinMode(2,INPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[0]);
  radio.setPALevel(RF24_PA_MAX);
}

void loop() {
  delay(5);
  dato dato2;
  bool mybutton = getButtonState(2);
  int analogOne = analogRead(A0);
  int analogTwo = analogRead(A1);
  radio.stopListening();
  dato2.button1 = mybutton;
  dato2.x = analogOne;
  dato2.y = analogTwo;
  Serial.print(dato2.button1);
  
  radio.write(&dato2, sizeof(dato2));
}
