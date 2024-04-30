#include <stdio.h>
#include <stm32f4xx.h>
#include <string.h> 
void your_strcpy(const char *src , char *dst ,int val);
void reverse_str(const char *src , char *dst ,int val);

int main (void)
{
    char a[] = "Hello world! My name is Soham";
    //char b[40];
		//char c[40];
		fprintf("%d", strlen(a));
	  // int val = strlen(a);
  //  reverse_str(a, b, val-1);
	  //your_strcpy(a,c,val);
    // printf("%s",b);
		// printf("%s",c);
	
}

void reverse_str(const char *src , char *dst ,int val){
        __asm volatile(
					  "initia: \n"
				    "       mov r1 ,#0 \n"
				    "       b fun1 \n"
					  "fun1: \n"
            "     ldrb r0 , [%0 , %2] \n"
				    "     strb r0 , [%1 , r1] \n"				    
						"     add r1,r1,#1 \n"
				    "     cbz %2,complete \n"
						"     add %2,%2,#-1 \n"
				    "     b fun1 \n"
				
            "complete:  \n"
            :
            :"r"(src), "r"(dst) , "r"(val)
            :"r0","memory","r1","r2","r3"
        );
 }

/*
void your_strcpy(const char *src , char *dst ,int val){
        __asm volatile(
					  "initia: \n"
				    "       mov r1 ,#0 \n"
				    "       mov r2 ,%2 \n"
				    "       b fun1 \n"
				
					  "fun1: \n"
            "     ldrb r0 , [%0 , r1] \n"
				    "     cmp r0 , #97 \n"
				    "     bge c1 \n"
				    "     strb r0 , [%1 , r1] \n"
				    "     add r1,r1,#1 \n"
				    "     cmp r1,r2 \n"
				    "     beq complete \n"
				    "     b fun1 \n"
				
