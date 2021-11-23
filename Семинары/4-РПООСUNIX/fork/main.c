#include <unistd.h>
#include "stdio.h"

void main(){
	pid_t ret;
	switch(ret=fork())
	{
	  case -1: printf("Ошибка\n"); break; /*при вызове fork() возникла ошибка*/
	  case 0 : printf("Я потомок\n"); break; /*это код потомка*/
	  default : printf("Я родитель, мой ребёнок - %d\n", ret);/*это код родительского процесса*/
	}
}
