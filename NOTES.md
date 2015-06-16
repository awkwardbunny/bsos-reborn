Notes
===========
###### 1. In Printf.c, in function printf(const char *fmt, ...): [StackOverflow](http://stackoverflow.com/questions/8491531/standard-c-cast-of-va-arg-return-value-warning) int must be used for variable type instead of char.
###### 2. In multiboot.h, multiboot structure is laid out in the [multiboot specs](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Boot-information-format).