#ifndef PACKET_HIDE_H

#define PACKET_HIDE_H

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>


int init_packet_hide(void);

int exit_packet_hide(void);


#endif
