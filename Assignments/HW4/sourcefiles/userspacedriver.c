/**
 * @file userspacedriver.c
 * @author Michael Escue
 * @brief Userspace driver program based on ECE 373 lectures by Charles Stoll and Peter (PJ) Waskiewicz 
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
#include    <errno.h>

#define _LOOPS 5
#define LED0_ON 0xe
#define LED0_OFF 0x4e
#define LED1_ON 0xe00
#define LED1_OFF 0x4e00
#define LED2_ON 0xe0000
#define LED2_OFF 0x4e0000
#define LED3_ON 0xe000000
#define LED3_OFF 0x4e000000
#define LEDS_OFF (LED0_OFF | LED1_OFF | LED2_OFF | LED3_OFF)
#define LED_CTL_REG 0x00E00
#define E1000_REGION0 0xf8200000
#define E1000_REGION0_SIZE 128000
#define GPRC_OFFSET 0x04074

/*  Global Vairables    */
static int dev_mem_fd;

void main(){

    /*  Initialize and assign memory attributes    */
    volatile void *base_addr = 0;
    uint32_t *led_addr = 0;
    size_t mem_window_sz = E1000_REGION0_SIZE;
    size_t led_offset = LED_CTL_REG;
    off_t page_offset = E1000_REGION0 & ~(sysconf(_SC_PAGE_SIZE) - 1);
    errno = 0;
    int ledctl_initial_val = 0;

    /*  Open memory map  */
    if((dev_mem_fd = open("/dev/mem", O_RDWR)) == -1 ){
        perror("Open /dev/mem failure:\n");
    }

    /*  Map to memory   */
    base_addr = mmap(NULL, mem_window_sz, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_32BIT, dev_mem_fd, page_offset);    // NULL defers the location of the map to the kernel.

    if(base_addr == MAP_FAILED){
        perror("mmap failure:\n");
        return ;
    }

    /*  Generate the LED Control register address   */
    led_addr = (uint32_t *) (led_offset + base_addr);

    /*  Save and display initial value of LEDCTL    */
    ledctl_initial_val = *led_addr;
    printf("Initial LEDCTL Register Value = 0x%x\n", *led_addr);

    /*  LED operations */
    *led_addr = LED0_ON | LED1_OFF | LED2_ON | LED3_OFF;    //LEDs2 and 0 on.
    sleep(2);
    *led_addr = LEDS_OFF;   //ALL LEDs off.
    sleep(2);

    for(int i = 0; i < (_LOOPS); i++){  //Begin rotation LED on/off.
        
        *led_addr = LED0_ON << ((i%5)*8);   // Rotate the on LED.

        sleep(1);
    }

    *led_addr = ledctl_initial_val; //Restore initial LEDCTL value

    /* Read Good Packets Received Register */
    size_t gprc_offset = GPRC_OFFSET;
    uint32_t *gprc = (uint32_t *) (gprc_offset + base_addr);
    printf("GPRC Count = %d\n", *gprc);

    /*  Unmap the memory region */
    munmap(base_addr, mem_window_sz);

    /*  Close fd    */
    close(dev_mem_fd);

    /* End program  */
    return;
}
