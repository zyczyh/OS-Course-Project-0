#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

/* array for getting the syscallname with index */

char syscallnamemapping[27][30] = {"freemem", "chprio", "getpid", \
"getprio", "gettime", "kill", \
"receive", "recvclr", "recvtim", \
"resume", "scount", "sdelete", \
"send", "setdev", "setnok", \
"screate", "signal", "signaln", \
"sleep", "sleep10", "sleep100", \
"sleep1000", "sreset", "stacktrace", \
"suspend", "unsleep", "wait"};

int traceflag;

void printsyscallsummary()
{
	int i = 0;
	int j = 0;
	int flag = 0;

	kprintf("void printsyscallsummary()\n");
	for(i = 0; i < NPROC; i = i + 1)
	{
		flag = 0;
		for(j = 0; j < 27; j = j + 1)
		{
			if(proctab[i].syscallcounter[j] != 0)
			{
				if(flag == 0)
				{
					kprintf("Process[pid:%d]\n", i);
					flag = 1;
				}
				kprintf("\tSyscall:sys_%s, count:%d, average execution time: %d(ms)\n", syscallnamemapping[j], proctab[i].syscallcounter[j], proctab[i].syscalltime[j]/proctab[i].syscallcounter[j]);
			}
		}
	}
}

void syscallsummary_start()
{
	int i = 0;
	int j = 0;

	traceflag = 1;
	for(i = 0; i < NPROC; i = i + 1)
	{
		for(j = 0; j < 27; j = j + 1)
		{
			proctab[i].syscallcounter[j] = 0;
			proctab[i].syscalltime[j] = 0;
		}
	}
}

void syscallsummary_stop()
{
	traceflag = 0;
}