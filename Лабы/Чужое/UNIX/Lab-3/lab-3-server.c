#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>

#define SH_MEM_SIZE 	512
#define SH_MEM_FILE_NAME "shared_mem.temp"
#define MODE_OPEN 	2
#define MODE_APPEND 	3
#define MODE_UNLINK	4

void usage() {
	printf("USAGE:\n\t!ONLY ONE OPTION AT THE SAME TIME!\n\t-h help\n\t-o open shared memory\n\t-a append data\n\t-u unlink\n");
}

int main(int argc, char *argv[]) {
	printf("SERVER IS WORKING...\n");
	int mode, carg, size=SH_MEM_SIZE;
	char *str;
	if(argc>3) {
		printf("CMD_LINE_ARGS_ERROR: wrong amount!\n");
		usage();
		return 1;
	}
	while((carg=getopt(argc, argv,"ho:a:"))!=-1){
		switch() {
			case 'h':
				usage();
				return 0;
			case 'o':
				mode = MODE_OPEN;
				shm_open(SH_MEM_FILE_NAME, O_RDWR | 0777);
				size = atoi(optarg);
				break;
			case 'a':
				mode = MODE_APPEND;
				str = optarg;
				break;
			case 'u':
				mode = UNLINK;
				break;
			case '?':
				printf("CMD_LINE_ARGS_ERROR: invalid option!\n");
				return 1;
		}
	}
	
	
}

