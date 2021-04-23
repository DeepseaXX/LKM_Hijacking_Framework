#ifndef SYSCALL_HOOKING_H

#define SYSCALL_HOOKING_H

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kprobes.h>
#include "new_kln.h"
#include <linux/syscalls.h>

struct hooked_syscall {
	unsigned long syscall;
	void *original_syscall;
	void *fake_syscall;
};

unsigned long* hook_syscall(struct hooked_syscall *sys);

int reset_syscall(struct hooked_syscall *sys);

#endif