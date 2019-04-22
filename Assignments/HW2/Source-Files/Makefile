
 
# @file Makefile
# @author Michael Escue
# @brief Makefile for HW2
# @version 0.1
# @date 2019-04-14
# @copyright Copyright (c) 2019
 
C = gcc

# From Lecture
KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

obj-m += hello_kernel.o

default:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

	
clean: 
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean 


