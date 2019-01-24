/* user.c - main */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

int prX;
void halt();

/*------------------------------------------------------------------------
 *  main  --  user main program
 *------------------------------------------------------------------------
 */

prch(c)
char c;
{
	int i;
	sleep(5);	
}

int main()
{
	kprintf("\n\nHello World, Xinu lives\n\n");
	kprintf("0x%.8x \n", zfunction(0xaabbccdd));
	printsegaddress();
	printtos();
	printprocstks(1);
	kprintf("Task 5 (printsyscallsummary)\n");
	syscallsummary_start();
	resume(prX = create(prch,2000,20,"proc X",1,'A'));
	sleep(10);
	syscallsummary_stop();
	printsyscallsummary();
	return 0;
}
