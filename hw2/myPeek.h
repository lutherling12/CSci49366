/******************************************************************************
These functions read from an input file and lseek back to prior locations; 
they do not displace the offset when called. 

Or, they perform "peeks" into the file.
******************************************************************************/

#ifndef MY_PEEK
#define MY_PEEK

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//For off_t
#include <sys/types.h>
//For lseek
#include <unistd.h>

#include "myGet.h"

char peekChar (int fd);
void peekLine (int fd, char container [], int n);
off_t countLineByte (int fd);

#endif