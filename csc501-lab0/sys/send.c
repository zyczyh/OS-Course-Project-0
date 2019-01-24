/* send.c - send */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 *  send  --  send a message to another process
 *------------------------------------------------------------------------
 */
SYSCALL	send(int pid, WORD msg)
{
	STATWORD ps;    
	struct	pentry	*pptr;
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Send] = proctab[currpid].syscallcounter[Send] + 1;
		starttime = ctr1000;
	}
	disable(ps);
	if (isbadpid(pid) || ( (pptr= &proctab[pid])->pstate == PRFREE)
	   || pptr->phasmsg != 0) {
		restore(ps);
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Send] = proctab[currpid].syscalltime[Send] + (ctr1000 - starttime);
		}
		return(SYSERR);
	}
	pptr->pmsg = msg;
	pptr->phasmsg = TRUE;
	if (pptr->pstate == PRRECV)	/* if receiver waits, start it	*/
		ready(pid, RESCHYES);
	else if (pptr->pstate == PRTRECV) {
		unsleep(pid);
		ready(pid, RESCHYES);
	}
	restore(ps);
	if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Send] = proctab[currpid].syscalltime[Send] + (ctr1000 - starttime);
	}
	return(OK);
}
