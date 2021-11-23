// myfile.c
#include <stdio.h>
 
void main()
{
    #ifdef DEBUG   
       printf("Debug run \n%d\n", DEBUG);
    #else
       printf("Release run\n");
    #endif
}

