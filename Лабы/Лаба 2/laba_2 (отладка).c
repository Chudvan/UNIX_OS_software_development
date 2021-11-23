#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void dialog(){
	printf("To stop the process, write the 's' symbol in the console.\n");
	printf("To continue the process, write the 'c' symbol in the console.\n");
	printf("To kill the process, write the 'k' symbol in the console.\n");
	printf("To exit from the programm, write the 'e' symbol in the console.\n");
}

int main(int argc, char *argv[]) {
	//printf("%s %ld", "str", sizeof("str")); 
	pid_t pid = fork();
	if (pid == -1){
		printf("Error with starting process.\n");
		exit(-1);
	}
	if (pid == 0){
		//printf("старт в дочернем\n");
		int len = 0;
		while (argv[2 + len] != NULL) len++;
		//printf("len == %d", len);
		char **args;
		int str_sizeof = sizeof(char *);
		if (len != 0){
			args = (char **)malloc((len + 2) * str_sizeof);
			//printf("Мы в if.\n"); 
			//memcpy(args, argv[2], str_sizeof * len);
			int i = 1;
			for(; i <= len + 1; i++){
				args[i] = argv[1 + i];
			}
		}
		else{
			args = (char **)malloc(2 * str_sizeof);
			//printf("Мы в else\n"); 
			args[1] = NULL;
		}
		args[0] = argv[0];
		int i = 0;
		//printf("Переданные аргументы\n");
		while (args[i] != NULL){
			printf("%s ", args[i]);
			i++;
		}
		//fflush(stdout);
		execv(argv[1], args);
	}
	else{
		//printf("висим в родительском\n");
		//int n = 128;
		char sym;
		dialog();
		while ((sym = getchar()) != 'e'){
			switch(sym){
			case '\n':
				continue;
			case 's':
				printf("SIGSTOP\n");
				kill(pid, SIGSTOP);
				break;
			case 'c':
				printf("SIGCONT\n");
				kill(pid, SIGCONT);
				break;
			case 'k':
				printf("SIGKILL\n");
				kill(pid, SIGKILL);
				break;
			default:
				printf("Unexpected symbol '%c'\n", sym);
				break;
			}
			dialog();
		}
		//fgets(fname, n, stdin);
	}
	return 0;
}
