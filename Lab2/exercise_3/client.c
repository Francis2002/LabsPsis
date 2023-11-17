#include "fifo.h"
#include "funcs.h"
#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
    char *str  = NULL;
    str = (char *)malloc(100 * sizeof(char));
    printf("entering loop\n");
    while(1){
        fifo_write_(fd1,NULL);
        fifo_read_(fd2,str);
    }
}
