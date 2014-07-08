C64 Cartridge Dumper
-------------------

As a software reverse engineer, we always look to push the limits... and finding an old cartridge in my garage, 
and no available ROM online, got me wondering whats inside it.

This dumper is a WIP, it doesn't support bank switching... but can rip standard 8k Carts without issue.

The provided C application is merely the Arduino serial example, with a few minor modifications.

The Arudino "CartDump" sketch is the heart of the ripping, setting the address pins as required, reading the data pins back and sending the resulting byte over USB to the serial listener C app.

Most of the information about the Expansion Port, is taken from http://www.c64-wiki.com/index.php/Expansion_Port

![Schematic of the Cart Dumper](https://raw.githubusercontent.com/segrax/Arduino-C64-Cartridge-Dumper/master/Schematic.png)

![Photo of completed device](https://github.com/segrax/Arduino-C64-Cartridge-Dumper/blob/master/Photos/Final.jpg)
