/*

Downloading and bulding the linux kernel.

source code obtained.

checkout the latest branch.

run the patch shell if any.

*/

/** Preparations prior to kernel build:	**/ // bash commands.

// We wish to build beaglebone series kernels 
cp configs/beaglebone kernel/arch/arm/configs/beaglebone_defconfig 

// Pre-compiled power management firmware 
wget http://arago-project.org/git/projects/?p=am33x-cm3.git\;a=blob_plain\;f=bin/am335x-pm-firmware.bin\;hb=HEAD -O kernel/firmware/am335x-pm-firmware.bin 

cd kernel

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- beaglebone_defconfig 

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- uImage dtbs 

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- uImage-dtb.am335x-boneblack 

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- modules 

# Follow the series of commands 