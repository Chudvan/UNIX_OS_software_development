#include <iostream>
#include <pthread.h>
#include <cstring>
#include <stdio.h>

#define FINISH() { 	std::cout << (int)pthread_self() << " exits\n"; \
			pthread_mutex_unlock(&mutex); pthread_exit(0); return 0;	}
			
pthread_mutex_t mutex;
pthread_cond_t cond;
int msglen, done;
char msgbuf[256];

void* writer(void* argp){
	do{
		pthread_mutex_lock(&mutex);
		while(!msglen){
			pthread_cond_wait(&cond, &mutex);
			if(done) FINISH();
		}
		std::cout << "*> " << msgbuf << std::endl;
		msglen = 0;
		pthread_mutex_unlock(&mutex);
	} while(1);
}

void* reader(void* argp){
	do{
		pthread_mutex_lock(&mutex);
		if(!msglen){
			if(!std::cin.getline(msgbuf, 256)) break;
			msglen = strlen(msgbuf) + 1;
			pthread_cond_signal(&cond);
		}
		pthread_mutex_unlock(&mutex);
	} while(1);
	
	FINISH();
}

main(){
	pthread_t wtid, rtid;
	pthread_mutex_init(&mutex, 0);
	pthread_cond_init(&cond, 0);
	if(pthread_create(&wtid, 0, writer, 0)) perror("create error\n");
	if(pthread_create(&rtid, 0, reader, 0)) perror("create error\n");
	if(!pthread_join(rtid, 0)){
		done = 1;
		pthread_cond_signal(&cond);
	}
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	pthread_exit(0);
	return 0;
}
