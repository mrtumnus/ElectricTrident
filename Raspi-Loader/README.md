Programming the ATtiny85 From Raspberry Pi
============================

Copied/derived from https://www.instructables.com/id/Programming-the-ATtiny85-from-Raspberry-Pi/

These instructions tell you how to setup and program the ATtiny85 microcontroller from a Raspberry Pi via the SPI interface.

Items required:
 * Raspiberry Pi
 * ATtiny85 chip
 * 5 x 1K resistors (or similar)
 * LED of your choice
 * A connection to the GPIO of the Pi, and a breadboard and wire.

Raspberry Pi Setup
============================

Download and build avrdude
----------------------------
 
  Run in a shell session:

    sudo apt-get install bison automake autoconf flex git gcc
    sudo apt-get install gcc-avr binutils-avr avr-libc
    git clone https://github.com/kcuzner/avrdude 
    cd avrdude/avrdude
    ./bootstrap && ./configure && sudo make install

Setup SPI on the GPIO
----------------------------

    sudo raspi-config

Enable SPI device in the Advanced Options

You can check this at the command line with lsmod, no need to reboot. (Maybe need to sudo modprobe spidev)

Download and build WiringPi for the gpio commands
----------------------------

    cd ~
    git clone git://git.drogon.net/wiringPi
    cd wiringPi
    ./build

Electrical Connections
============================

![Image](https://github.com/mrtumnus/firefly/raw/master/Misc/raspi-schematic.jpg)

Connect up the ATtiny85 to the Raspberry Pi GPIO as follows:

| Pi Pin | ATTiny Pin | Pin Usage |
|:------:|:----------:| --------- |
| 15 | 1 | GPIO22 to RESET |
| 17 | 8 | 3.3V |
| 19 | 5 | MOSI |
| 21 | 6 | MISO |
| 23 | 7 | SCLK |
| 25 | 4 | GND |

Test AVRDude Connection
============================

Test avrdude connection to the ATtiny85. GPIO pin 22 controls the ATTiny reset. This pin must be pulled low to program the chip.

    sudo gpio -g mode 22 out
    sudo gpio -g write 22 0
    sudo avrdude -p t85 -P /dev/spidev0.0 -c linuxspi -b 10000
    sudo gpio -g write 22 1

If the avrdude command reports success, then you're good to go.


