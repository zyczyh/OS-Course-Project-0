/* recvtim.c - recvtim */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 *  recvtim  -  wait to receive a message or timeout and return result
 *------------------------------------------------------------------------
 */
SYSCALL	recvtim(int maxwait)
{
	STATWORD ps;    
	struct	pentry	*pptr;
	int	msg;
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Recvtim] = proctab[currpid].syscallcounter[Recvtim] + 1;
		starttime = ctr1000;
	}
	if (maxwait<0 || clkruns == 0)
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Recvtim] = proctab[currpid].syscalltime[Recvtim] + (ctr1000 - starttime);
		}
		return(SYSERR);
	disable(ps);
	pptr = &proctab[currpid];
	if ( !pptr->phasmsg ) {		/* if no message, wait		*/
	        insertd(currpid, clockq, maxwait*1000);
		slnempty = TRUE;
		sltop = (int *)&q[q[clockq].qnext].qkey;
	        pptr->pstate = PRTRECV;
		resched();
	}
	if ( pptr->phasmsg ) {
		msg = pptr->pmsg;	/* msg. arrived => retrieve it	*/
		pptr->phasmsg = FALSE;
	} else {			/* still no message => TIMEOUT	*/
		msg = TIMEOUT;
	}
	restore(ps);
	if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Recvtim] = proctab[currpid].syscalltime[Recvtim] + (ctr1000 - starttime);
	}
	return(msg);
}
