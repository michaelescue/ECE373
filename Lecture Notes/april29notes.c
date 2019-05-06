ECE 373 Lecture Notes
April 29th 

/*	Time	*/

jiffies:	Global kernel time tick

	-	The smallest interval of time that the kernel is concerned about.
	
HZ:	The number of jiffies per second.

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
	
		