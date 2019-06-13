ECE 373
05/13/19

Port mapped I/O in Linux

-	The main difference between port and memory mapped I/O:

	>	Port mapped I/O is not using memory locations.
	
	>	Global to a system.
	
	>	Numbered.
	
	>	Architecture specific.
	
	>	Special CPU operations to enable I/O requests.
	
		+	inb <reg>
		
		+	outb <val> <reg>
		
	>	Port mapped I/O are registers.
	
	//	Know the difference between port mappe dand memory mapped I/O
		
	+	I/O Ports allow pre (Hard Disk) boot to Operating system.
	
		+	Older 
		
	>	PXE running on the chip attempts network boot
	
		+	No memory is available, so port mapped I/O is ideal (cannot memory map yet, no OS).
		
	>	PXE: Pre-Boot Execution Environment

	
	use: ioresource io
	
	use: lspci -s 00:03.0 -VVV
	
		>	Can find the capabailites of each Region by mapped BAR address. 
		
		
	use: ps -ef
	
		>	Shows processes and ids
		
		>	PPID
		
			+	Parent Process I D
			
		>	PID 0 is the kernel.
		
Network Manager:

	>	THe thing configuring Wi-Fi on the laptop.
	
	use: ps -eLf
	
		>	LWP
		
			+	Light Weight Process.
			
			+	A Thread.
			
IPC: Inter Process Communication.
	
	>	Shared memory between threads.
	
	>	Each process gets a new block of memory every time it is spawned.
	
SELinux-NSA-Rip-out-on-new-machines-crap.

More on PIDs:

-	Kernel threads have cpu numbers denoted by "/1, 2, 3, of 4" on a quad CPU system.

SystemD:

-	Leonard Pottering (Giant Asshole)

	>	Works for RedHat linux.
	
	>	Wrote Pulse Audio.
	
	>	Wrote SystemD.
	
	>	Banned from Linux Gatherings where Linus is. (From argument)
	
-	Binary application

-	Tried to take over everything.

-	Went for a monolithic non modularlize
	
init:

-	Init is the root of the tree.

-	Kernel Processes run from it.

	>	[kthreadd]
	
	>	[ksoftirqd]
	
	>	[watchdog]
	
	>	Kernel processes are bracketed.
	
-	User threads run from it.
	
	>	getty
	
	>	bash

		+	ps -ef
		
OS Scheduler:

-	Chooses which to process/thread to run next on which CPU.

-	Interrupts mess with scheduler plans.

-	Weighted Tree Structure

	>	Ready queue
	
	>	Wait queue
	
	>	Thread priority
	
		+	remember to use: nice
		
	>	Time slice
	
		+ sleeping the process is required at the end of loops in the kernel processes/threads.
		
		+ Also known as blocking.
		
	use: sleep();

	>	Preemption
	
	>	CPU core affinity
	
	>	Etc

Interrupted Thread:

-	Files will not be in memory.

	>	More likely in the drive.
	
	>	Page faults occur when .
	
		+	Generates an exception (interrupt).
		
		+	Blocks the process.
		
		+	Page faults in DMA are fatal, but page faults otherwise serve a purpose in most threads.
	
	>	The page fault signals:
	
		+	I/O request issued.
		
		+	Retrieve the file using CPU
		
		+	Signal when file in memory.
		
		+	Has the OS wake up a process blocking waiting on data to become available.
		
Concurrency:

-	Bad things can happen when multiple threads attempt to run/read data at the same time as another thread.

-	Race condition can corrput data when.

-	Coordination needed.
	
Completions:

-	A shared flag on which one trhead waits on another.

-	Particularly suited to waiting for an unknown amount of time.

-	Wont use these.

Atomic action:

-	Large hammers.

-	Good for maintaining consistency for data.

-	Awful for performance.

-	Some functions:

	>	atomic_inc(x)
	
	>	atomic_inc_and_test(x)
	
	>	set_bin(n, *s)
	
	>	clear_bit(n, *s)
	
	>	test_bit(n, *s)
	
	>	static inline void atomic_inc(atomic_t *v){
			
			asm volatile(LOCK_PREFIX "incl %0"
					:"+m"(v->counter);
		}
		
-	All cores must coordinate CPU cache.

-	Any atomic actions are extremely expensive time-wise.
	
-	These instructions map directly to assembly language on the architecure being supported.

-	Bit fields are used to manage features.

	>	Bits are set to indicate the feature is supported.
	
Semaphores:

-	A thread incrementable and decrementable counter.

-	Once zero, next thred to decrement to negative blocks.

-	Also uses atomic actions

-	Also very expensive.

Spinlock:

-	While lock is not available, try to take the lock.

-	These will be used.

-	Thread running spin lock

	>	Doesn't allow for any power savings at all until it gets the lock and consumes all CPU time.
	
-	Atomic version of spinlock:

	>	while (test_and_set(3, &bit_string))
		
		+	a "tight loop"
		
-	Alternative is to sleep 
	
	>	while (test_and_set(3, &bit_string))
	
- DO NOT SLEEP INSIDE OF INTERRUPTS

	>	SLEEPING IS TO BLOCKUSE
	
	>	USE SPINLOCKs
	
Mutexs:

-	Threads which lock.

	>	Must be released by the same thread.
	
-	Other threads seleep while waitingin for lock.

-	Good for blocking access to data, other resources

-	Like spinlock, but more restrictive

-	Linux commands:

	>	struct mutuex mlock;
	
	>	mutex_init(%mlock);
	
	>	mutex_lock(&mlock);
	
	>	mutex_ulock(&mlock);
	
Deadlock:

-	When two processes request each others lock and is waiting on the other to release the lock.

Livelock:

-	Similar to Deadlock. 

-	Something in the system is trying to get out deadlock,
but never results in anything.

Hiesenburg bug:

-	A timing related bug.  