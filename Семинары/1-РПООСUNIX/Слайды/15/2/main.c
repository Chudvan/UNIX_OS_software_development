// C program to demonstrate working of 
// __attribute__((constructor)) and 
// __attribute__((destructor)) 
#include<stdio.h> 
  
// Assigning functions to be executed before and 
// after main() 
void __attribute__((constructor)) calledFirst(); 
void __attribute__((destructor)) calledLast(); 
  
void main() 
{ 
    printf("\nI am in main"); 
} 
  
// This function is assigned to execute before 
// main using __attribute__((constructor)) 
void calledFirst() 
{ 
    printf("\nI am called first"); 
} 
  
// This function is assigned to execute after 
// main using __attribute__((destructor)) 
void calledLast() 
{ 
    printf("\nI am called last"); 
} 

