/* chprio.c - chprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * chprio  --  change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
SYSCALL chprio(int pid, int newprio)
{
	STATWORD ps;    
	struct	pentry	*pptr;
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Chprio] = proctab[currpid].syscallcounter[Chprio] + 1;
		starttime = ctr1000;
	}
	disable(ps);
	if (isbadpid(pid) || newprio<=0 ||
	    (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Chprio] = proctab[currpid].syscalltime[Chprio] + (ctr1000 - starttime);
		}
		return(SYSERR);
	}
	pptr->pprio = newprio;
	restore(ps);
	if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Chprio] = proctab[currpid].syscalltime[Chprio] + (ctr1000 - starttime);
	}
	return(newprio);
}
