#ifndef FUNCTION_HOOKING_H

#define FUNCTION_HOOKING_H

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>

#define assembly_len 12

extern char assembly_jump_opc[assembly_len]; //will be defined later

struct hooked_function
{
	char function_name[25]; //adjustable...
	char original_function_asm[assembly_len];
	void *original_function;
	void *fake_function;
};

int hook_function(struct hooked_function *f);

int reset_function(struct hooked_function *f);

#endif