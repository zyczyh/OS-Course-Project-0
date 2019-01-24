/* scount.c - scount */

#include <conf.h>
#include <kernel.h>
#include <sem.h>
#include <proc.h>

/*------------------------------------------------------------------------
 *  scount  --  return a semaphore count
 *------------------------------------------------------------------------
 */
SYSCALL scount(int sem)
{
	extern	struct	sentry	semaph[];
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Scount] = proctab[currpid].syscallcounter[Scount] + 1;
		starttime = ctr1000;
	}
	if (isbadsem(sem) || semaph[sem].sstate==SFREE)
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Scount] = proctab[currpid].syscalltime[Scount] + (ctr1000 - starttime);
		}
		return(SYSERR);
	if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Scount] = proctab[currpid].syscalltime[Scount] + (ctr1000 - starttime);
	}
	return(semaph[sem].semcnt);
}
