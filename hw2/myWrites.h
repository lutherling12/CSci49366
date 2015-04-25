/******************************************************************************
Title:    Unix Tools - Assignment 2 - myWrites
Author:   Luther Ling

Build:    make myWrites.o
Usage:    with hw2.c

Description:

writeStr expects the file descriptor of an open file, and writes string str
into the open file. Returns nothing.

shiftWrite expects the file descriptor of an open file and shifts the contents 
of the file by shiftBytes number of bytes starting from the offset of the 
open file. It does so via tail recursion. Returns 1 if not EOF for the next 
iteration of recursion, else returns 0.
******************************************************************************/
#ifndef MY_WRITES
#define MY_WRITES

#include "myPeek.h"
#include "myGet.h"

#define BUFFER_SIZE 512

void writeStr (int fd, char str []);
bool shiftWrite (int fd, off_t shiftBytes);

#endif