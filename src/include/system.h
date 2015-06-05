#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
#include <stddef.h>

uint8_t *memcpy (uint8_t *dest, uint8_t *src, size_t count);
uint8_t *memset (uint8_t *dest, uint8_t val, size_t count);
uint16_t *memsetw (uint16_t *dest, uint16_t val, size_t count);
size_t strlen (const char *str);

#endif