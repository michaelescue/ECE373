#Makefile for HW3 Question 2c.
#Author: Michael Escue.
#Assignment: HW3.
#Due Date: 10/27/18 22:00.

C = gcc
HW3OBJS = main.o max.o 1dalloc.o
HW3HDRS = hw3. verbose.h
Q2.1OBJS = main2.o stack.o 
Q2.1HDRS = stack.h verbose.h
Q2.2OBJS = main3.o queue.o
Q2.2HDRS = queue.h verbose.h

#Question 1 make-code
all: hw3.1 hw3.2a hw3.2b

hw3.1: main.o 1dalloc.o max.o
	$(C) -o $@ $(HW3OBJS)

1dalloc.o: 1dalloc.c verbose.h
	$(C) -c 1dalloc.c
	
max.o: max.c verbose.h
	$(C) -c max.c
	
main.o: main.c hw3.h verbose.h
	$(C) -c main.c
	
#Question 2a make-code.
hw3.3a: main2.o stack.o
	$(C) -o $@ $(Q2.1OBJS)

main2.o: main2.c stack.h verbose.h
	$(C) -c main2.c

stack.o: stack.c stack.h verbose.h
	$(C) -c stack.c

#Question 2b make-code
hw3.3b: main3.o queue.o
	$(C) -o $@ $(Q2.2OBJS)

main3.o: main3.c queue.h verbose.h
	$(C) -c main3.c

queue.o: queue.c queue.h verbose.h
	$(C) -c queue.c
	
clean: 
	rm $(HW3OBJS)
	rm $(Q2.1OBJS)
	rm $(Q2.2OBJS)

