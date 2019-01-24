/* sleep1000.c - sleep1000 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * sleep1000 --  delay the caller for a time specified in 1/100 of seconds
 *------------------------------------------------------------------------
 */
SYSCALL sleep1000(int n)
{
	STATWORD ps;    
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Sleep1000] = proctab[currpid].syscallcounter[Sleep1000] + 1;
		starttime = ctr1000;
	}
	if (n < 0  || clkruns==0)
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Sleep1000] = proctab[currpid].syscalltime[Sleep1000] + (ctr1000 - starttime);
		}
	    return(SYSERR);
	disable(ps);
	if (n == 0) {		/* sleep1000(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
    if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Sleep1000] = proctab[currpid].syscalltime[Sleep1000] + (ctr1000 - starttime);
	}
	return(OK);
}
