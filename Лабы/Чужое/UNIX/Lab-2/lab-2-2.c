#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	printf("CHILD CODE EXECUTION\n");
	char *ch = argv[1];
	if(ch==NULL) {
		printf("COMMAND_LINE_ARGUMENT_ERROR!");
		return 1;
	}
	int fd = atoi(ch);
	printf("CHILD: fd=%d\n",fd);
	FILE *f = fdopen(fd, "a");
	fprintf(f, "test str value.\n");
	fclose(f);
	return 0;
}

