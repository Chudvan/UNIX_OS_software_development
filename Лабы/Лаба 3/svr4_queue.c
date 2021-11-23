#include "svr4_queue.h"

int create(key_t key){
	int msqid;
	msqid = msgget(key, IPC_CREAT | 0666);
	
	if(msqid == -1){
		printf("create errror: %s\n", strerror(errno));
	}
	
	return msqid;
}

int delete_(int msqid){
	if(msgctl(msqid, IPC_RMID, NULL) == -1){
		printf("delete errror: %s\n", strerror(errno));
		return 1;
	}
	return 0;
}

int write(int msqid, long type, const char* text){
	mq_message msg;
	msg.type = type;
	strcpy(msg.text, text);
	
	if(msgsnd(msqid, (void *)&msg, sizeof(msg), IPC_NOWAIT) == -1){
		printf("write errror: %s\n", strerror(errno));
		return 1;
	}
	return 0;
}

mq_message* read(int msqid, long type){
	
	mq_message* msg = (mq_message*)malloc(sizeof(mq_message));
	if(msgrcv(msqid, (void *)msg, MSGSIZE, type, IPC_NOWAIT | MSG_NOERROR) == -1){
		printf("read errror: %s\n", strerror(errno));
		return NULL;
	}
	return msg;
}

