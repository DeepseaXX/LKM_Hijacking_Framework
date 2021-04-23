#include <linux/kprobes.h>

MODULE_LICENSE("GPL"); //for exporting kprobes

unsigned long (*kln_pointer)(const char *name) = NULL;

#define KPROBE_LOOKUP 1
static struct kprobe kp = {
    .symbol_name = "kallsyms_lookup_name"
};

unsigned long new_kallsyms_lookup_name(const char *name){
	if (kln_pointer == NULL){
	    register_kprobe(&kp);

	    kln_pointer = (unsigned long (*)(const char *name)) kp.addr;

	    unregister_kprobe(&kp);
	}
	return kln_pointer(name);
}
