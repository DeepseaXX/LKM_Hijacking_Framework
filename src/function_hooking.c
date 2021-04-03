#include "function_hooking.h"
#include "new_kln.h"

char assembly_jump_opc[assembly_len] = {0x48, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0xc3};
//assembly for:
//mov rax, (address)
//push rax
//ret

//https://jm33.me/hook-system-calls-in-linux-5x.html
static inline void
write_cr0_forced(unsigned long val)
{
    unsigned long __force_order;

    /* __asm__ __volatile__( */
    asm volatile(
        "mov %0, %%cr0"
        : "+r"(val), "+m"(__force_order));
}

static inline void
protect_memory(void)
{
    write_cr0_forced(read_cr0());
}

static inline void
unprotect_memory(void)
{
    write_cr0_forced(read_cr0() & ~0x00010000);
}


int hook_function(struct hooked_function *f){

	f->original_function = (void*)new_kallsyms_lookup_name(f->function_name); //look up the function addr
	memcpy(f->original_function_asm, f->original_function, assembly_len); //save the assembly of the function

	unsigned long *ret_address = (unsigned long *)(assembly_jump_opc + 2); //pointer to the ret addr in the assembly code
	*ret_address = f->fake_function; //assign the fake function's address
	

	unprotect_memory(); //unprotect kernel memory to write the new assembly
	memcpy(f->original_function, assembly_jump_opc, assembly_len); //werite the new assembly with the return to the fake function
	protect_memory(); //protect the kernel memory back

	return 1;
}

int reset_function(struct hooked_function *f){

	unprotect_memory(); //unprotect kernel memory to write the new assembly
	memcpy(f->original_function, f->original_function_asm, assembly_len); //write the old assembly
	protect_memory(); //protect the kernel memory back


	return 1;
}