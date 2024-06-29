#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include"../includes/Endian_Check_Convert.h"
#include"../includes/Function.h"
#include"../includes/Header_Structure.h"
#include"../includes/Swap_Property.h"
#define BUF_LEN 128
/*
 * Parameter:
   - filename: Null-terminated string representing the name of the file to be read.

 * What the function does:
   - Opens a file specified by `filename` in read mode.
   - Checks if the file was opened successfully; if not, prints an error message and returns NULL.
   - Determines the size of the file by seeking to the end and using `ftell`.
   - Allocates a buffer (`hex_stream`) to hold the file's content plus a null terminator.
   - Reads the file's content into the allocated buffer and adds a null terminator at the end.
   - Closes the file and returns the buffer containing the file's content as a null-terminated string.

 * Return Type:
   - char*: Pointer to the buffer containing the file's content as a null-terminated string.
            Returns NULL if the file cannot be opened or if memory allocation fails.
 */
char* read_hex_stream_from_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *hex_stream = (char *)malloc(file_size + 1);
    if (hex_stream == NULL)
    {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    fread(hex_stream, 1, file_size, file);
    hex_stream[file_size] = '\0';

    fclose(file);
    return hex_stream;
}


// Main function
int main()
{
    // File containing the UDP packet hex stream
    const char *filename = "Database/Hex_Stream.txt";

    if(is_little_endian())
    {
        printf("Host Machine Is Little Endian\n");
    }
    else
    {
        printf("Host Machine Is Big Endian\n");
    }

    printf("\n");

    // Read the hex stream from the file
    char *udp_packet_hex_stream = read_hex_stream_from_file(filename);
    if (udp_packet_hex_stream == NULL)
    {
        fprintf(stderr, "Failed to read hex stream from file\n");
        return EXIT_FAILURE;
    }

    // Convert hex stream to byte array
    size_t byte_array_size = strlen(udp_packet_hex_stream) / 2;
    uint8_t byte_array[byte_array_size];
    hex_string_to_byte_array(udp_packet_hex_stream, byte_array, byte_array_size);

    uint8_t input_buffer[BUF_LEN];
    memcpy(input_buffer,byte_array,BUF_LEN);

    // Parse, swap MAC addresses, IP addresses, and ports, then print UDP packet information
    parse_and_print_udp_packet(input_buffer, BUF_LEN);
    printf("\n");
    printf("After Swapping, Parsing From Output Buffer:\n");
    uint8_t output_buffer[BUF_LEN];
    memcpy(output_buffer,input_buffer,BUF_LEN);
    parse_and_print_udp_packet(input_buffer, BUF_LEN);



    return 0;
}
