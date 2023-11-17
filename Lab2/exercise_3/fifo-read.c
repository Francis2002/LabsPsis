#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fifo_read_(int fd,char* str){

	int n;
    printf("entered read\n");
    n = read(fd, str, 100);
    printf("information read: %s; number of chars: %d\n",str, n);
    if(n<=0){
        perror("read ");
        exit(-1);
    }
    return 0;
}
