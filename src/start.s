.code32

.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

# Multiboot Header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Stack (Temporary)
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function

# Start (Entry Point)
_start:
	movl $stack_top, %esp

	call kernel_main # KERNEL! :)

	cli
	hlt
.Lhang:
	jmp .Lhang

# Descriptor Tables
# GDT
.global gdt_flush
.extern gp
gdt_flush:
	
	lgdt (gp)
	
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	jmp $0x08, $flush2

flush2:
	ret

# IDT
.global idt_flush
.extern ip
idt_flush:
	lidt (ip)
	ret

# ISR Macro
.macro ISR num, ec=1
.global isr\num
isr\num:
	cli
.if \ec
	push $0
.endif
	push $\num
	jmp isr_common
.endm

# ISRs
ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8,0 # Error codes are pushed, so don't put dummy
ISR 9
ISR 10,0
ISR 11,0
ISR 12,0
ISR 13,0
ISR 14,0
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19
ISR 20
ISR 21
ISR 22
ISR 23
ISR 24
ISR 25
ISR 26
ISR 27
ISR 28
ISR 29
ISR 30
ISR 31

.extern isr_handler
isr_common:
	pusha

	push %ds
	push %es
	push %fs
	push %gs

	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs

	call isr_handler

	pop %gs
	pop %fs
	pop %es
	pop %ds

	popa

	add $8, %esp # Add 8 to 'pop' the two numbers off the stack
	sti
	iret

.size _start, . - _start #Should this be here or up there?
