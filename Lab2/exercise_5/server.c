#include "funcs.h"
#include <string.h>

#include <dlfcn.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "data_struct.h"

int main(){

    int fd1,fd2;
    char library_name[100];
    while((fd1 = open("/tmp/fifo_teste", O_RDONLY)) == -1){
      if(mkfifo("/tmp/fifo_teste", 0666)!=0){
		    printf("problem creating the fifo\n");
		    exit(-1);
      }else{
	      printf("fifo created\n");
      }
    }
    while((fd2 = open("/tmp/fifo_teste2", O_WRONLY))== -1){
      if(mkfifo("/tmp/fifo_teste2", 0666)!=0){
	        printf("problem creating the fifo\n");
	        exit(-1);
      }else{
          printf("fifo2 created\n");
      }
    }

    message_type *message  = NULL;
    message = (message_type *)malloc(sizeof(message_type));
    strcpy(message->f_name,"hello");
    message->funct_type = -1;
    message->arg = -1;
    while(1){

        printf("waiting for message\n");
        read(fd1,message, sizeof(message_type));
        printf("message received\n");
        printf("function name: %s\n",message->f_name);
        printf("function type: %d\n",message->funct_type);
        printf("argument: %d\n",message->arg);

        char *str = message->f_name;

        if(strncmp(str, "f1",2)==0 || strncmp(str, "f2",2)==0 || strncmp(str, "f3",2)==0){
            strcpy(library_name,"./funcs_mac.so");
            void *handle = dlopen(library_name,RTLD_LAZY);
            if(!handle)
            {
                fprintf(stderr,"%s\n",dlerror());
                exit(1);
            }
            int(*f1)()=NULL;
            int(*f2)()=NULL;

            int(*f3)(int)=NULL;

            f1 = dlsym(handle,"f1");
            if (!f1) {
                fprintf(stderr, "Error loading f1: %s\n", dlerror());
                exit(1);
            }
            f2 = dlsym(handle,"f2");
            if (!f2) {
                fprintf(stderr, "Error loading f1 or f2: %s\n", dlerror());
                exit(1);
            }
            f3 = dlsym(handle,"f3");
            if (!f3) {
                fprintf(stderr, "Error loading f3: %s\n", dlerror());
                exit(1);
            }
            printf("function found\n");
            printf("function name: %s\n",str);
            if(strncmp(str, "f1",2)==0)
            {
                printf("f1\n");
                int a = f1();
                write(fd2,&a, sizeof(int));
            }
            else if(strncmp(str, "f2",2)==0)
            {
                printf("f2\n");
                int b = f2();
                write(fd2,&b, sizeof(int));
            }
            else if(strncmp(str, "f3",2)==0)
            {
                printf("f3\n");
                printf("argument: %d\n",message->arg);
                int argument = message->arg;
                printf("computing f3\n");
                int c = f3(argument);
                printf("f3 computed\n");
                write(fd2,&c, sizeof(int));
            }
        }    
        else
        {
            printf("Function not found\n");
            int useless = -1;
            printf("fifo_writing_ useless: %d\n",useless);
            write(fd2, &useless, sizeof(int));
        }
    }
}
