/* setdev.c - setdev */

#include <conf.h>
#include <kernel.h>
#include <proc.h>

/*------------------------------------------------------------------------
 *  setdev  -  set the two device entries in the process table entry
 *------------------------------------------------------------------------
 */
SYSCALL	setdev(int pid, int dev1, int dev2)
{
	short	*nxtdev;
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Setdev] = proctab[currpid].syscallcounter[Setdev] + 1;
		starttime = ctr1000;
	}
	if (isbadpid(pid))
		if(traceflag == 1)
		{
			proctab[currpid].syscalltime[Setdev] = proctab[currpid].syscalltime[Setdev] + (ctr1000 - starttime);
		}
		return(SYSERR);
	nxtdev = (short *) proctab[pid].pdevs;
	*nxtdev++ = dev1;
	*nxtdev = dev2;
	if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Setdev] = proctab[currpid].syscalltime[Setdev] + (ctr1000 - starttime);
	}
	return(OK);
}
