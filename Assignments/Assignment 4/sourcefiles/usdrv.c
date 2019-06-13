/**
 * @file userspacedriver.c
 * @author Michael Escue
 * @brief Userspace driver program.
 * @version 0.1
 * @date 2019-05-14
 * 
 * @copyright Charles Stoll, PSU, ECE 373: EMbedded Drivers and Operating Systems, May 8th, 2019 lecture. 
 * 
 */
 
#include    <unistd.h>
#include    <stdio.h>
#include    <fcntl.h>
#include    <stdlib.h>
#include    <sys/types.h>
#include    <sys/mman.h>
#include    <stdint.h>

#define LED1_ON 0xe
#define LED2_ON 0xe00
#define LED3_ON 0xe0000
#define LED4_ON 0xe000000
#define LED_CTL_REG 0xE00
#define E1000_REGION0 0xf8200000
#define E1000_REGION0_SIZE 0x20000

/*  Global Vairables    */
static int dev_mem_fd;

void main(int argc, char* argv[]){

    /*  Initialize and assign memory attributes    */
    int *base_addr = 0;
    int *led_addr = 0;
    int mem_window_sz = E1000_REGION0_SIZE;
    int led_offset = LED_CTL_REG;
    int target_region = E1000_REGION0;

    
    /*  Open memory map  */
    dev_mem_fd = open("/dev/mem", O_RDWR);

    /*  Map to memory   */
    base_addr = mmap(NULL, mem_window_sz, PROT_READ | PROT_WRITE, MAP_SHARED, dev_mem_fd, target_region);    // NULL defers the location of the map to the kernel.

    if(base_addr == MAP_FAILED){
        printf("mmap failure.\n");
        return;
    }

    printf("base_addr = %x\n", base_addr);

    /*  Generate the LED Control register address   */
    led_addr = (uint32_t *) (led_offset + base_addr);

    printf("LED Control Register address = %x\n", led_addr);

    /*  Data operations */
    *led_addr = LED1_ON;
    sleep(2);
    *led_addr = LED2_ON;
    sleep(2);
    *led_addr = LED3_ON;
    sleep(2);
    *led_addr = LED4_ON;
    //...
    //... Assignment 4 required operations.

    /*  Unmap the memory region */
    munmap(base_addr, mem_window_sz);

    /*  Close fd    */
    close(dev_mem_fd);

    /* End program  */
    return;
}
