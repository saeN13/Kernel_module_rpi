#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#define LICENSE		"Proprietary"
#define DRIVER_AUTHOR	"Roberto de la Cruz, Juan Samper"
#define DRIVER_DESC	"Allows comunication between a RBPi and an FPGA SPARTAN 6 using de GPIO RBPi pins"
#define SUPORTED_DEVICE "Tested on a Raspberry PI model A"

static char* mystring = "My name is Johny Macarroni.";

module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "A character string");

static int __init init_hello_4(void)
{
	printk(KERN_INFO "Hello, world 4\n");
	printk(KERN_INFO "mystring is a string: %s\n", mystring);
	return 0;
}

static void __exit cleanup_hello_4(void)
{
	printk(KERN_INFO "Goodbye, world 4\n");
}

module_init(init_hello_4);
module_exit(cleanup_hello_4);

MODULE_LICENSE(LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE(SUPORTED_DEVICE);
