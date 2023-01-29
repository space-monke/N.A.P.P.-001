#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6]={"00001"};

Servo servo1;
Servo servo2;
Servo tailServo;
Servo mainEngine;

struct dato
{
	int x;
	int y;
	int throttle;
	bool forceStop;
};

void setup()
{
	servo1.attach(9);
	servo2.attach(6);
	tailServo.attach(5);
	mainEngine.attach(3);
	Serial.begin(9600);
	radio.begin();
	radio.openReadingPipe(0, addresses[0]);
	radio.setPALevel(RF24_PA_MAX);
}

void loop()
{
	delay(5);
	radio.startListening();
	if(radio.available())
	{
		while(radio.available())
		{
			dato recievedData;
			radio.read(&recievedData, sizeof(recievedData));
			recievedData.x = map(recievedData.x, 0, 1024, 150, 30);
			int s2 = map(recievedData.y, 0, 1024, 45, 135);
			int s1 = map(recievedData.y, 0, 1024, 135, 45);
			recievedData.throttle = map(recievedData.throttle, 0,1024, 0, 160);
			Serial.println(recievedData.throttle);
			if(recievedData.forceStop)
			{
				mainEngine.write(0);
			}
			servo1.write(s1);
			servo2.write(s2);
			tailServo.write(recievedData.x);
			mainEngine.write(recievedData.throttle);
		}
	}
}
