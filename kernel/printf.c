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
int buf_i = 0;

void printf(const char *fmt, ...){
	buf_i = 0;
	va_list args;
	va_start(args, fmt);

	char * s;
	int num;

	for(const char *f = fmt; *f; f++){
		if(*f != '%'){
			buf[buf_i++] = *f;
			continue;
		}
		++f;
		
		if(*f == 's'){
			s = va_arg(args, char *);
			size_t len = strlen(s);
			memcpy(&(buf[buf_i]), s, len);
			buf_i += len;
		}else if(*f == 'c'){
			buf[buf_i++] = (char)va_arg(args, int); //#1 (See NOTES.md)
		}else if(*f == '%'){
			buf[buf_i++] = '%';
		}else if(*f == 'd'){
			num = va_arg(args, int);
			if(num < 0){
				buf[buf_i++] = '-';
				num = 0-num;
			}
			int beg = buf_i;
			while(num > 9){
				int r = num % 10;
				num = (num-r)/10;
				buf[buf_i++] = (r+'0');
			}
			buf[buf_i++] = (num+'0');
			
			// Reverse
			for(int i = 0; i < (buf_i - beg) / 2; i++){
				char c = buf[beg+i];
				buf[beg+i] = buf[buf_i - i - 1];
				buf[buf_i - i - 1] = c;
			}
		}else if(*f >= '0' && *f <= '9'){
			int i = *f-'0';
			f++;
			if(*f == 'x'){
				num = va_arg(args, int);
				buf[buf_i++] = '0';
				buf[buf_i++] = 'x';
				while (i-- > 0) {
					buf[buf_i++] = "0123456789abcdef"[(num>>(i*4))&0xF];
				}
			}
		}else if(*f == 'x'){
			num = va_arg(args, int);
			buf[buf_i++] = '0';
			buf[buf_i++] = 'x';
			int i = 8;
			while (i-- > 0) {
				buf[buf_i++] = "0123456789abcdef"[(num>>(i*4))&0xF];
			}
		}else{
			buf[buf_i++] = *f;
		}
	}

	va_end(args);
	buf[buf_i] = '\0';
	puts(buf);
}
