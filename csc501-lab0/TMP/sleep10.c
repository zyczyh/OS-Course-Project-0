/* sleep10.c - sleep10 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * sleep10  --  delay the caller for a time specified in tenths of seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep10(int n)
{
	STATWORD ps;
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Sleep10] = proctab[currpid].syscallcounter[Sleep10] + 1;
		starttime = ctr1000;
	}    
	if (n < 0  || clkruns==0)
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Sleep10] = proctab[currpid].syscalltime[Sleep10] + (ctr1000 - starttime);
		}
		return(SYSERR);
	disable(ps);
	if (n == 0) {		/* sleep10(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n*100);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
    restore(ps);
    if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Sleep10] = proctab[currpid].syscalltime[Sleep10] + (ctr1000 - starttime);
	}
	return(OK);
}
