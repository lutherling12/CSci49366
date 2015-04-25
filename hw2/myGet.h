/******************************************************************************
Title:    Unix Tools - Assignment 2 - myGet
Author:   Luther Ling

Build:    make myGet.o
Usage:    with hw2.c

Description:

These functions read from an input file and leaves the offset where it is when
it is done; they alter and displace the offset when called. 

getChar takes the file descriptor of an open file, fd. Returns the 
next character from the offset. and the file descriptor

getALine stores in string container the next line from the offset of open file 
with file descriptor, fd, or stops after getting n number of characters.
Returns nothing.

getBytePos get the byte number of the '\n' after row (argument) number of rows
in open file with file descriptor fd.
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
void getALine (int fd, char container [], int n);
off_t getBytePos (int row, int fd);

#endif