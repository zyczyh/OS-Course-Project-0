/* getpid.c - getpid */

#include <conf.h>
#include <kernel.h>
#include <proc.h>

/*------------------------------------------------------------------------
 * getpid  --  get the process id of currently executing process
 *------------------------------------------------------------------------
 */
SYSCALL getpid()
{
	unsigned long starttime;
	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Getpid] = proctab[currpid].syscallcounter[Getpid] + 1;
		starttime = ctr1000;
		proctab[currpid].syscalltime[Getpid] = proctab[currpid].syscalltime[Getpid] + (ctr1000 - starttime);
	}
	return(currpid);
}
