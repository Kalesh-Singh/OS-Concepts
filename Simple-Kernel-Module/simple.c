/*
 * Use make to compile this module using the Makefile.
 * sudo insmod simple.ko - to load the module.
 * lsmod - serach for loaded modules.
 * dmesg - to check the kernel log buffer.
 * sudo rmmod simple - to remove module.
 * sudo dmesg -c - to clear the kernel log buffer.
 */

#include <linux/slab.h>			// kmalloc()
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>

// The node struct for the linked list.
struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
}; 

// Create the list head.
static LIST_HEAD(birthday_list);

#define print_list(curr, head, list) \
	printk(KERN_INFO "["); \
	list_for_each_entry(curr, head, list) { \
		printk(KERN_INFO "%d/%d/%d ", curr->month, curr->day, curr->year); \
	} \
	printk(KERN_INFO "]\n");

// ^Include the new line to flush the kernel buffer.


/* This function is called when the module
   is loaded. */
int simple_init(void) {

    printk(KERN_INFO "Loading Module\n");

	// Create 5 new nodes for the list.
	struct birthday* person1;
	person1 = kmalloc(sizeof(*person1), GFP_KERNEL);
	person1->day = 2;
	person1->month = 8;
	person1->year = 1995;
	INIT_LIST_HEAD(&person1->list);

	struct birthday* person2;
	person2 = kmalloc(sizeof(*person2), GFP_KERNEL);
	person2->day = 10;
	person2->month = 3;
	person2->year = 1983;
	INIT_LIST_HEAD(&person2->list);

	struct birthday* person3;
	person3 = kmalloc(sizeof(*person3), GFP_KERNEL);
	person3->day = 19;
	person3->month = 10;
	person3->year = 1991;
	INIT_LIST_HEAD(&person3->list);

	struct birthday* person4;
	person4 = kmalloc(sizeof(*person4), GFP_KERNEL);
	person4->day = 4;
	person4->month = 4;
	person4->year = 1965;
	INIT_LIST_HEAD(&person4->list);

	struct birthday* person5;
	person5 = kmalloc(sizeof(*person5), GFP_KERNEL);
	person5->day = 22;
	person5->month = 10;
	person5->year = 1998;
	INIT_LIST_HEAD(&person5->list);

	// Add nodes to the end of the list.
	list_add_tail(&person1->list, &birthday_list);	
	list_add_tail(&person2->list, &birthday_list);	
	list_add_tail(&person3->list, &birthday_list);	
	list_add_tail(&person4->list, &birthday_list);	
	list_add_tail(&person5->list, &birthday_list);	

	// Print the list to the kernel buffer
	struct birthday* curr;
	print_list(curr, &birthday_list, list);

    return 0;
}

/* This function is called when the
   module is removed. */
void simple_exit(void) {
    printk(KERN_INFO "Removing Module\n");

	struct birthday *curr, *next;
	
	// Delete all elements in the list.	
	list_for_each_entry_safe(curr, next, &birthday_list, list) {
		list_del(&curr->list); kfree(curr);
	}

	print_list(curr, &birthday_list, list);
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A Simple Kernel Module");
MODULE_AUTHOR("Kaleshwar Singh");
