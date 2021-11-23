#define _POSIX_SOURCE 
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#undef _POSIX_SOURCE 
#include <stdio.h>

int main(int argc, char *argv[]) {
	int fd = creat("temp.txt", S_IRUSR | S_IWUSR);
	//command[0]='\0';
	/*if(c!=0) {
		printf("SETENV_ERROR!");
		return 1;
	}*/
	//int fd = atoi();
	char *desc;
	//int fd = 0;
	pid_t pid;
	switch(pid = fork()) {
		case -1:
			printf("fork ERROR!");
			break;
		case 0:
			desc = getenv("DESC");
			fd = atoi(desc);
			FILE *f = fdopen(fd, "a");
			printf("%s", f);
			break;
		default:
			printf("def");
	}

	return 0;
}

