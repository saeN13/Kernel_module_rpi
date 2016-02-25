#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>

#define LICENSE		"Proprietary"
#define DRIVER_AUTHOR	"Roberto de la Cruz, Juan Samper"
#define DRIVER_DESC	"Allows comunication between a RBPi and an FPGA SPARTAN 6 using de GPIO RBPi pins"
#define SUPORTED_DEVICE "Tested on a Raspberry PI model A"
#define VERSION		"0.1"


/*#define GPIO_BASE               0x20200000 This one is for the usermode*/

#define GPIO_BASE               0xf2200000 /*This is the kernel memory adress*/
#define BLOCK_SIZE              4096

/* GPIO macros  */

#define INP_GPIO_04(b)   *(volatile unsigned int *)(0x00000000+b) &= (unsigned int)0xFFFF8FFF /* &= Binary AND assignment*/
#define OUT_GPIO_04(b)   *(volatile unsigned int *)(0x00000000+b) |= (unsigned int)0x00001000 /* |= Binary OR  assignment*/

#define GPIO_SET_04(b)  *(volatile unsigned int *)(0x0000001C+b) |= 0x10
#define GPIO_CLR_04(b)  *(volatile unsigned int *)(0x00000028+b) |= 0x10


struct timer_list led_timer; //Type of the led_timer variable: timer_list
char kbledstatus = 0;
int status = 0;

/* main function */

static void hello_timer(unsigned long ptr)
{
	printk("jiffies + HZ = %ld + %d\n", jiffies, HZ);
	if (status == 0)
	{
		GPIO_SET_04(GPIO_BASE);
		status = 1;
	} else {
		GPIO_CLR_04(GPIO_BASE);
		status = 0;
	}
	
	led_timer.expires = jiffies + HZ;
	add_timer(&led_timer);
}

static int hello_init(void){
	printk("Hello, LED World!\n");

	OUT_GPIO_04(GPIO_BASE);

	init_timer(&led_timer);
	led_timer.function = hello_timer;
	led_timer.data = (unsigned long) &kbledstatus;
	led_timer.expires = jiffies + HZ;
	add_timer(&led_timer);
	
	return 0;	
}

static void hello_exit(void){
	del_timer(&led_timer);
	printk("Goodbye!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE(LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE(SUPORTED_DEVICE);
MODULE_VERSION(VERSION);


/*
jiffies variable is used in the Linux operating system that tell us the
ticks that have passed since the system was booted. In each interruption
of the internal system clock the value of the variable is increased by one.
This variable is defined in the file of the core code in linux/jiffies.h

This variable is usually combined with another variable (HZ) that tells us,
as its name suggests, the frequency of the internal clock, here is why these
two variables allow us to calculate the jiffies per second of a Machine.
*/
