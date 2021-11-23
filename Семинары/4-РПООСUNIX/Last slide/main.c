#include <unistd.h>
#include <sys/types.h>
#include <sys/priocntl.h>
#include <sys/rtpriocntl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

static void trap_func( int sig ) {
	printf("\a");
}
int main() {
	pcinfo_t pcinfo;
	pcparms_t pcparms;
	struct sigaction sigact;
	struct itimerval itimerval;
	int count = 0;
	strcpy( pcinfo.pc_clname, "RT" );
	priocntl( 0, 0, PC_GETCID, &pcinfo );
	pcparms.pc_cid = pcinfo.pc_cid;
	((rtparms_t*)pcparms.pc_clparms)->rt_pri=((rtinfo_t*)pcinfo.pc_clinfo)->rt_maxpri;
	((rtparms_t*)pcparms.pc_clparms)->rt_tqsecs = RT_TQINF;
	priocntl( P_PID, P_MYID, PC_SETPARMS, &pcparms );
	memcntl( 0, 0, MC_LOCKAS, MCL_CURRENT | MCL_FUTURE, 0, 0 );
	sigact.sa_handler = trap_func;
	sigfillset( &sigact.sa_mask );
	sigact.sa_flags = 0;
	sigaction( SIGPROF, &sigact, 0 );
	itimerval.it_interval.tv_sec = 5; itimerval.it_interval.tv_usec = 0;
	itimerval.it_value.tv_sec = 0;
	itimerval.it_value.tv_usec = 500;
	setitimer( ITIMER_PROF, &itimerval, NULL );
	while( 1 ) { ++count; if ( count > 1000000000 ) count = 0; }
}
