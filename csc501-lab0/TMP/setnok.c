/* setnok.c - setnok */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 *  setnok  -  set next-of-kin (notified at death) for a given process
 *------------------------------------------------------------------------
 */
SYSCALL	setnok(int nok, int pid)
{
	STATWORD ps;    
	struct	pentry	*pptr;
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Setnok] = proctab[currpid].syscallcounter[Setnok] + 1;
		starttime = ctr1000;
	}
	disable(ps);
	if (isbadpid(pid)) {
		restore(ps);
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Setnok] = proctab[currpid].syscalltime[Setnok] + (ctr1000 - starttime);
		}
		return(SYSERR);
	}
	pptr = &proctab[pid];
	pptr->pnxtkin = nok;
	restore(ps);
	if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Setnok] = proctab[currpid].syscalltime[Setnok] + (ctr1000 - starttime);
	}
	return(OK);
}
