/* wait.c - wait */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * wait  --  make current process wait on a semaphore
 *------------------------------------------------------------------------
 */
SYSCALL	wait(int sem)
{
	STATWORD ps;    
	struct	sentry	*sptr;
	struct	pentry	*pptr;
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Wait] = proctab[currpid].syscallcounter[Wait] + 1;
		starttime = ctr1000;
	}
	disable(ps);
	if (isbadsem(sem) || (sptr= &semaph[sem])->sstate==SFREE) {
		restore(ps);
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Wait] = proctab[currpid].syscalltime[Wait] + (ctr1000 - starttime);
		}
		return(SYSERR);
	}
	
	if (--(sptr->semcnt) < 0) {
		(pptr = &proctab[currpid])->pstate = PRWAIT;
		pptr->psem = sem;
		enqueue(currpid,sptr->sqtail);
		pptr->pwaitret = OK;
		resched();
		restore(ps);
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Wait] = proctab[currpid].syscalltime[Wait] + (ctr1000 - starttime);
		}
		return pptr->pwaitret;
	}
	restore(ps);
	if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Wait] = proctab[currpid].syscalltime[Wait] + (ctr1000 - starttime);
	}
	return(OK);
}
