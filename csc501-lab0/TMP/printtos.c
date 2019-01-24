#include <stdio.h>

unsigned long *esp;
unsigned long *ebp;

void printtos()
{
	int i = 0;

	asm("movl %esp,esp");
	asm("movl %ebp,ebp");
	kprintf("void printtos()\n");
	kprintf("Before[0x%08lx]: 0x%08lx \n", esp + 2, *(esp + 2));
	kprintf("After[0x%08lx]: 0x%08lx \n", esp, *esp);
	for(i = 0; i < 4; i = i + 1)
	{
		if(esp + i < ebp)
		{
			kprintf("	element[0x%08lx]: 0x%08lx \n", esp + i, *(esp + i));
		}
		else
		{
			break;
		}
	}
}