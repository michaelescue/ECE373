
 
# @file Makefile
# @author Michael Escue
# @brief Makefile for HW1
# @version 0.1
# @date 2019-04-14
# @copyright Copyright (c) 2019
 
C = gcc
HW1_OBJS = hw1.o
HELLO_SRC = hello.c
HW1_SRC = hw1.c
HW1_HDRS = hw1.h
HELLO_OBJS =  hello.o

# From Lecture
KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

obj-m += hello_kernel.o

default:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

	
clean: 
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean 


