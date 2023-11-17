#include "funcs.h"
#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "data_struct.h"

int main(){
    int fd1,fd2;

	while((fd1 = open("/tmp/fifo_teste", O_WRONLY))== -1){
	  if(mkfifo("/tmp/fifo_teste", 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
	  }else{
		  printf("fifo created\n");
	  }
	}
    while((fd2 = open("/tmp/fifo_teste2", O_RDONLY))== -1){
      if(mkfifo("/tmp/fifo_teste2", 0666)!=0){
		    printf("problem creating the fifo\n");
		    exit(-1);
      }else{
	      printf("fifo2 created\n");
      }
    }

    int* output = (int *)malloc(sizeof(int));
    char* buff = (char *)malloc(100 * sizeof(char));

    char fun_name[50];
    int fun_arg;
    printf("entering loop\n");
    while(1){
      printf("Write a function name:");
      fgets(buff,100,stdin);
      printf("Read from stdin: %s\n",buff);

      // Using sscanf to split the input into two words
      sscanf(buff, "%s %d", fun_name, &fun_arg);

      printf("Word 1: %s\n", fun_name);
      printf("Word 2: %d\n", fun_arg);

      if(strncmp(fun_name, "f1",2)==0 || strncmp(fun_name, "f2",2)==0 || strncmp(fun_name, "f3",2)==0){
        message_type *message = (message_type *)malloc(sizeof(message_type));
        strcpy(message->f_name,fun_name);
        message->arg = fun_arg;
        if (strncmp(fun_name, "f3",2)==0)
        {
          message->funct_type = 1;
        }
        else{
          message->funct_type = 0;
        }

        printf("writing to fifo\n");
        printf("function name: %s\n",message->f_name);
        printf("function type: %d\n",message->funct_type);
        printf("argument: %d\n",message->arg);
        write(fd1, message, sizeof(message_type));
        read(fd2,output, 100);
        printf("output: %d\n",*output);
      }
      else{
        printf("function not found\n");
      }
    }
}
