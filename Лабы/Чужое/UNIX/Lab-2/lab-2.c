#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int carg;
	char *filename;
	while((carg=getopt(argc, argv,"f:h"))!=-1) {
		switch(carg) {
			case 'f':
				filename = optarg;
				break;
			case 'h':
				printf("USAGE:\n\t-h help\n\t-f filename\n");
				break;
			case '?':
				printf("WRONG ARG!");
				break;
		}
	}
	int fd = creat(filename, S_IRWXG);
	printf("PARENT: fd=%d\n",fd);
	pid_t pid;
	switch(pid = fork()) {
		case -1:
			printf("fork ERROR!");
			break;
		case 0:
			printf("CHILD_PROCESS CASE\n");
			execl("lab-2-2.exe", fd, NULL);
			break;
		default:
			printf("DEFAULT CASEn\n");
	}

	return 0;
}
