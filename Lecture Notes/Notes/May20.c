ECE 373
05/20/19

//05.15.19
/*

k*alloc and friends

-	There are several ways to allocate memory:

	>	kmalloc()
	
	>	kmalloc_array(),
	
	>	kmalloc_node()
	
	>	kzalloc()
	
	>	kzalloc_node()
	
	>	more...
	
-	void *kmalloc(size_t size, gfp_t flags)

	>	Flags: (GFP = Get Free Pages)
	
		+	GFP_USER
		
		+	GFP_KERNEL	(kmalloc will be allowed to sleep)
		
		+	GFP_ATOMIC	(kmalloc is not allowed to sleep, useful for interrupts)
		
		+	GFP_NOWAIT
		
		+	GFP_DMA
		
-	void kfree(void *)

-	Always check to ensure a NULL is not returned.

Direct Memory Access

-	Allows direct access to memory without involving the CPU.

	>	MMIO involves the CPU
	
	>	Important for performance.
	
-	Incorporated in many devices.

Why is DMA important

-	Ease the load on the CPU.

Back in the day

-	Device RAM was mapped into system memory (MMIO).

	>	Command buffers and registers addressable in memory.
	
Evolution of DMA

-	ISA bus is the predecessor to PCI.

	>	Contained a DMA controller
	
-	Floppy disks and old parallel ports still use ISA DMA.

Controller Driven DMA

-	MAC addresses are the unique hardware address of a network adapter.

-	OSI model will describe the network stack and operation of network protocol of interest.

1.	Data received from network

2.	Device sends IRQ

3.	IRQ handler starts DMA

4.	Device requests DMA access

5.	DMA controller requests a bus hold.

6.	CPU ack's the hold

7.	Bus controller ack's the DMA

8.	Device copies data to RAM

-	This model worked for a while but needed to be improved.

-	DMA was redesigned.

Further Evolution of DMA

-	No centralized DMA controller

-	DMA is performed by peripheral device.

-	Not all PCI devices allowed to talk at once.

BUS Mastering

-	PCI devices utilize protocol called bus mastering.

-	Each device requests ownership of PCI

-	PCI controller arbirates over all bus masters

-	Each bus master issues commands when it owns the bus

	>	readl commands
	
	>	writel commands
	
Device Driven DMA

1.	Data received from network

2.	Bus Master negotiates for bus access

3.	Device copies data to RAM

4.	Device send IRQ

5.	IRQ handler processes data

How DMA works

-	DMA enabled device told which direction to DMA 

	>	To or from device, or bidirectional
	
-	Physical memory is mapped for DMA

	>	Memory is pinned. 

	>	Kernel logical memory (1:1 mapping) is what is allocated.
	
		+	Kernel logical memory is still offest because of kernel reserved memory.
		
	>	Devices need physical memory address because there is no translation by DMA devices.
	
	>	ALways unmap the memory for DMA.
	
	>	Usually userspace drivers can't map for DMA.

-	Device initiates the DMA (either to ror fom device)

-	Memory unampped for DMA after operation completes.

*/

Descriptors:

-	Each descriptor points to a buffer.

-	There are multiple buffers for each discriptor.

-	Finds descripter.

-	Finds buffer.

-	Puts data into buffer.

-	Buffer holds data.

-	Changes descriptors to let the CPU know it had done this.

Logic View of Ring Descriptors:

-	Descriptor Data location.

-	Descriptor ring.

-	Descriptor Done 0

	>	Means descriptor is ready to receive new data from the device.
	
-	One entire descriptor takes the size of a packet.

-	Each ring can contain any number of descriptors.

HW5:

-	Difference is timer

	>	to blink the LEDs at a defined rate.
	
	>	automatically do the makenod for us.
	
	
-	Communication up to userspace should include code in the init function.

-	put the codein the prod function for pci

Automatically creating the dev node.

-	if((myDev.my_class = class_create(THIS_MODULE, "led_dev")) == NULL)
	{
		printk(KENR_ERR "Class_create failed!\n");
		goto destroy_class;
	}

-	//Need to find dual to destroy.

