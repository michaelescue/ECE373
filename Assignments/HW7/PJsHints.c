/** HW6

So a few of you have been hitting this.  It took me a bit to figure out what is missing from some of your code, and it's very subtle.

In probe and remove, there are two functions that some of you don't have.  Before you start mapping anything, in probe() you need to do:

*/

pci_enable_device_mem(pdev); 

// OR

pci_enable_device(pdev);

// and one of the last things in remove() is:

pci_disable_device(pdev);

/*
Here's references...

https://elixir.bootlin.com/linux/latest/source/drivers/net/ethernet/intel/e1000e/netdev.c#L7064
https://elixir.bootlin.com/linux/latest/source/drivers/net/ethernet/intel/e1000e/netdev.c#L7450

Hope this helps folks...

-PJ

 */

/** HW7
Hi folks,

Thanks to Amanda (you can all thank her tomorrow), she sent some steps she needed to use to bail herself out of some issues when building a new kernel for HW7, and running into a panic.  This is her email verbatim (shared with her permission):

I had to use this link to get back into the kernel where I was building my stuff in the first place: https://www.pcsuggest.com/grub-rescue-linux/  
which can be done by, when you are greeted by that menu that's like Ubuntu / memory check /.....
you type 'e' with the cursor highlighting Ubuntu to get into the grub menu
navigate to the bottom where it shows the kernels it is intending to build
and change them back to the version that works
and it boots when I press F10 to tell it to boot.  

Compile the kernel, run make -j4
Build the kernel modules, make -j4 modules
Install kernel modules, sudo make modules_install
Install firmware files, sudo make firmware
Finish the installation, sudo make install
then run sudo update-initramfs -c -k 4.19.49voegtlin
THEN run sudo update-grub
then sudo reboot

 */