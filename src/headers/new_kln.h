#ifndef NEW_KLN_H

#define NEW_KLN_H

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>

unsigned long new_kallsyms_lookup_name(const char *name);

#endif
