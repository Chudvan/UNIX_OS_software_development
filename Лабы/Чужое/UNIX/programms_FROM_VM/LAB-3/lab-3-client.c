#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <pthread.h>
#include <string.h>

#define SH_MEM_FILE_NAME "lab-3-server.c"
#define SH_MEM_SIZE 1120
#define PROJ_ID 12
#define BUFF_SIZE 1024

int main(int argc, char *argv[]) {
	int has_new = 0;
	int message_size = 0;
	int message_number = -1;
	int message_number_old = -1;
	char *sh_mem;
	int shmid;
	key_t key;
//	generating key
//	printf(">>>key = %d\n", key);
	if((key = ftok(SH_MEM_FILE_NAME, 12)) < 0) {
//		printf(">>>key = %d\n",key);
		printf(">>>FTOK_ERROR!\n");
		return 1;
	}
//	creating shared memory
	if((shmid = shmget(key, SH_MEM_SIZE*sizeof(char), 0666)) < 0) {
//		printf(">>>shmid = %d\n", shmid);
		printf(">>>SHMGET_ERROR!\n");
		return 1;
	}
//	getting pointer to shared memory
	if((sh_mem = (int*)shmat(shmid, NULL, 0)) == (int*)(-1)) {
//		printf(">>>sh_mem = %d\n", sh_mem);
		printf(">>>SHMAT_ERROR!\n");
		return 1;
	}
	for(;;) {
		pthread_mutex_lock((pthread_mutex_t*)sh_mem);
		memcpy(&message_number, sh_mem+92, sizeof(int));
		while(message_number == sh_mem[92])
			pthread_cond_wait((pthread_cond_t*)(sh_mem+sizeof(pthread_mutex_t)), (pthread_mutex_t*)sh_mem);
		memcpy(&message_number, 
			sh_mem+sizeof(pthread_mutex_t)+sizeof(pthread_cond_t)+sizeof(int), 
			sizeof(int));
		if(message_number == -1) {
			printf(">>>SERVER_DISCONNECTED!\n");
			printf(">>>MESSAGE_NUMBER: -1\n");
			
		} else {
			printf(">>>GETTING_MESSAGE:\n");
			printf(">>>MESSAGE_NUMBER: %d\n", message_number);
			memcpy(&message_size, 
				sh_mem+sizeof(pthread_mutex_t)+sizeof(pthread_cond_t), 
				sizeof(int));
			printf(">>>MESSAGE_SIZE = %d\n", message_size);
			for(int i=0;i<message_size;i++) {
				printf("%c", (sh_mem+96)[i]);
			}
		}
		pthread_mutex_unlock((pthread_mutex_t*)sh_mem);
	}
	return 0;
}

