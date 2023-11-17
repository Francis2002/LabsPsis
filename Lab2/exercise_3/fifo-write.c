#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int fifo_write_(int fd , int* arg){
    
	char str[100];
    if (arg != NULL )
    {
        sprintf(str, "%d", *arg);
        write(fd, str, 100);   
        return 0;
    }
    printf("write a function name:");
    fgets(str, 100, stdin);
    printf("writing to fifo: %s\n", str);
    write(fd, str, 100);
    return 0;

}
