#include <system.h>

void *memcpy(void *dest, const void *src, size_t count){
	uint8_t *a = dest;
	const uint8_t *b = src;
	for(size_t i = 0; i < count; i++){
		a[i] = b[i];
	}
	return dest;
}

void *memset (void *dest, uint8_t val, size_t count){
	uint8_t *a = dest;
	for(size_t i = 0; i < count; i++){
		a[i] = val;
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

char* itoa(int val){
	static char buf[32] = {0};
	int i = 30;
	for(; val && i; --i, val/=16)
		buf[i] = "0123456789abcdef"[val % 16];
	return &buf[i+1];
}