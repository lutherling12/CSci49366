/******************************************************************************
Performs writes to a file.
Offset for open file changes
******************************************************************************/

#ifndef MY_WRITES
#define MY_WRITES

#include "myPeek.h"
#include "myGet.h"

#define BUFFER_SIZE 512

void writeStr (int fd, char str []);
bool shiftWrite (int fd, off_t shiftBytes);

#endif