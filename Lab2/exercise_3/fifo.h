//write a .h file for the fifo-read.c and fifo-write.c file

#ifndef FIFO_READ_H
#define FIFO_READ_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int fifo_read_(int fd ,char* str);

int fifo_write_(int fd ,int* arg);

#endif
