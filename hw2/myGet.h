/******************************************************************************
These functions read from an input file and leaves the offset where it is when
it is done; they alter and displace the offset when called. 

Or, they perform "gets" into the file.
******************************************************************************/

#ifndef MY_GET
#define MY_GET

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//For off_t
#include <sys/types.h>
//For lseek
#include <unistd.h>

char getChar (int fd);
void getLine (int fd, char container [], int n);
off_t getBytePos (int row, int fd);

#endif