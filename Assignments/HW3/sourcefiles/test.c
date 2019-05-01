/**
 * @file test.c
 *
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-04-22
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUF_SIZE 256

int main(void) {
    errno = 0;
    char buf[BUF_SIZE] ={0};

    int fd = 0;

/* open file    */
    if ((fd = open("/dev/hellokernel", O_RDWR)) == -1) {
        perror("Error on open.");
        return -1;
    }

    printf("POST SYSCALL OPEN\n");

/* Read file    */
    if ((read(fd, buf, sizeof(int))) == -1) {
        perror("Error on read.");
        return -1;
    }

    printf("POST SYSCALL READ\n");

    int sys_call_val = 0;
    sys_call_val = buf[0];

    printf("sys_call_val = %d\n", sys_call_val);

    sys_call_val++;

/* Write to file    */
     if ((write(fd, &sys_call_val, BUF_SIZE)) == -1) {
        perror("Error on write.");
        return -1;
    }

/* 2nd readback after write */
    if ((read(fd, buf, sizeof(int))) == -1) {
            perror("Error on read.");
            return -1;
        }

        sys_call_val = buf[0];

        printf("sys_call_val = %d\n", sys_call_val);

    if (close(fd) == -1) {
            perror("Error on close.");
            return -1;
        }

    return 0;
}
