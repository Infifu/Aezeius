#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>

void kernel_main(void)
{
	initGdt();
	terminal_initialize();
	printf("Hello, kernel World!\n");
	printf("I love you!\n");
}
