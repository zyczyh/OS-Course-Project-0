/* getprio.c - getprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * getprio -- return the scheduling priority of a given process
 *------------------------------------------------------------------------
 */
SYSCALL getprio(int pid)
{
	STATWORD ps;    
	struct	pentry	*pptr;
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Getprio] = proctab[currpid].syscallcounter[Getprio] + 1;
		starttime = ctr1000;
	}
	disable(ps);
	if (isbadpid(pid) || (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Getprio] = proctab[currpid].syscalltime[Getprio] + (ctr1000 - starttime);
		}
		return(SYSERR);
	}
	restore(ps);
	if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Getprio] = proctab[currpid].syscalltime[Getprio] + (ctr1000 - starttime);
	}
	return(pptr->pprio);
}
