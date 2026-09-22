# EEPROM Programmer
This repo contains code on how to program an EEPROM without a EEPROM programming device.

You require:
1. A microcontroller (Arduino uno is recommended)
2. 2 8bit shift registers (SN74HC595N)
3. 2 100 nf ceramic capacitors (labeled with 104)
4. A breadboard
5. Wires
6. Energy Drink of your choice

## The end result
<img width="4080" height="2296" alt="image" src="https://github.com/user-attachments/assets/fc112675-a0b0-4f46-8dd9-e532de4570b1" />


## What is a EEPROM?
An EPPROM stands for Electrically Erasable Programmable Read-Only Memory. EEPROMs are non-volatile therefore they keep data even when there's no power on.
But to store data in a EEPROM in the first place required you to have a programmer that knew the timings, voltage and sequence of each individual pin in order to store data.
A good example of a modern programmer can be the T48 which has a wide list of supported EEPROMS as well as MCU's such as the Atmega8A (Which im currently playing with).
For this project, the programmer will only program one specific EEPROM called the AT28C256.

<img width="1420" height="798" alt="image" src="https://github.com/user-attachments/assets/63cacf7c-baa1-425f-9e18-e413fa7428eb" />


## What is the AT28C256?
The AT28C256 is a 256K (32K x 8) EEPROM manufactured by the Atmel Corporation in 1988.
The EEPROM is now used by hobbyists to make retro computers. Paired with the classic MOS 6502 CPU or even the Intel 8080 CPU.
In the 'Features' heading of the documentation for the AT28C256 states that it has "Full Military and Industrial Temperature Ranges". Maybe it was used by the Military? Who knows...
The main reason why I chose this EEPROM is because I'm following along Ben Eaters tutorial on the 6502 computer to which he also made a video on how to make a programmer but I decided to figure it out the code by myself while I use the same parts as him.
