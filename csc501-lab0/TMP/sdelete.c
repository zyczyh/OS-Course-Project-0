/* sdelete.c - sdelete */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * sdelete  --  delete a semaphore by releasing its table entry
 *------------------------------------------------------------------------
 */
SYSCALL sdelete(int sem)
{
	STATWORD ps;    
	int	pid;
	struct	sentry	*sptr;
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Sdelete] = proctab[currpid].syscallcounter[Sdelete] + 1;
		starttime = ctr1000;
	}
	disable(ps);
	if (isbadsem(sem) || semaph[sem].sstate==SFREE) {
		restore(ps);
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Sdelete] = proctab[currpid].syscalltime[Sdelete] + (ctr1000 - starttime);
		}
		return(SYSERR);
	}
	sptr = &semaph[sem];
	sptr->sstate = SFREE;
	if (nonempty(sptr->sqhead)) {
		while( (pid=getfirst(sptr->sqhead)) != EMPTY)
		  {
		    proctab[pid].pwaitret = DELETED;
		    ready(pid,RESCHNO);
		  }
		resched();
	}
	restore(ps);
	if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Sdelete] = proctab[currpid].syscalltime[Sdelete] + (ctr1000 - starttime);
	}
	return(OK);
}
