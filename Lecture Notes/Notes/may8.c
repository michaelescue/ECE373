ECE 373 Lecture Notes
April 29th 

Userspace driver

-	A way to drive hardware from outside the kernel.

-	A userspace program.

	>	Higher level of control.
	
-	Access to various resources.

	>	I/O ports
	
	>	Memory regions
	
		+	Includes BAR Access and related regions. 
	
	>	Control interfaces
	
-	Resources presented by kernel scanning hardware in standardized ways.

	>	Libraries are available to use for retrieving specific information from the kernel.
	
		+	Fills out declared data strctures with data requested. 

	>	PCI bus scan.
	
-	Not a kernel object file, just a regular object file.


What isn't a userspace driver?

-	What doesn't qualify as a "Userspace Driver":

	>	Scripts/programs using:
	
		+	/sysfs
		
		+	/proc
		
		+	/devfs
		
-	Exceptional Cases:

	>	Graphics drivers can be combination of user and kernel mode.
	
	>	Nvidia kmod-nvidia plus Xorg userpsace driver.
	
		+	Serach further lecture notes for information.
		

Userspace Drivers in Embedded Systems

-	Popular for fully-encapsulated devices.

	>	Touchscreen.
	
	>	Battery driver maybe.
	
-	Popular for simple devices.

	>	LEDs, GPIOs, etc.
	
	>	Arduino, BeagleBone, etc.
	
-	Not popular when interfacing with subsystems.

	>	Networking.
	
	>	Audio.
	
-	(DPDK) Data Plane Development Kit

	>	Intel SDK to enable switching infrastructure.
	
	>	"Kernel bypass".
	
	
Why use a userspace driver?

-	Quick prototyping.

-	Free from kernel "ABI" changes.

	>	"ABI" is "Application Binary Interface".

-	Typically doesn't blow up te machine.

	>	Constrained to mapped, user, space.
	
-	Ease of use.

	>	Can be written in most compiled and scripted languages.
	
-	May not have ability to change the kernel (protection).


Why not use a userspace driver?

-	Performance and latency on wake-ups.

-	Power efficiency.

-	No interrupts.

-	No access to kernel infrastructure.

	>	Kernel times.
	
	>	Jiffies.
	
	>	Physical Memory.
	
	>	Traditional DMA.
	
	
Drivers of the rings

-	These are the rings of programs around the kernel, where ring 0 is the kernel.

-	Rings refer to privlege levels.

	>	Analagous to User, IRQ, supervisor, etc.

-	Kernel runs in ring 0 on CPU.

-	Hardware is protected by ring 0 access.

-	Userspace (Applications) runs in ring 3 on CPU.

-	Userspace drivers run in userspace.


Unavailable Resources

-	Direct access to all kernel memory.
	
	>	Not always a disadvantage.
	
	>	Requires more "maps" if you need access.
	
-	Interrupts

	>	Only fire in kernel space.
	
	>	Priority is lost in userspace.
	
-	Schedule priority can be a problem.

	>	Another userspace process.
	
	
Performance Considerations

-	Pure userspace drivers can be quick.

-	Polling can have negative side effects.

-	Polling can have advantages for letency-sensitive operations.

	>	Stock trading.
	
	>	Stop-lights.
	
	>	Car computers.	
	
	
Kernel Access from Userspace drivers

-	Pure userspace approach must break into the kenel somehow.

-	Kernel provides mechanisms to get at memory.

-	Use a hybrid approach
	
	>	Small shim driver in kernel space.
	
	>	Exports driver interface file /dev for userspace to drive.
	

Mapping memory

-	mmap, munmap - map or unmap files or devices into memory

-	Access with array/pointer operations.

-	Page is cached once, rewritten on updates, everyone sees update.

-	Example: 

	>	Web server using memory mapped files for multiple threads on multiple files.

-	Advantages:

	>	Access large files, reading quickly from file in memory.
	
	>	Kernel can manage page resources better. mmap()'d pages backed by page cache.
	
	>	Memory swaps are quick as opposed to file page cache writing back before swapping.
	
	>	Share file data between processes.

-	Disadvantages:

	>	Limited space in 32-bit addressing.

-	Attributes:

	>	MAP_SHARED
	
	>	MAP_ANONYMOUS
	
-	Procedure of Mapping Memory:

	>	open(pathname, flags);	// Ironically opening a file in /dev, where the previous definition of a non-userspace driver is anything that accesses /dev.

	>	// mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

	>	Inspect the region of memory regutrned: on error, MAP_FAILED  (that  is, (void *) -1) 

		if( (mmap(addr, length, prot, flags, fd, offset)) == MAP_FAILED ){
			perror("Memory Mapping (mmap()) failed.\n");
		}
		
		+	Use "lspci" to find the values needed to utilize the mmap() function.

	>	munmap(addr, length);	// Release mapped memory.

	>	close(fd);
	
	
Mapping into the Kernel

-	May require relaxing constraints on io memory:

	>	Linux boot parameter: iomem = relaxed.
	
-	When mapping sensitive areas:

	>	strace
	
	>	dmidecode
	
	>	SMBIOS	(research online).
	
	>	Follow dmidecode

-	/dev/memory
	
	>	 /dev/mem is a character device file that is an image of the main memory of the computer.  It may be used, for example,  to  examine  (and  even patch) the system.
	
-	open(pathname, flags);

-	if( (mmap(addr, length, prot, flags, fd, offset)) == MAP_FAILED ){ 
		perror("Memory Mapping (mmap()) failed.\n");
	}
	
	>	To mmap() successfully on /dev/mem, need a place to map.
	
	>	What are we trying to map on our PCI device to control it?
	
		+ What do we map in the kernel?
		
	>	Where do we find the BAR address?
	
		+	lspci
		
		+	Can look in /sysfs
		
		
Interrupts

-	Poll.

	>	Assigning a single core to perform this action on a multi-core machine is a good idea.
	
-	Using hybrid approach:

	>	Interrupt routine could consist of waking userspace thread.
	
-	Can generate interrupts if underlying HW supports it.

	>	Writing register to fire SW-originated interrupt.
	

SecureBoot

-	Attempt at securing EFI to bootloader security

-	Trying to prevent rootkit access to the bootloader and OS.

-	"Signed" modules used, signed by a CA (Microsoft).

-	SecureBoot is required for Win8	certification on ARM only.

-	Red Hat, SuSE, others still moving forward with SecureBoot compliance on x86.

-	Locks access to the kernel space.

	>	/dev/mem access prohibited because of this.
	
-	Kernel modules (drivers) must be signed.


Reading

-	LDD3 pages 37-39

-	Essentials pages 558-564

-	Man pages on mmap();

-	Read e1000regs (akaethregs) on 31000.sourceforge.net
