#/bin/bash!
modprobe bmp085-i2c
echo bmp085 0x77 > /sys/bus/i2c/devices/i2c-1/new_device
