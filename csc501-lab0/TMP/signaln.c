/* signaln.c - signaln */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 *  signaln -- signal a semaphore n times
 *------------------------------------------------------------------------
 */
SYSCALL signaln(int sem, int count)
{
	STATWORD ps;    
	struct	sentry	*sptr;
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Signaln] = proctab[currpid].syscallcounter[Signaln] + 1;
		starttime = ctr1000;
	}
	disable(ps);
	if (isbadsem(sem) || semaph[sem].sstate==SFREE || count<=0) {
		restore(ps);
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Signaln] = proctab[currpid].syscalltime[Signaln] + (ctr1000 - starttime);
		}
		return(SYSERR);
	}
	sptr = &semaph[sem];
	for (; count > 0  ; count--)
		if ((sptr->semcnt++) < 0)
			ready(getfirst(sptr->sqhead), RESCHNO);
	resched();
	restore(ps);
	if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Signaln] = proctab[currpid].syscalltime[Signaln] + (ctr1000 - starttime);
	}
	return(OK);
}
