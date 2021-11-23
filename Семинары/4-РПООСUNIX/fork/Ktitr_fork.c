#include <unistd.h>
#include "stdio.h"

void main(){
	pid_t p;
	switch ( p = fork() ) {
		case -1: ошибка...break;
		case 0: код дочернего процесса; break;
		default: printf(“PID дочернего = %d\n”, p );
	}
}
