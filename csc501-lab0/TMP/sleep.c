/* sleep.c - sleep */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * sleep  --  delay the calling process n seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep(int n)
{
	STATWORD ps;
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Sleep] = proctab[currpid].syscallcounter[Sleep] + 1;
		starttime = ctr1000;
	}    
	if (n<0 || clkruns==0)
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Sleep] = proctab[currpid].syscalltime[Sleep] + (ctr1000 - starttime);
		}
		return(SYSERR);
	if (n == 0) {
	        disable(ps);
		resched();
		restore(ps);
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Sleep] = proctab[currpid].syscalltime[Sleep] + (ctr1000 - starttime);
		}
		return(OK);
	}
	while (n >= 1000) {
		sleep10(10000);
		n -= 1000;
	}
	if (n > 0)
		sleep10(10*n);
	if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Sleep] = proctab[currpid].syscalltime[Sleep] + (ctr1000 - starttime);
	}
	return(OK);
}
