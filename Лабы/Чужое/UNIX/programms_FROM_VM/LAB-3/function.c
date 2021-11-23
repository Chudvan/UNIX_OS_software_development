#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void create_message(char *buff, int buffer_size, int *msg_size) {
	memset(buff, 0, buffer_size*sizeof(char));
	//printf(">%d\n", buffer_size);
	for(int i=0;i<buffer_size;i++) {
		msg_size[0]++;
		//printf("CR_M>>>msg_size=%d\n", msg_size[0]);
		if((buff[i]=getchar())=='\n')
			break;
	}
}
