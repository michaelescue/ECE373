#!/bin/bash

rmmod YOUR_DRIVER_NAME
echo XXXX:XX:XX.X > /sys/module/e1000/drivers/pci\:e1000/bind
echo XXXX:XX:XX.X > /sys/module/e1000/drivers/pci\:e1000/unbind
insmod YOUR_DRIVER_NAME.ko
