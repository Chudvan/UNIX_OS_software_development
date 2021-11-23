#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

const int MSGSIZE = 256;

typedef struct {
	long type;
	char text[1];
} mq_message;

int create(key_t key);
int delete_(int msqid);
int write(int msqid, long type, const char* text);
mq_message* read(int msqid, long type);

