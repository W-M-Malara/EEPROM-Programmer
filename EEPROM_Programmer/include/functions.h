#pragma once
#include <Arduino.h>

#define SET 2
#define SRCLK 4
#define RCLK 3
#define WE 5
#define OE 6
#define STARTING_ADDRESS 0x0000


extern int Pins[];

void initPins();
void readROM(int addr1, int addr2);
void setAddress(int address);
void setData(int address, byte data);
void inputPins();
void outputPins();
void writeData(byte value);