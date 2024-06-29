#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Function prototypes
void hex_string_to_byte_array(const char *hex_string, uint8_t *byte_array, size_t byte_array_size);
void print_mac_address(const char *label, uint8_t *mac);
void print_ipv4_address(const char *label, uint32_t ip);
void print_ipv6_address(const char *label, uint8_t *ip);
void parse_and_print_udp_packet(const uint8_t *byte_array, size_t byte_array_size);


#endif // FUNCTION_H_INCLUDED
