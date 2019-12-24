#!/bin/bash

hexfile="$1"

sudo gpio -g mode 22 out
sudo gpio -g write 22 0
sudo /usr/local/bin/avrdude -V -p t85 -P /dev/spidev0.0 -c linuxspi -b 10000 -U flash:w:$hexfile
sudo gpio -g write 22 1
