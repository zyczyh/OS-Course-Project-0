/* resume.c - resume */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * resume  --  unsuspend a process, making it ready; return the priority
 *------------------------------------------------------------------------
 */
SYSCALL resume(int pid)
{
	STATWORD ps;    
	struct	pentry	*pptr;		/* pointer to proc. tab. entry	*/
	int	prio;			/* priority to return		*/
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Resume] = proctab[currpid].syscallcounter[Resume] + 1;
		starttime = ctr1000;
	}
	disable(ps);
	if (isbadpid(pid) || (pptr= &proctab[pid])->pstate!=PRSUSP) {
		restore(ps);
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Resume] = proctab[currpid].syscalltime[Resume] + (ctr1000 - starttime);
		}
		return(SYSERR);
	}
	prio = pptr->pprio;
	ready(pid, RESCHYES);
	restore(ps);
	if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Resume] = proctab[currpid].syscalltime[Resume] + (ctr1000 - starttime);
	}
	return(prio);
}
