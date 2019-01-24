#include <stdio.h>

extern unsigned long _etext;
extern unsigned long _edata;
extern unsigned long _end;

void printsegaddress()
{
	kprintf("void printsegaddress()\n");
	kprintf("Current: etext[0x%08lx] = 0x%08lx, edata[0x%08lx] = 0x%08lx, ebss[0x%08lx] = 0x%08lx\n", &_etext, _etext, &_edata, _edata, &_end, _end);
	kprintf("Preceding: etext[0x%08lx] = 0x%08lx, edata[0x%08lx] = 0x%08lx, ebss[0x%08lx] = 0x%08lx\n", &_etext - 1, *(&_etext - 1), &_edata - 1, *(&_edata - 1), &_end - 1, *(&_end - 1));
	kprintf("After: etext[0x%08lx] = 0x%08lx, edata[0x%08lx] = 0x%08lx, ebss[0x%08lx] = 0x%08lx\n", &_etext + 1, *(&_etext + 1), &_edata + 1, *(&_edata + 1), &_end + 1, *(&_end + 1));
}