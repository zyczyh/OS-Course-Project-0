/* screate.c - screate, newsem */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>

LOCAL int newsem();

/*------------------------------------------------------------------------
 * screate  --  create and initialize a semaphore, returning its id
 *------------------------------------------------------------------------
 */
SYSCALL screate(int count)
{
	STATWORD ps;    
	int	sem;
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Screate] = proctab[currpid].syscallcounter[Screate] + 1;
		starttime = ctr1000;
	}
	disable(ps);
	if ( count<0 || (sem=newsem())==SYSERR ) {
		restore(ps);
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Screate] = proctab[currpid].syscalltime[Screate] + (ctr1000 - starttime);
		}
		return(SYSERR);
	}
	semaph[sem].semcnt = count;
	/* sqhead and sqtail were initialized at system startup */
	restore(ps);
	if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Screate] = proctab[currpid].syscalltime[Screate] + (ctr1000 - starttime);
	}
	return(sem);
}

/*------------------------------------------------------------------------
 * newsem  --  allocate an unused semaphore and return its index
 *------------------------------------------------------------------------
 */
LOCAL int newsem()
{
	int	sem;
	int	i;

	for (i=0 ; i<NSEM ; i++) {
		sem=nextsem--;
		if (nextsem < 0)
			nextsem = NSEM-1;
		if (semaph[sem].sstate==SFREE) {
			semaph[sem].sstate = SUSED;
			return(sem);
		}
	}
	return(SYSERR);
}
