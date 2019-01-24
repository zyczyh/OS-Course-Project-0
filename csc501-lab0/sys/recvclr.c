/* recvclr.c - recvclr */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 *  recvclr  --  clear messages, returning waiting message (if any)
 *------------------------------------------------------------------------
 */
SYSCALL	recvclr()
{
	STATWORD ps;    
	WORD	msg;
	unsigned long starttime;

	if(traceflag == 1)
	{
		proctab[currpid].syscallcounter[Recvclr] = proctab[currpid].syscallcounter[Recvclr] + 1;
		starttime = ctr1000;
	}
	disable(ps);
	if (proctab[currpid].phasmsg) {
		proctab[currpid].phasmsg = 0;
		msg = proctab[currpid].pmsg;
	} else
		msg = OK;
	restore(ps);
	if(traceflag == 1)
	{
		proctab[currpid].syscalltime[Recvclr] = proctab[currpid].syscalltime[Recvclr] + (ctr1000 - starttime);
	}
	return(msg);
}
