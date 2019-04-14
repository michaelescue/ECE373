
 
# @file hw1.c
# @author Michael Escue
# @brief Makefile for HW1
# @version 0.1
# @date 2019-04-14
# @copyright Copyright (c) 2019
 
C = gcc
HW1_OBJS = hw1.o
HW1_HDRS = hw1.h
HELLO_OBJS =  hello.o

# Make file code:
all: hw1 hello

hw1: hw1.o
	$(C) -o $@ $(HW1OBJS)

hello: hello.o
	$(C) -o $@ $(HELLO_OBJS)

hello.o: hello.c $(HW1_HDRS)
	$(C) -c 1dalloc.c
	
clean: 
	rm $(HW1OBJS)


