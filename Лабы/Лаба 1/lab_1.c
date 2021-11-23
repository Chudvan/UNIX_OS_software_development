#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	struct stat file_info;
	if (stat(argv[1], &file_info) == -1){
		printf("Cannot open %s file.\n", argv[1]);
		exit(1);
	}
	if (file_info.st_nlink >= atoi(argv[2])) {
		unlink(argv[1]);
		printf("File %s deleted.\n", argv[1]);
	}
	else{
		printf("File %s still exists.\n", argv[1]);
	}
	return 0;
}
