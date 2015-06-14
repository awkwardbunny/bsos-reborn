#include <system.h>
#include <vga.h>

char buf[1024] = {-1};
uint32_t buf_i = -1;

void printf(char *fmt, ...){
	
	buf_i = 0;
	char **arg_ptr = &fmt;
	char *s;
	uint32_t fmt_i = 0;

	for(; fmt[fmt_i]; fmt_i++){
		char c = fmt[fmt_i];
		if(c != '%'){
			buf[buf_i++] = c;
			continue;
		}
		
		switch(fmt[++fmt_i]){
			case 's':
				s = *(++arg_ptr);
				size_t len = strlen(s);
				memcpy(&(buf[buf_i]), s, len);
				buf_i += len;
				break;
			case 'c':
				buf[buf_i] = (char)*(++arg_ptr);
				break;
		}
	}

	buf[buf_i] = '\0';
	puts(buf);
}