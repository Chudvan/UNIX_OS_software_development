#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
	pid_t pid;
	switch(pid = fork()) {
		case -1:
			printf("ERROR!\n");
			break;
		case 0:
			execl("example.exe", "example.exe", NULL);
			break;
		default:
			printf("PARENT_CODE\n");
			break;
	}
	return 0;
}

