#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>

void kernel_main(void)
{
	initGdt();
	terminal_initialize();
	printf("GDT initialized\n");
	printf("Terminal initialized\n");
	initIdt();
	printf("IDT initialized\n");
	printf("I love you!\n");
}
