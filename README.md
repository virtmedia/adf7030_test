# adf7030_test
Experimental project to startup the ADF7030 transceiver.

ADF7030 is a modern transceiver integrated in one chip. It can work in 400, 800 and 900 MHz ranges. 
Here is a project using STM32F103C8T6 microcontroller to make that chip work.
The key element is the Src/adf7030.c and src/adf7030.h C library. The main task is to write that library.
The chip uses SPI bus to communicate with the uC. The library should be write in such a way, that it will be easy 
to migrate on a different hardware platform, like PIC or AVR. For that, all hardware specific functions 
(like SPI send byte) should be wrapped on the begining of the file, to be easy to adapt.

Together with the software project there is also a hardware with electronic schematic and PCB design. 
The first prototype was build sucessfully and it will be used to test the software library. 


