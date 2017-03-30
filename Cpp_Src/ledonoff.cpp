#include <iostream>
#include <wiringPi.h>

#define LED_OUT 0
#define LED_IN 12

using namespace std;


int main()
{
	wiringPiSetup();
	cout << "Init Complete"<< endl;
	pinMode(LED_OUT,OUTPUT);
	pinMode(LED_IN,INPUT);
	pullUpDnControl(LED_IN,PUD_DOWN);
	while(1)
{

if(digitalRead(LED_IN) == HIGH)
	{
	 digitalWrite(LED_OUT,HIGH);
	}

else
	{
	 digitalWrite(LED_OUT,LOW);
	}
}

return 0;
}
