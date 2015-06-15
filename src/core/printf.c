#include <system.h>
#include <vga.h>

/* va_list.h */

typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;

#define va_start(v,l)	__builtin_va_start(v,l)
#define va_end(v)	__builtin_va_end(v)
#define va_arg(v,l)	__builtin_va_arg(v,l)
#define va_copy(d,s)	__builtin_va_copy(d,s)

char buf[1024] = {-1};
uint32_t buf_i = 0;

void getDec(unsigned long val){
	unsigned int n = val/10;
	int r = val % 10;
	if(r < 0){
		r += 10;
		n--;
	}
	if(val >= 10){
		getDec(n);
	}
	buf[buf_i++] = (r+'0');
}

void printf(const char *fmt, ...){
	buf_i = 0;
	va_list args;
	va_start(args, fmt);
	char * s;

	for(const char *f = fmt; *f; f++){
		if(*f != '%'){
			buf[buf_i++] = *f;
			continue;
		}
		++f;
		
		switch(*f){
			case 's':
				s = (char *)va_arg(args, char *);
				size_t len = strlen(s);
				memcpy(&(buf[buf_i]), s, len);
				buf_i += len;
				break;
			case 'c':
				buf[buf_i++] = (char)va_arg(args, int); //GCC tells me to use int instaed of char?
				break;
			case '%':
				buf[buf_i++] = '%';
				break;
			case 'd':
				getDec((unsigned long)va_arg(args, unsigned long));
				break;
			default:
				buf[buf_i++] = *f;
		}
	}

	va_end(args);
	buf[buf_i] = '\0';
	puts(buf);
}