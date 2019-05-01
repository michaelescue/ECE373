cd /dev/
rm hellokernel
rmmod hello_kernel
cd /home/michael/Documents/ECE373/Assignments/HW3/sourcefiles
make clean
echo  0000:00:03.0 > /sys/module/e1000/drivers/pci\:e1000/unbind
echo  0000:00:03.0 > /sys/module/e1000/drivers/pci\:e1000/bind
exit
