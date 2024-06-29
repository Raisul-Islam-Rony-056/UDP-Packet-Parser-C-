#ifndef HEADER_STRUCTURE_H_INCLUDED
#define HEADER_STRUCTURE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Ethernet header structure
struct eth_header {
    uint8_t dest_mac[6];
    uint8_t src_mac[6];
    uint16_t eth_type;
};

// IPv4 header structure
struct ipv4_header {
    uint8_t ihl:4, version:4;
    uint8_t tos;
    uint16_t tot_len;
    uint16_t id;
    uint16_t frag_off;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t check;
    uint32_t src_ip;
    uint32_t dest_ip;
};

// IPv6 header structure
struct ipv6_header {
    uint8_t ihl:4, version:4;
    uint8_t flow_label[3];
    uint16_t payload_len;
    uint8_t next_header;
    uint8_t hop_limit;
    uint8_t src_ip[16];
    uint8_t dest_ip[16];
};

// UDP header structure
struct udp_header {
    uint16_t src_port;
    uint16_t dest_port;
    uint16_t length;
    uint16_t checksum;
};


#endif // HEADER_STRUCTURE_H_INCLUDED
