/* suspend.c - suspend */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 *  suspend  --  suspend a process, placing it in hibernation
 *------------------------------------------------------------------------
 */
SYSCALL	suspend(int pid)
{
	STATWORD ps;    
	struct	pentry	*pptr;		/* pointer to proc. tab. entry	*/
	int	prio;			/* priority returned		*/
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Suspend] = proctab[currpid].syscallcounter[Suspend] + 1;
		starttime = ctr1000;
	}
	disable(ps);
	if (isbadpid(pid) || pid==NULLPROC ||
	 ((pptr= &proctab[pid])->pstate!=PRCURR && pptr->pstate!=PRREADY)) {
		restore(ps);
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Suspend] = proctab[currpid].syscalltime[Suspend] + (ctr1000 - starttime);
		}
		return(SYSERR);
	}
	if (pptr->pstate == PRREADY) {
		pptr->pstate = PRSUSP;
		dequeue(pid);
	}
	else {
		pptr->pstate = PRSUSP;
		resched();
	}
	prio = pptr->pprio;
	restore(ps);
	if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Suspend] = proctab[currpid].syscalltime[Suspend] + (ctr1000 - starttime);
	}
	return(prio);
}
