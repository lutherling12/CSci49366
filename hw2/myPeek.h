/******************************************************************************
Title:    Unix Tools - Assignment 2 - myWrites
Author:   Luther Ling

Build:    make myWrites.o
Usage:    with hw2.c

Description:

These functions read from an input file and lseek back to prior locations; 
they do NOT displace the offset when called. 

getALine stores in string container the next line from the offset of open file 
with file descriptor, fd, or stops after getting n number of characters, then
moves back however many bytes were read. Returns nothing.

countLineByte determines how many bytes are in the next line to be retrieved
from the offset of open file with file descriptor, fd.
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