cd /home/michael/Documents/ECE373/Assignments/HW3/sourcefiles
make clean
make
insmod hello_kernel.ko
cd /dev/
mknod hellokernel c 241 1
exit