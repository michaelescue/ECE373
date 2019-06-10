cd /home/michael/Documents/ECE373/Assignments/HW3/sourcefiles
make clean
make
echo  0000:00:03.0 > /sys/module/e1000/drivers/pci\:e1000/unbind
insmod hello_kernel.ko
cd /dev/
# mknod hellokernel c 241 1
# mknod no longer required. Build is done in-situ.
exit
