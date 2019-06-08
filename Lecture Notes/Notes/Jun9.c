ECE 373
06/03/19

//	Linux Build Infrastructure

/*

	Build symlink is addressed by the Makefile
	
	Do not re-invent the very, very, big wheel that is the kernel build.
	
*/

// Building a kernel

/*

	Open-source terminology:
	-	Upstream:
		>	"I'm using the code from upstream."
		>	Mainline
		>	Tip of Tree
		>	HEAD
		>	Latest commit to the tree
		>	The main development branch.
		
	git uses this terminology.
	
	There are many branches off the main Linux tree
	-	Maintained by Linus Torvald
	
	Distribution:
	-	Collection of the kernel and everything else
	-	Using the kernel by itself wouldn't get you very far.
	-	bash prompt is contained within the distro.
	-	C library is contained within the distro.
	-	Drivers to interface with kernel and hardware.
	-	userspace is created using these components.
	
*/

// Prepping the machine.

/*

	http://kernel.org and unpack the kernel code archive
	
	or
	
	use git,
	https://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/torvalds/linux
	
	or
	
	apt-get source linux-image-($uname -r)
	
	Read: https://wiki.ubuntu.com/Kernel/BuildYourOwnKernel
	
*/

//	How to configure a kernel

/*

	Always start with copy of the .config named as olddefconfig to remake the config file.
	
	Start with a .config that you know works.
	
	Tweak the config for your needs
	
	Interactive Terminal:	make config
	-	All questions are asked in sequence.
	-	If a mistake is made, you must exit "ctl+c" and start over.
	-	~13000 options.
	-	Takes a loong time.
	
	Curses-based:	make menuconfig
	-	This is the old terminal version of cursors in a terminal.
	-	used 90% of the time.
	
	GUI-based:	make gconfig
	
	or: Edit the .config file directly.
	
*/

//	make config

/*

	after installing build-essentials...
	after installing bison...
	
	running make config gives you options.
	
	Enter selects the default option for building modules.
	
	Symbol:
	-	Shows the module symbol and the current selection.
	
	Type:
	-	bool is either built into the kernel or not
	-	(tri-state) the third state is to build as a seperate module.
	
	Location:
	-	Where in the hierarchy it lives, such as "General setup"
	-	lists dependencies of the module.
	
	
	The dependencies of the module will prevent the build option from showing if not all are met.
	
*/

//	make menuconfig

/*

	Much better.
	
	The "/" button for dependencies.
	-	If searching for "MMU" all the symbols with instances of "MMU" will be listed.
	
	The list in this menu is built off of the architecture.

*/

// kconfig

/*

	Framework
	
	The system is hierarchical tree
	-	leaves are the bottom of the list.
	
	This is the infrastructure which enables/disables kernel features.
	
	Linux Kernel Source has in every directory:
	-	Kconfig file
	-	Make file 

	kconfig:
	-	Its own scripting language.
	-	Homework 7 HW7 HW 7
	
	init:
	-	Has a list of all the kernel configuration.
	-	Has menus of config options.
	
	init/makefile:
	-	shows the build order for that directory.
	
	obj-m, obj-y, obj-n:
	
	The build options for the object file which list the subdirectories which the object is dependent on other modules beneath it.
	
	Leaf directories which have the modules of that depenency, there will be no Kconfig file.
	
	
	
	
	
	