#include <functions.h>


//Our data pins
int Pins[] = {8, 9, 10, 11, 12, 13, A0, A1};


//Pin initialization function
void initPins(){

	for (int i = 0; i < 5; i++){
		pinMode(2 + i, OUTPUT);
	}

	for (int i = 0; i < 8; i++){
		pinMode(Pins[i], INPUT_PULLUP);
	}

	digitalWrite(RCLK, LOW);
	digitalWrite(OE, LOW);
	digitalWrite(WE, HIGH);
}

//Hidden function. You can read the contents of your eeprom
void readROM(int addr1, int addr2){

	byte value;

	for (int i = 0; i < addr2 - addr1 + 1; i++){

		setAddress(addr1 + i);
		Serial.print("0x");
		Serial.print(addr1 + i, HEX);
		Serial.print("   ");
		for (int i = 7; i >= 0; i--){
			Serial.print(digitalRead(Pins[i]) ? 1 : 0);
			value <<= 1;
			value |= digitalRead(Pins[i]) ? 1 : 0;
		}
		Serial.print("   0x");
		Serial.print(value, HEX);
		Serial.print("   ");
		Serial.print(value);
		Serial.println();
	}
}

//Function to set our address, will not write to the eeprom
void setAddress(int addr){

	digitalWrite(OE, LOW);
	digitalWrite(WE, HIGH);
	shiftOut(SET, SRCLK, LSBFIRST, lowByte(addr));
	shiftOut(SET, SRCLK, LSBFIRST, highByte(addr));
	digitalWrite(RCLK, HIGH);
	digitalWrite(RCLK, LOW);
}

//Change pins to output
void outputPins(){
	for (int i = 0; i < 8; i++)
	{
		pinMode(Pins[i], OUTPUT);
	}
}

//Change pins to input
void inputPins(){
	for (int i = 0; i < 8; i++){
		pinMode(Pins[i], INPUT_PULLUP);
	}
}

//Output our data to the pins
void writeData(byte value){
	for (int i = 0; i < 8; i++){
		digitalWrite(Pins[i], (value >> i) & 1);
	}
}

//Function to write data at our address
void setData(int addr, byte data){

	setAddress(addr);
	delay(10);

	digitalWrite(OE, HIGH);
	digitalWrite(WE, HIGH);

	outputPins();
	writeData(data);

	digitalWrite(WE, LOW);
	delayMicroseconds(1);
	digitalWrite(WE, HIGH);
	delay(10);

	digitalWrite(OE, LOW);
	inputPins();
}