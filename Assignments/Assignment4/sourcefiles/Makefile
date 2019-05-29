
 
# @file Makefile
# @author Michael Escue
# @brief Makefile for HW4
# @version 0.1
# @date 2019-04-14
# @copyright Copyright (c) 2019
 
C = gcc

# From Lecture
KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default: ledmon.o usdrv.o
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules
	gcc -s -g usdrv.o -o usdrv.out
	gcc -s ledmon.o -o ledmon.out

test: usdrv.c usdrv.o
	gcc -g usdrv.c -usdrv.out

usdrv.o:
	gcc -c -g usdrv.c 

ledmon.o: 
	gcc -c ledmon.c

clean: 
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean 
	rm usdrv.out
	rm ledmon.out