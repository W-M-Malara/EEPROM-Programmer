# EEPROM Programmer
This repo contains code on how to program an EEPROM without a EEPROM programming device.

You require:
1. A microcontroller (Arduino Nano is recommended)
2. 2 8-bit shift registers (SN74HC595N)
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

<img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/42a81e9d-2af6-4180-80b4-33fb6668c2d5" />


## How does it work?
The AT28C256 has 15 address pins, 8 data pins, write enable (WE), output enable (OE), chip enable (CE), VCC and GND. In total 28 pins that must be connected and controlled.
The 15 address pins are used to determine at which location in the EEPROM do we want to read or write. The address range of this EEPROM is from 0x0000 to 0x7FFF. Why not 0xFFFF? That is because we only have 15 pins available for the address. Each pin represents a bit therefore we can only have 15 bit addresses. If we had 16 pins then our data storage would increase from 32K to 65k address locations, doubling our EEPROM size.
The 8 data pins are used to read or write data into our chosen address. Each address contains 1 byte of data. 8 bits is extremely small... The highest 8 bit number is 255 so I don't recommend proving the Collatz Conjecture or any advanced mathematics using this EEPROM. Unless the user knows how to implement multi-byte arithmetic, go ahead!
Write enable, Output enable and Chip enable are pins for our chosen CPU. Those pins are responsible whether we want to write to the EEPROM, read from it or activate the chip itself. Those pins are controlled by the CPU usually when the EEPROM is implemented to a system.
The last two pins are VCC and GND which are used to power the chip. The chip cannot read or write data if its not powered but it can hold existing data. This specific EEPROM, under specified conditions in the datasheet, can hold data up to 10 years without power.

<img width="299" height="359" alt="image" src="https://github.com/user-attachments/assets/d4c8f26f-4a94-4961-8438-7ecc4c715b89" />


## The 8-bit shift registers (SN74HC595N)
The programmer uses 2 shift registers to output the address to the EEPROM. The Arduino Nano has 14 digital and 8 Analog pins that we can use. That makes us 6 pins short to program the EEPROM and that's why we need to use the 8 bit shift registers for our addresses. A 8-bit shift register is a chip that takes in serial data and transforms it into parallel data. A single shift register requires 5 inputs but we only need 3 for the microcontroller. The SER, SRCLK, RCLK while S̅R̅C̅L̅R̅ and OE will not be used by the microcontroller. The SER is responsible for letting us decide if we want our next bit to be 1 or 0 by providing high or low voltage. The SRCLK is responsible for shifting our current bit from SER down into the register, by doing that you also move down other bits by one position to the right. RCLK is will output all our shifted bits (stored inside our chip) to pins QA - QH simultaneously. This gives us 8 output pins! The SN74HC595N acts like a extension to program the EEPROM. But doesn't the EEPROM have 15 bit addresses? Thanks to the SN74HC595N design, we are able to connect both chips in such way that the bits from the first register will shift down to the second one therefore having 16 bits in total. For that we have QH' which copies the bit state of QH and passes it along to SER of our second chip. In the SN74HC595N datasheet it is also recommended to connect a 100 nf ceramic capacitor next to the VCC pin to filter out any electrical noise while using the chip.

<img width="350" height="240" alt="diagram of shift register" src="https://github.com/user-attachments/assets/355e9bc4-8828-4729-a652-bb5d27b35cd4" /> <img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/7a5b7922-95df-4a7f-a6c1-a0dfda0cf425" />


## Connections
Starting with the SN74HC595N. The OE is Output Enable and will be connected to GND. The bar at the top of OE means Active Low so in order to see output we have to connect the pin to GND. S̅R̅C̅L̅R̅ will be connected to VCC (we don't need to activate S̅R̅C̅L̅R̅ so it will go high). The SER, RCLK and SRCLK can be connected to any digital pin of the microcontroller, preferably next to each other. QH' will be connected to SER of our second chip. SRCLK and RCLK of our second chip will be connected to the same pins as our first SRCLK and RCLK. Start with the second chip and last output pin and connect them to the address pins of the EEPROM in ascending order. QH to A0, QG to A1, FQ to A2, etc. Once you finish with the second chip, you continue with the first chip but leave out QA since the EEPROM only needs 15 bits and our two chips produce 16 bit output.
