#ifndef SWAP_PROPERTY_H_INCLUDED
#define SWAP_PROPERTY_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include"../includes/Header_Structure.h"

void swap_mac_addresses(struct eth_header * eth);
void swap_ipv4_addresses(struct ipv4_header * ipv4);
void swap_ipv6_addresses(struct ipv6_header *ipv6);
void swap_port_number(struct udp_header * udp);


#endif // SWAP_PROPERTY_H_INCLUDED
