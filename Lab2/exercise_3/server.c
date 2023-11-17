#include "fifo.h"
#include "funcs.h"
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

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

    char *str  = NULL;
    str = (char *)malloc(100 * sizeof(char));
    while(1){

        fifo_read_(fd1,str);
        if(strncmp(str, "f1",2)==0 || strncmp(str, "f2",2)==0){
            strcpy(library_name,"./funcs_mac.so");
            void *handle = dlopen(library_name,RTLD_LAZY);
            if(!handle)
            {
                fprintf(stderr,"%s\n",dlerror());
                exit(1);
            }
            int(*f1)()=NULL;
            int(*f2)()=NULL;

            f1 = dlsym(handle,"f1");
            f2 = dlsym(handle,"f2");
            if(strncmp(str, "f1",2)==0)
            {
                int  a = f1();
                fifo_write_(fd2,&a);
            }
            else
            {
                int b = f2();
                fifo_write_(fd2,&b);
            }
        }
     
        else
        {
            printf("Function not found\n");
            int useless = -1;
            printf("fifo_writing_ useless: %d\n",useless);
            fifo_write_(fd2, &useless);
        }
    }
}
