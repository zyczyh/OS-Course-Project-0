/* unsleep.c - unsleep */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * unsleep  --  remove  process from the sleep queue prematurely
 *------------------------------------------------------------------------
 */
SYSCALL	unsleep(int pid)
{
	STATWORD ps;    
	struct	pentry	*pptr;
	struct	qent	*qptr;
	int	remain;
	int	next;
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Unsleep] = proctab[currpid].syscallcounter[Unsleep] + 1;
		starttime = ctr1000;
	}
    disable(ps);
	if (isbadpid(pid) ||
	    ( (pptr = &proctab[pid])->pstate != PRSLEEP &&
	     pptr->pstate != PRTRECV) ) {
		restore(ps);
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Unsleep] = proctab[currpid].syscalltime[Unsleep] + (ctr1000 - starttime);
		}
		return(SYSERR);
	}
	qptr = &q[pid];
	remain = qptr->qkey;
	if ( (next=qptr->qnext) < NPROC)
		q[next].qkey += remain;
	dequeue(pid);
	if ( (next=q[clockq].qnext) < NPROC)
		sltop = (int *) & q[next].qkey;
	else
		slnempty = FALSE;
        restore(ps);
    if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Unsleep] = proctab[currpid].syscalltime[Unsleep] + (ctr1000 - starttime);
	}
	return(OK);
}
