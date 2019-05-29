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

#define LED0_ON 0xe
#define LED0_OFF 0x4e
#define LED1_ON 0xe00
#define LED1_OFF 0x4e00
#define LED2_ON 0xe0000
#define LED2_OFF 0x4e0000
#define LED3_ON 0xe000000
#define LED3_OFF 0x4e000000
#define LEDS_OFF (LED0_OFF | LED1_OFF | LED2_OFF | LED3_OFF)
#define BUF_SIZE 256

int main(void) {
    errno = 0;
    int buf[BUF_SIZE] ={0};

    int fd = 0;

/* open file    */
    if ((fd = open("/dev/hellokernel", O_RDWR)) == -1) {
        perror("Error on open.");
        return -1;
    }

    //printf("POST SYSCALL OPEN\n");

/* Read file    */
    printf("Ready to read. Press enter.\n");
    getchar();
    if ((read(fd, buf, sizeof(int))) == -1) {
        perror("Error on read.");
        return -1;
    }

    //printf("POST SYSCALL READ\n");

    int sys_call_val = 0;
    sys_call_val = buf[0];

    printf("blink_rate = %d per second.\n", sys_call_val);

   // printf("sys_call_val write val= %x, size of = %ld\n", sys_call_val, sizeof(sys_call_val));

/* Write to file    */
    printf("enter integer value:");
    scanf("%d", &sys_call_val);
    getchar();

     if ((write(fd, &sys_call_val, sizeof(sys_call_val))) == -1) {
        perror("Error on write.");
        return -1;
    }

    sleep(2);

/* Close file   */
    if (close(fd) == -1) {
            perror("Error on close.");
            return -1;
        }

    return 0;
}
