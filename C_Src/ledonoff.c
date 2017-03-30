#include <stdio.h>
#include <wiringPi.h>

#define LED_OUT 0
#define LED_IN 12

int main()
{
	int state = 0;
	wiringPiSetup();
	printf("Init Complete\n\r");
	pinMode(LED_OUT,OUTPUT);
	pinMode(LED_IN,INPUT);
	pullUpDnControl(LED_IN,PUD_DOWN);
	while(1)
	{

if(digitalRead(LED_IN) == HIGH)
	{
	digitalWrite(LED_OUT, HIGH);
/*	if(state)
	{
	printf("HIGH\n\r");
	state = 0;
	}*/
	}

else
	{
	digitalWrite(LED_OUT, LOW);
/*	if(!state)
	{
	printf("LOW\n\r");
	state = 1;
	}*/
	}


}
	return 0;
}
