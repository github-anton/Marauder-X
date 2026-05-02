/*
 * AliveTest.cpp
 *
 * For testing new boards.
 */


void setup()
{
	Serial.begin(115200);
}

void loop()
{
	while (true)
	{
		Serial.printf("I'm alive!\n\r");
		delay (500) ;
	}
}
