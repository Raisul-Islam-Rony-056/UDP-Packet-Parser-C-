// Function to swap MAC addresses

#include"../includes/Header_Structure.h"
#include"../includes/Swap_Property.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
 * Parameter:
   - eth: Pointer to an `eth_header` structure representing the Ethernet header.

 * What the function does:
   - Swaps the source and destination MAC addresses within the given Ethernet header (`eth`).
   - Uses a temporary buffer (`temp_mac`) to facilitate the swap using `memcpy`.

 * Return Type:
   - void: The function modifies the `eth` structure in place.
 */
void swap_mac_addresses(struct eth_header *eth) {
    uint8_t temp_mac[6];
    memcpy(temp_mac, eth->src_mac, 6);
    memcpy(eth->src_mac, eth->dest_mac, 6);
    memcpy(eth->dest_mac, temp_mac, 6);
}

/*
 * Parameter:
   - ipv4: Pointer to an `ipv4_header` structure representing the IPv4 header.

 * What the function does:
   - Swaps the source and destination IPv4 addresses within the given IPv4 header (`ipv4`).
   - Uses a temporary variable (`temp_ip`) to facilitate the swap.

 * Return Type:
   - void: The function modifies the `ipv4` structure in place.
 */
void swap_ipv4_addresses(struct ipv4_header *ipv4) {
    uint32_t temp_ip = ipv4->src_ip;
    ipv4->src_ip = ipv4->dest_ip;
    ipv4->dest_ip = temp_ip;
}

/*
 * Parameter:
   - ipv6: Pointer to an `ipv6_header` structure representing the IPv6 header.

 * What the function does:
   - Swaps the source and destination IPv6 addresses within the given IPv6 header (`ipv6`).
   - Uses a temporary buffer (`temp_ip`) to facilitate the swap using `memcpy`.

 * Return Type:
   - void: The function modifies the `ipv6` structure in place.
 */
void swap_ipv6_addresses(struct ipv6_header *ipv6) {
    uint8_t temp_ip[16];
    memcpy(temp_ip, ipv6->src_ip, 16);
    memcpy(ipv6->src_ip, ipv6->dest_ip, 16);
    memcpy(ipv6->dest_ip, temp_ip, 16);
}

/*
 * Parameter:
   - udp: Pointer to a `udp_header` structure representing the UDP header.

 * What the function does:
   - Swaps the source and destination UDP ports within the given UDP header (`udp`).
   - Uses a temporary variable (`temp_port`) to facilitate the swap.

 * Return Type:
   - void: The function modifies the `udp` structure in place.
 */
void swap_port_number(struct udp_header *udp) {
    uint16_t temp_port = udp->src_port;
    udp->src_port = udp->dest_port;
    udp->dest_port = temp_port;
}
