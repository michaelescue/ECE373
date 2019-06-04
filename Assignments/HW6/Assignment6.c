/*
Interrupts
Descriptors
Hello to the world

Processing data; input, output, both.

Configuring a device

Allocating resources for the device

Processing data via DMA, Interrupts, and using descriptors.

*/

/* Driver-side

Re-use assignment #5 code base.

Requires:

	Chardev
	PCI access
	
**Add the following to the driver**

- A small set of legacy descriptors for the RECEIVE QUEUE
	> 16 descriptors
	> 2048 byte buffers
	
- A control to track HEAD and TAIL of the RECEIVE QUEUE

- An Interrupt handler.
	> Tied to the legacy interrupt source
	
- A workqueue THREAD to handle deferred processing from the interrupt.

- Config code to put the chip into promiscuous mode.
	> force the link up at 1 Gigabit
	
- Update the read() system call function
	> return a 16-bit unsigned integer.
	> lower 8 bits will be the value of the receive queue TAIL
	> upper 8 bits will be the value of the receive queue HEAD
	
***Reference the e1000e driver for chip initialization

*****************************************************************************
**Steps to success**********************************************************

Step 1: Create a function that;
	Adds and allocates the descriptors
	Adds and allocates the buffers
	
	- This function to be called from probe after regions are mapped.
	
Step 2:
	Add the interrupt hadler.
	Hook the interrupt with request_irq().
	
	-  Check /proc/interrupts
	
		> The interrupt will be listed if it was successfully hooked.
		
Step 3: 
	Add the workqueue thread.
	Invoke from the interrupt handler.
	
Step 4:
	Add the descriptor ring control.
	
		- Should be added into interrupt handler to maintain HEAD and TAIL positions.
		
	Change read() system call as described above.
	
Step 5:
	Add a mechanism for re-arming the interrupt before exiting the handler.
	
*/


/* Link side

	
