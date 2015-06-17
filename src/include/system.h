#ifndef SYSTEM_H
#define SYSTEM_H

/* stdint.h */
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned long uintptr_t;

/* stddef.h */
#define NULL ((void*)0)
typedef unsigned long size_t;

void *memcpy (void *dest, const void *src, size_t count);
void *memset (void *dest, uint8_t val, size_t count);
uint16_t *memsetw (uint16_t *dest, uint16_t val, size_t count);
size_t strlen (const char *str);
char* itoa(int val);

/* printf */
void printf(const char *fmt, ...);

#endif