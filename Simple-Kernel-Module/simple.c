/*
 * Use make to compile this module using the Makefile.
 * sudo insmod simple.ko - to load the module.
 * lsmod - serach for loaded modules.
 * dmesg - to check the kernel log buffer.
 * sudo rmmod simple - to remove module.
 * sudo dmesg -c - to clear the kernel log buffer.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

/* This function is called when the module
   is loaded. */

int simple_init(void) {
    printk(KERN_INFO "Loading Module\n");
    return 0;
}

/* This function is called when the
   module is removed. */
void simple_exit(void) {
    printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A Simple Kernel Module");
MODULE_AUTHOR("Kaleshwar Singh");
