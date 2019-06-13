ECE 373
05/22/19

POST: Power On Self Test

HW Interrupts

-	Hardware signals Data Waiting-Might be case sensitive.

-	Interrupts cannot be scheduled.

-	Interrupts cannot be put to sleep.

	>	Cannot use printk()
	
	>	Use traceprintk

-	msleep usleep = you will hate life.

-	mutexes (blocking) 

-	kzalloc()

	>	Flags
	
		+	GFP_KERNEL	(Don't use this in interrupts)
		
		+	GFP_ATOMIC (use this one for interrupts)

-	Machine Check

	>	CPU ran into a nasty problem and aborted.

	>	MMI
	
	>	Non Massable Interrupt.
	
		+	Can't be suppressed.
		
		+	Corrupt data on the BUS
		
		+	Bad opcode
		
		+	Thermal event typically MMI
		
-	Nested Exceptions (Interrupts)

	>	On x86 an interrupt interuppting an interrupt will crash into the ground.
	
	>	Nested exceptions support required in silicon.
	
use: cat /proc/interrupts

-	Outputs the interrupt numbers.

-	Some are named.

-	Local timer interrupt runs on every CPU.

-	At the end of the software timer interrupt the jiffies are updated.

Basic Interrupt Flow

-	Must allocate interrupt and set up handler.

	>	Specific to what your driver needs to process.
	
	>	USB device would clean URBs. (USB Request Blocks-USB version of descriptors) Possible refill if needed.
	
	>	Network device will process received packets.
	
	>	Disk device will process data blocks.
	
-	Older interrupts were hardwired.

	>	Numbers were predetermined.

-	Tell the device what interrupt line/number to use.

-	Run.

-	Disable interrupt in device then OS when done.

	>	If not disabled first when triggered, the interrupt will interrupt the current interrupt and bad things will happen.

-	Interrupt numbers work differently with PCI.

Interrupt Types

-	Legacy

	>	Since obsoleted. Hard traces ugly.

	>	Hardware based, individual wires, limited availablitliy.
	
	>	Chainging of handlers on same interrupt 
	
		+	Coordination of handlers.
		
		+	Recall the limited availability.
		
	>	lspci
	
		+	Devices that support legacy interrupts use "pin A, B, C, etc".
		
		+	Devices will be handed an IRQ.
		
-	MSI

	>	PCI message signaled interrupt
	
	>	No more chaining
	
		+	Each device gets its own interrupt
		
	>	Each PCI device gets its own interrupt.
	
-	Networking Cards

	>
	
-	MSI-X

	>	Many Interrupts per PCI device.
	
	>	Queues are parallelized 
	
	>	Important for NVme and SSD drives.
	
		+	These have multiple queues by spec.
		
	>	One interrupt servicing multiple queues.
	
		+	Eats away at time slice
		
		+	Have to due further processing.
		
-	SW Interrupts

	>	Still an interrupt but a lower priority than a  hardware irq.
	
		+	Remember that interrupts shouldn't be interrupted by and interrupt.
	
	>	SW triggers
	
	>	Timers
	
	
Basic Wiring

-	Legacy 

	>	Request an IRQ using device info.

	>	err = request_irq(pdev->irq, irq_handler_name, 0, "Interrupt Name (shows up in proc/interrupts), data_to_pass_to_handler_func);
	
-// Use legacy for the assignment not MSI.

-	MSI

	>	Enable MSI for the device
	
	>	Request an IRQ using PCI device info
	
		+	pci_enable_msi(pdev);
		
		+	err = request_irq(pdev->irq, irq_handler_name, 0, irqname, data);
		
-	MSI-X

	>	MSI-X needs an array for many interrupt vectors.
	
	>	Prep an array of msix data structures
	
		+	entries = kcalloc(num_vectors, sizeof(struct msix_entry), GFP_KERNEL);
		
		+	The kernel requires physically continous entries for MSI-X. 
		
	>	Enable MSI-X for the device.
	
		+	get block of interrupt vectors.
		
		+	pci_enable_msix(pdev, entries, num_vectors)
		
	>	Request an IRQ for each msix entry
		
		+	for (i = 0; i < num_vectors; i++){
			
			err = request_irq(entries[i].vector,
			
			ece_irq_handler, 0, "ece_msix", i);
			
		}
		
//	See example: MSI-X @ 55:00 into video for may 22.

	>	Hard to run out of MSI-X interrupts.
	
Interrupt Handler

-	Legacy interrupts only.

	> Check ICR
	
		+	Interrupt Cause register.
		
		+	Pull data, mask and check if Legacy IRQ is source.
		
	>	Return IRQ_NONE if the interrupt is not the expected one.
	
	>	Return IRQ_HANDLED when ISR is complete and the interrupt was for the intended routine.
	
	>	Handler needs to be quick
	
		+	The longer the CPU is held down the more overhead.
		
	>	Hardware info is grabbed.
	
		+	States to hold or return to
		
	>	Don't Call code that might sleep!
	
		+	includes sleep(), malloc(), other I/O functions.
		
		+	kmalloc GFP_ATOMIC ok if used correctly.
		
		+	Locking mutexes no.
		
		+	Spin locks ok.
		
		+	Completions ok.
		
	>	Use Top/half Bottom/half concept.
	
		-	Wake up driver code with worker thread or waiting on a completion.
		
Typical Handler

-	Return type is irqretur_t

-	inputs are the interrupt number and cookie data.

-	Read the Interrupt Cause Register (ICR) "REG_IRQ_CAUSE);

-	Switch depending on if the IRQ was the cause.

	>	