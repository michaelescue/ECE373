ECE 373 Lecture Notes
April 29th 

/*	Time	*/

jiffies:	Global kernel time tick (some OS have tickless operation).

	-	The smallest interval of time that the kernel is concerned about.
	
HZ:	The number of jiffies per second.

	-	changes depending on the system.

Operations for conversion:

	-	msecs_to_jiffies(m)
	-	jiffies_to_msecs(j)
	-	nsecs_to_jiffies(n)
	-	jiffies_to_nsecs(j)
	-	time_after(a,b)
	-	time_before(a,b)
	
Low-level time:

	-	get_cycles()
	
		>	Architecture dependent CPU cycle counter
		>	#defined'd to 0 if not supported.
	
	-	rdtsc:	Time Stamp Counter Register
	
		>	A register with 64 bit counter of clock cycles. 
	
Time of Day:

	-	current_kernel_time()
	
		>	Updated by tick, running time-of-date
		>	Initiated from the RTC.
		>	Not updated every ns, but every few hundered.
		>	Not recommended for performance testing.
		
	-	do_gettimeofay()
	
		>	Read from HW, adjusted with nanosecs & arch specific tweaks.
		
	-	mktime()
	
		>	Takes min/sec/etc/ to make seconds since "epoch" on Jan 1st, 1970.

	-	RTC
	
		> 	i2c devices keep Time of Day info.
		> 	Standard i2c device interface.
		>	Standard RTC interface.
		
Delayers:
  
	-	mdelay(),	udelay(), 	ndelay()
	
	-	The OS may only allow for a smallest time unit, such as ms, even wth smalled delay requests.
	
	-	While loop spin on a counter, no scheduler action.
	
	-	Only way to get short period delays
	
	-	Not very friendly for long periods.
		
	-	Could block jiffies update if interrupts disabled.
	
	-	Are useful for locking, interrupting, etc.
	
CPU friendly Delayers:

	-	cpu_relax()

		>	architecture dependent, may not do anything.

	-	schedule()
	
		>	give up timeslice.

	-	Also:

			while (!is_device_finished()){
				schedule();
			}

Sleepers:

	-	msleep()
	
		>	Give up timeslices for specific number of millisecs

	-	msleep_interruptible()
	
		>	Same, but stop if a signal is pending.
		
Timers:

	-	setup_timer(t_var, t_callback, t_data)
	
	-	mod_timer(t_var, interval)
	
	-	del_timer_syc(t_var)
	
	-	Callback function
	
		>	is called when timer expires.
		>	Given t_data as an argument.
		>	timer_cb(unsigned int data).
		
	-