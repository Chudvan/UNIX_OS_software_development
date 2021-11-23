#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int main(int argc, char **argv) {
	printf("SIZES_OF_VARS:\n");
	printf(">>>int = %ld\n>>>char = %ld\n>>>cond = %ld\n>>>mutex = %ld\n", sizeof(int), sizeof(char), sizeof(pthread_cond_t), sizeof(pthread_mutex_t));
	return 0;
}

