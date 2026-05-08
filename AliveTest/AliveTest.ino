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
	static int i ;

	Serial.printf("I'm alive! %d\n\r", i++);
	delay (500) ;
}
