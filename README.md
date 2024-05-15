# VWCDCEmu
CD Changer emulator for VAG vehicles using attiny85.
Enables aux input for older VAG head units (tested on VW New Beetle head unit).
Tested with ATTiny85 dev board, should work with attiny13 also. No 3rd party dependencies, only single-way communication with head unit (playing CD0 TR01). Bit-banged SPI.

Wiring:


![image](https://github.com/nikolajovickg/VWCDCEmu/assets/8313782/67c03725-a713-4cc5-ad2a-a485122f9db8)


PB0 to DATA-IN

PB1 to CLOCK

Supply voltage from switched supply (must be regulated to 5V, since switched supply is 12V. AtTiny85 dev board has 7805, if using devboard it can be connected directly).

GND to chasis, since gnd in connector is just for audio ground.

AF-L AF-R COM. <- Audio left right and ground.

compiling and uploading:
```
avr-gcc -Wall -Os -mmcu=attiny85 -o cde.o cdc.c
avr-objcopy -j .text -j .data -O ihex cde.o cde.hex
avrdude -c usbasp -p t85 -U flash:w:cde.hex:i -U lfuse:w:0xC2:m -U hfuse:w:0xDF:m -U efuse:w:0xFF:m -U lock:w:0xFF:m
```
Thanks to:
https://www.mikrocontroller.net/topic/28549
https://schuett.io/2013/09/avr-raspberry-pi-vw-beta-vag-cdc-faker/
