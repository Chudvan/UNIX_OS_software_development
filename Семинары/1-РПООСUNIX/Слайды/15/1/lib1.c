#include <stdlib.h>

char *test;

char *ret_test(){
	return test;
};

void _init(){
	test=(char *)malloc(6);
	if (test!=NULL){
		*(test+0)='d';
		*(test+1)='r';
		*(test+2)='o';
		*(test+3)='n';
		*(test+4)='!';
		*(test+5)=0;
	};
	printf("_init() executed...\n");
};

void _fini(){
	if (test!=NULL) free(test);	
	printf("_fini() executed...\n");
};
