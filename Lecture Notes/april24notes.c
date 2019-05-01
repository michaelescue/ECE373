The BAR

	- Base address register.

	- "# lspci -s <bus:slot:fn> -vv" command 
	
	- Lists pci devices and details for the base address registers
	
Accessing PCI Regions

	-	"pci_request_selected_regions()" maps I/O BAR into pci_device.
	
	-	"ioremap()" Returns the physical address of the requested BAR
	
		>	At this point PCI reads and writes can be issued to the devices
		
			+	"writel()" and "read()"
			
Removing the PCI devices
	
	-	"iounmap()" and "pci_release_selected_regions()"
		
		>	Must be called from the remove function, not the "exit_module"!
		
	- "exit_moduel()" must unregister the pci_device struct from the driver subsystem.
	
Source file initiation order:

	1.	alloc_chrdev_region()
	2.	cdev_init()
	3.	cdev_add()
	4.	pci_register_driver()
	
		-	providing function pointers, what types of devices we can drive, 
	
	5.	pci_unregister_driver()	// Use goto from failure to register to this call.
	6	unregister_chrdev_region()
	
Source file structs:

	1.	static struct file_operations myDev_fops = {
			.owner = THIS_MODULE,
			.open  = blinkDriver_open,
			.read = blinkDriver_read,
			.write = blinkDriver_write,
		};
	
	2.	static const struct pci_device_id pci_blinkDriverTable[] = {
		{ PCI_DEVICE(0x8086, 0x100e)},
			{},
		};
		
	3.	static struct pci_driver pci_blinkDriver = {	// Similar to file_operations struct
			.name = "Blink Driver"
			.id_table = pci_blinkDriverTable,
			.probe = pci_blinkDriver_probe,		// When the PCI subsystem gets a device that you are capable of driving.
			.remove = pci_blinkDriver_remove,	
		};
		
Source file driver operations:

	1.	static int blinkDriver_open()
	2.	static ssize_t blinkDriver_read()
	3.	static ssize_t blinkDriver_write()
	4.	static ssize_t pci_blinkDriver_probe()
	5.	static void pci_blinkDriver_remove()
	
Shell script sequence:

	1.	Unbind the PCI	//Stop the e1000 , not necessary for the homework.
	2.	Install module
	
If strange errors start to occur:

	-	Use the clean script.
	
Take over a claimed device:

	-	
	

	
	