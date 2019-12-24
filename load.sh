#!/bin/bash

hexfile=Arduino/ElectricTridentControl/ElectricTridentControl.ino.hex

scp $hexfile pi@raspberrypi.partridge.home:/home/pi/load.hex
ssh pi@raspberrypi.partridge.home /home/pi/dev/ElectricTrident/Raspi-Loader/load_hex.sh load.hex
