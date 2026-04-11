#include <Arduino.h>
#include <functions.h>

void setup(){
	Serial.begin(9600);
	delay(2000);
	initPins();
	setAddress(0x0000);
}

uint16_t address = 0x0000;

void loop(){

	while (Serial.available()){
		byte data = Serial.read();

		if (data == 'S'){
			address = 0;
			return;
		}
		setData(address, data);
		address++;
	}
}