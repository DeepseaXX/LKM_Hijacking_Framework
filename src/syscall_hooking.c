#include "syscall_hooking.h"
#include "new_kln.h"

unsigned long *syscall_table_p;
int got_table = 0;

//https://jm33.me/hook-system-calls-in-linux-5x.html
static inline void write_cr0_forced(unsigned long val)
{
    unsigned long __force_order;

    /* __asm__ __volatile__( */
    asm volatile(
        "mov %0, %%cr0"
        : "+r"(val), "+m"(__force_order));
}

static inline void protect_memory(void)
{
    write_cr0_forced(read_cr0());
}

static inline void unprotect_memory(void)
{
    write_cr0_forced(read_cr0() & ~0x00010000);
}

void get_syscall_table(void) {
	if (!got_table){
		syscall_table_p = (unsigned long *)new_kallsyms_lookup_name("sys_call_table");
		got_table = 1;
	}
}

unsigned long* hook_syscall(struct hooked_syscall *sys){

	get_syscall_table();

	unprotect_memory();
	sys->original_syscall = (void*)syscall_table_p[sys->syscall];
	syscall_table_p[sys->syscall] = (unsigned long)sys->fake_syscall;
	protect_memory();

	return sys->original_syscall;
}

int reset_syscall(struct hooked_syscall *sys){
	unprotect_memory();

	syscall_table_p[sys->syscall] = (unsigned long)sys->original_syscall;

	protect_memory();
	return 1;
}