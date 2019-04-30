The BAR

	- Base address register.

	- "# lspci -s <bus:slot:fn> -vv" command 
	
	- Lists pci devices and details for the base address registers
	
Accessing PCI Regions

	-	"pci_request_selected_regions()" maps I/O BAR into pci_device.
	
	-	"ioremap()" Returns the physical address of the requested BAR
	
		>	At this point PCI reads and writes can be issued to the devices
		
			+	"writel()" and "read()"
			
		