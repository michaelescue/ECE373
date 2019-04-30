
 
# @file Makefile
# @author Michael Escue
# @brief Makefile for HW2
# @version 0.1
# @date 2019-04-14
# @copyright Copyright (c) 2019
 
C = gcc

# From Lecture
KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

obj-m += hello_kernel.o

default: ledmon.o test.o
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules
	gcc -s test.o
	gcc -s -o ledmon.o ledmon.out


test.o:
	gcc -c test.c 

ledmon.o: 
	gcc -c ledmon.c

clean: 
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean 
	rm a.out
	rm ledmon.o ledmon.out

