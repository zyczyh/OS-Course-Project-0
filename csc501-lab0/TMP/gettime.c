/* gettime.c - gettime */

#include <conf.h>
#include <kernel.h>
#include <date.h>
#include <proc.h>

extern int getutim(unsigned long *);

/*------------------------------------------------------------------------
 *  gettime  -  get local time in seconds past Jan 1, 1970
 *------------------------------------------------------------------------
 */
SYSCALL	gettime(long *timvar)
{
    /* long	now; */

	/* FIXME -- no getutim */
	unsigned long starttime;
	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Gettime] = proctab[currpid].syscallcounter[Gettime] + 1;
		starttime = ctr1000;
		proctab[currpid].syscalltime[Gettime] = proctab[currpid].syscalltime[Gettime] + (ctr1000 - starttime);
	}
    return OK;
}
