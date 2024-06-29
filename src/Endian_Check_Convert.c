#include"../includes/Endian_Check_Convert.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/*
 * Parameter: None
 *
 * What the function does:
 *   1. Creates a 16-bit unsigned integer (`test`) with the value 0x0001.
 *   2. Checks the least significant byte of `test` to determine the endianness of the system.
 *   3. Returns 1 if the system is little-endian (where the least significant byte is stored first),
 *      otherwise returns 0 (indicating big-endian architecture).
 *
 * Return Type:
 *   - int: Returns 1 if the system is little-endian, 0 otherwise.
 */

int is_little_endian() {
    uint16_t test = 0x0001;
    return *((uint8_t*)&test);
}

/*
 * Parameter:
   - netshort: The 16-bit unsigned integer value in network byte order (big-endian) to be converted.

 * What the function does:
   1. Checks if the system architecture is little-endian using `is_little_endian()`.
   2. If the system is little-endian, converts the network byte order (`netshort`) to host byte order (little-endian).
   3. Otherwise, returns the `netshort` value unchanged since it's already in host byte order (big-endian).
   4. The conversion swaps the byte order of `netshort` by shifting and bitwise OR operations.
   5. Returns the converted or unchanged `netshort` value.

 * Return Type:
   - `uint16_t`: The 16-bit unsigned integer value converted to host byte order if necessary.
 */
uint16_t ntohs_custom(uint16_t netshort) {
    if (is_little_endian()) {
        return (netshort >> 8) | (netshort << 8);
    }
    return netshort;
}

/*
 * Parameter:
   - netlong: The 32-bit unsigned integer value in network byte order (big-endian) to be converted.

 * What the function does:
   1. Checks if the system architecture is little-endian using `is_little_endian()`.
   2. If the system is little-endian, converts the network byte order (`netlong`) to host byte order (little-endian).
   3. Otherwise, returns the `netlong` value unchanged since it's already in host byte order (big-endian).
   4. The conversion swaps the byte order of `netlong` by shifting and bitwise OR operations.
   5. Returns the converted or unchanged `netlong` value.

 * Return Type:
   - `uint32_t`: The 32-bit unsigned integer value converted to host byte order if necessary.
 */
uint32_t ntohl_custom(uint32_t netlong) {
    if (is_little_endian()) {
        return ((netlong >> 24) & 0x000000FF) |
               ((netlong >> 8)  & 0x0000FF00) |
               ((netlong << 8)  & 0x00FF0000) |
               ((netlong << 24) & 0xFF000000);
    }
    return netlong;
}
