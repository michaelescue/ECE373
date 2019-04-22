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

#define BUF_SIZE 256

int main(void){
    errno = 0;
    char *buf[BUF_SIZE] ={NULL};

    int fd = 0;
    if((fd = open("/proc/241", O_RDONLY)) == -1){
        perror("Error on open.");
        return -1;
    }

    read(fd, buf, sizeof(int));

 if(close(fd) == -1){
        perror("Error on close.");
        return -1;
    }

return 0;
}