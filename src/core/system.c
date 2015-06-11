#include "system.h"

uint8_t *memcpy(uint8_t *dest, uint8_t *src, size_t count){
	for(size_t i = 0; i < count; i++){
		dest[i] = src[i];
	}
	return dest;
}

uint8_t *memset (uint8_t *dest, uint8_t val, size_t count){
	for(size_t i = 0; i < count; i++){
		dest[i] = val;
	}
	return dest;
}

uint16_t *memsetw (uint16_t *dest, uint16_t val, size_t count){
	for(size_t i = 0; i < count; i++){
		dest[i] = val;
	}
	return dest;
}

size_t strlen(const char* str){
	size_t ret = 0;
	while ( str[ret] )
		ret++;
	return ret;
}