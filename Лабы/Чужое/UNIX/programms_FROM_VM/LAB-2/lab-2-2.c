#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]) {
	printf("CHILD CODE EXECUTION\n");
	char *ch = argv[1];
	if(ch==NULL) {
		printf("COMMAND_LINE_ARGUMENT_ERROR!");
		return 1;
	}
	int fd = atoi(ch);
	printf("CHILD: fd=%d\n",fd);
	char buff[] = "1234567890";
	int size = strlen(buff);
	if(write(fd, buff, size)!=size)
		printf("WRITE_ERROR!\n");
	close(fd);
	return 0;
}

