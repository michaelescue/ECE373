/**
 * @file april 22 notes.c
 * @author Michael
 * @brief  Notes for ECE373
 * @version 0.1
 * @date 2019-04-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

 bash commands:
    int umask;
/**
 * prints to terminal, will print with format specifier.
 * inverts the bits.(?)
 * "cancels" out 777 for all permission bits set. 
 */


    ls -l /dev/"device"

    $ strace
/**
 * strace prints out all the system calls used during a program execution.
 * Likely have to build the program with debugging symbols.
 */

    $ sudo bash   
/**
 * sudo puts the bash shell into a different environment.  
 * sudo is to change user, but defaults to root.
 * this environment gives you a bunch of meaningfull macro(?) or
 * defines that contain paths for lookups.
 * 
 */

    # su
/**   
 * su sets user to root (default).
 * Creates a shell within a shell that is root #
 *        
*/

chmod

/**
 * changes permissions.
 * accepts octal input for setting permission flags.
 * the man page 
 * 
 *      chmod 777
 *            bit positions
 *            111_111_111
 *            7:    Read/Write/Execute
 *            4:    Read
 *            6:    Read/Write
 *            1:    Execute
 * 
 *      "-rwx--x--x 1   user    0   date    time"
 *      "-" A dash.
 *        read bit      |
 *         write bit    |   Octal 1         [File]
 *          execute bit |
 *           read bit      |
 *            write bit    |   Octal 2      [Group]
 *             execute bit |
 *              read bit      |
 *               write bit    |   Octal 3   [World]
 *                execute bit |
 */
<<<<<<< HEAD

ICH  : Integrated Controller Hub.

	-	i7 and i9 PCI connectivity is mostly in the CPU instead of in the ICH (w/ ICH can cause performance issues.
	
PCI Bus (pre 'Express') 

	- 	Historically the Bus had to talk to the "Bus Bridge" which woud then forward communications to the "Frontside"
		System BUs to communicate with the CPU.
		
	-	PCI is parallel protocol.
	
	-	PCI Express is serial (uses "latents").
	
	-	Supplies only 45W of power (v4.0) 
	
	-	When hardware interfaces with the PCI "Link Training Occurs" with the config space of the PCI device.
	
		>	Data block begins with vendor & device ID.
		
		>	Lists capabilities (IRQs, Suspend capabilities, Device speeds, Memory mapped).
		
		> 	Register sets get mapped into the memory mapped I/O.
		
PCI Lifecycle

	- 	OS operations

		> 	Scans PCI bus for devices.
	
		>	Queries found device for config block.
	
		>	Finds deviceID in PCI driver table.
	
		>	Loads driver and calls "probe()".
	
		>	When removing the driver: calls "remove()" to unload device & driver.
	
			+ PCI device is waiting (if not uplugged) waiting for another device to load and use it.
		
	-	The driver
	
		>	Initis device and maps it into memory.
		
		>	Register interrupt handlers.
		
		>	Waits to service interrupts and OS requests.
	
		>	Stops device, erleases memory.
		
	-	PCI access in Linux
	
		>	"init_modue()" and "exit_module()" are still used
		
		> 	"probe()" /* is required */ for PCI initialization.
		
			+	The callback on this function is a struct with the name, id_table, probe, remove, suspend, resume, etc.
			
			+ 	Example: If a system tries to suspend, but doesnt, its probably because the driver hasnt provied the
				detail on suspend capability, or doesnt support it.
				
		> 	When the PCI driver is registered with the kernel:
			
			-	The bus driver is what you are talking to with your driver.
			
			-	The bus driver owns the "idtable"
			
			-	See http://lxr.free-electronscom/source/drivers/net/ethernet/intel/e1000e/netdev.c
			
				> Full network driver, not everything in this doc is needed.
				
e1000e/netdev

	-	Ftrace bug
	
		>	Function tracer inside the kernel
		
		>	2.6.27 kernel included a glitch from redHat which caused all the eeprom drivers to be nuked!
		
			+ PJ had to help fix the error which essentially erased the drivers (no write lock!)
			
		

PCI EXPRESS Bus

	-	Root Complex (Top level interface)
		
		> Communicates to CPU.
	
	-	End point (Cards, Graphics)
	
	-	Switch is a hierachical sub Root Complex top level for sub end points.
	

The BAR

	- Base address register.

	- "# lspci -s <bus:slot:fn> -vv" command 
	
	- Lists pci devices and details for the base address registers
	




 
=======
<<<<<<< HEAD

tail -f

/**
 * Uses tail command to show real time writes appended to target file.
 * tail -f /var/log/messages
 *      Shows dmesg.
 * 
 */
=======
 
int ISA EISA
 
>>>>>>> 2c1b7395d4171ae7d7089d7ff55c84594c5a4f94
>>>>>>> 3de67ccabbf646636bbd9eba1955c9b3e7d20492
