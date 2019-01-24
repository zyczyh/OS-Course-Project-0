#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

static unsigned long *esp;

void printprocstks(int priority)
{
	int pid = 0;

	kprintf("void printprocstks(int priority)\n");
	for(pid = 0; pid < NPROC; pid = pid + 1)
	{
		if(proctab[pid].pstate != PRFREE && proctab[pid].pprio > priority)
		{
			kprintf("Process[%s]\n\tpid:%d\n\tpriority:%d\n\tbase:0x%08x\n\tlimit:0x%08x\n\tlen:%d\n\t", proctab[pid].pname, pid, proctab[pid].pprio, proctab[pid].pbase, proctab[pid].plimit, proctab[pid].pstklen);
			if(pid == currpid)
			{
				asm("movl %esp,esp");
				kprintf("pointer:0x%08x \n", esp);
			}
			else
			{
				kprintf("pointer:0x%08x \n", proctab[pid].pesp);
			}
		}
	}
}