#ifndef ENDIAN_CHECK_CONVERT_H_INCLUDED
#define ENDIAN_CHECK_CONVERT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint16_t ntohs_custom(uint16_t netshort);
uint32_t ntohl_custom(uint32_t netlong);
int is_little_endian();

#endif // ENDIAN_CHECK_CONVERT_H_INCLUDED
