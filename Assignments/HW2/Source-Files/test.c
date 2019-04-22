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

int test(void){
    errno = 0;
    char *buf[BUF_SIZE] ={NULL};

    FILE * fd = NULL;
    if((fd = open("/proc/241", O_RDONLY)) == -1){
        perror(errno);
        return -1;
    }

    read(fd, buf, sizeof(int));

 if(close(fd) == -1){
        perror(errno);
        return -1;
    }

return 0;
}