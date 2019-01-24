/* sreset.c - sreset */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 *  sreset  --  reset the count and queue of a semaphore
 *------------------------------------------------------------------------
 */
SYSCALL sreset(int sem, int count)
{
	STATWORD ps;    
	struct	sentry	*sptr;
	int	pid;
	int	slist;
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Sreset] = proctab[currpid].syscallcounter[Sreset] + 1;
		starttime = ctr1000;
	}
	disable(ps);
	if (isbadsem(sem) || count<0 || semaph[sem].sstate==SFREE) {
		restore(ps);
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Sreset] = proctab[currpid].syscalltime[Sreset] + (ctr1000 - starttime);
		}
		return(SYSERR);
	}
	sptr = &semaph[sem];
	slist = sptr->sqhead;
	while ((pid=getfirst(slist)) != EMPTY)
		ready(pid,RESCHNO);
	sptr->semcnt = count;
	resched();
	restore(ps);
	if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Sreset] = proctab[currpid].syscalltime[Sreset] + (ctr1000 - starttime);
	}
	return(OK);
}
