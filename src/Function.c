#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include"../includes/Function.h"
#include"../includes/Endian_Check_Convert.h"
#include"../includes/Swap_Property.h"
#include"../includes/Header_Structure.h"
/*
 * Parameter:
   - c: Character representing a hexadecimal digit ('0'-'9', 'a'-'f', 'A'-'F').

 * What the function does:
   - Converts a hexadecimal character (`c`) to its corresponding integer value.
   - Handles both lowercase ('a'-'f') and uppercase ('A'-'F') hexadecimal characters.
   - Returns the integer value of the hexadecimal character. Returns -1 if `c` is not a valid hexadecimal digit.

 * Return Type:
   - int: Integer value of the hexadecimal character, or -1 if `c` is not a valid hexadecimal digit.
 */
int hex_char_to_int(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else if (c >= 'a' && c <= 'f')
    {
        return c - 'a' + 10;
    }
    else if (c >= 'A' && c <= 'F')
    {
        return c - 'A' + 10;
    }
    else
    {
        return -1;
    }
}

/*
 * Parameter:
   - hex_string: Null-terminated string containing hexadecimal characters to convert.
   - input_buffer: Pointer to a uint8_t array where the converted byte array will be stored.
   - input_buffer_size: Size of the input_buffer array, indicating the number of bytes to convert.

 * What the function does:
   - Converts a null-terminated hexadecimal string (`hex_string`) into a byte array (`input_buffer`).
   - Processes each pair of hexadecimal characters from `hex_string`, converting them into bytes and storing them in `input_buffer`.
   - Checks for invalid hexadecimal characters in `hex_string` and exits with an error message if found.

 * Return Type:
   - void: The function modifies the `input_buffer` array in place.
 */
void hex_string_to_byte_array(const char *hex_string, uint8_t *input_buffer, size_t input_buffer_size)
{
    for (size_t i = 0; i < input_buffer_size; i++)
    {
        int high_nibble = hex_char_to_int(hex_string[2 * i]);
        int low_nibble = hex_char_to_int(hex_string[2 * i + 1]);
        if (high_nibble == -1 || low_nibble == -1)
        {
            fprintf(stderr, "Invalid hex character in hex string\n");
            exit(EXIT_FAILURE);
        }
        input_buffer[i] = (high_nibble << 4) | low_nibble;
    }
}

/*
 * Parameter:
   - label: Label or description for the MAC address being printed.
   - mac: Pointer to a uint8_t array containing the MAC address bytes (6 bytes).

 * What the function does:
   - Prints the MAC address (`mac`) in a human-readable format with the specified `label`.
   - Formats the MAC address as six pairs of hexadecimal digits separated by colons (e.g., "00:11:22:33:44:55").

 * Return Type:
   - void: The function prints the MAC address to stdout.
 */
void print_mac_address(const char *label, uint8_t *mac)
{
    printf("%s: %02x:%02x:%02x:%02x:%02x:%02x\n", label, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

/*
 * Parameter:
   - label: Label or description for the IPv4 address being printed.
   - ip: IPv4 address in network byte order (big-endian) to be printed.

 * What the function does:
   - Converts and prints the IPv4 address (`ip`) from network byte order to a human-readable format.
   - Formats the IPv4 address as four decimal octets separated by periods (e.g., "192.168.0.1").

 * Return Type:
   - void: The function prints the IPv4 address to stdout.
 */
void print_ipv4_address(const char *label, uint32_t ip)
{
    ip = ntohl_custom(ip);
    printf("%s: %d.%d.%d.%d\n", label, ip & 0xFF, (ip >> 8) & 0xFF, (ip >> 16) & 0xFF, (ip >> 24) & 0xFF);
}

/*
 * Parameter:
   - label: Label or description for the IPv6 address being printed.
   - ip: Pointer to a uint8_t array containing the IPv6 address bytes (16 bytes).

 * What the function does:
   - Prints the IPv6 address (`ip`) in a human-readable format with the specified `label`.
   - Formats the IPv6 address as eight groups of four hexadecimal digits separated by colons (e.g., "fe80::1").

 * Return Type:
   - void: The function prints the IPv6 address to stdout.
 */
void print_ipv6_address(const char *label, uint8_t *ip)
{
    printf("%s: ", label);
    for (int i = 0; i < 16; i += 2)
    {
        printf("%02x%02x", ip[i], ip[i + 1]);
        if (i < 14)
        {
            printf(":");
        }
    }
    printf("\n");
}
/*
 * Parameter:
   - input_buffer: Pointer to the buffer containing the UDP packet data.
   - input_buffer_size: Size of the input buffer in bytes.

 * What the function does:
   1. Parses and prints various headers (Ethernet, IP, and UDP) from the given UDP packet data.
   2. Retrieves and prints original and swapped MAC addresses, IP addresses, and UDP ports.
   3. Supports both IPv4 and IPv6 packets, identified by checking their respective header versions.
   4. If the packet's IP version is unsupported, outputs an error message to stderr and exits the program with failure.

 * Return Type:
   - void: The function does not return a value; it performs operations directly on the input buffer and prints output.
 */

void parse_and_print_udp_packet(const uint8_t *input_buffer, size_t input_buffer_size)
{
    // Ethernet header
    struct eth_header *eth = (struct eth_header *)input_buffer;
    print_mac_address("Original Source MAC", eth->src_mac);
    print_mac_address("Original Destination MAC", eth->dest_mac);
    swap_mac_addresses(eth);

    // IP header
    const uint8_t *ip_start = input_buffer + sizeof(struct eth_header);
    struct ipv4_header *ipv4 = (struct ipv4_header *)ip_start;
    struct ipv6_header *ipv6 = (struct ipv6_header *)ip_start;

    if (ipv4->version == 4)
    {
        // IPv4
        printf("IP Version: IPv4\n");
        print_ipv4_address("Original Source IP", ipv4->src_ip);
        print_ipv4_address("Original Destination IP", ipv4->dest_ip);
        swap_ipv4_addresses(ipv4);

        // UDP header
        struct udp_header *udp = (struct udp_header *)(ip_start + sizeof(struct ipv4_header));
        if(is_little_endian())
        {
            printf("Original Source Port: %u\n", ntohs_custom(udp->src_port));
            printf("Original Destination Port: %u\n", ntohs_custom(udp->dest_port));
        }
        else
        {
            printf("Original Source Port: %u\n", (udp->src_port));
            printf("Original Destination Port: %u\n", (udp->dest_port));
        }

        swap_port_number(udp);

    }
    else if (ipv6->version == 6)
    {
        // IPv6
        printf("IP Version: IPv6\n");
        print_ipv6_address("Original Source IP", ipv6->src_ip);
        print_ipv6_address("Original Destination IP", ipv6->dest_ip);
        swap_ipv6_addresses(ipv6);


        // UDP header
        struct udp_header *udp = (struct udp_header *)(ip_start + sizeof(struct ipv6_header));
        if(is_little_endian())
        {
            printf("Original Source Port: %u\n", ntohs_custom(udp->src_port));
            printf("Original Destination Port: %u\n", ntohs_custom(udp->dest_port));
        }
        else
        {
            printf("Original Source Port: %u\n", (udp->src_port));
            printf("Original Destination Port: %u\n", (udp->dest_port));
        }
        swap_port_number(udp);

    }
    else
    {
        fprintf(stderr, "Unsupported IP version\n");
        exit(EXIT_FAILURE);
    }
}
