/******************************************************************************
Title:    Unix Tools - Assignment 3.1 - Assignment Name
Author:   Luther Ling

Build:    make hw3.1
Usage:    ./hw3.1.out fileInput

Description:
If the program is run with at least one argument, it checks the present
working directory for files whose names are fileInput, then tries to access 
them. If the user cannot access the file (read and/or write), it tries to 
change the owner of the file to the current user for access.

If the program is run without any arguments, it generates a file named
"notMine" for test purposes. 
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <string.h>

#define FLAGS (S_IRUSR | S_IWUSR | S_IRGRP | IWGRP | S_IROTH | S_IWOTH)

#define MYUSER 1000
#define MYGROUP 1000

int main (int argc, char ** argv)
{
	int fd = open ("notMine", O_CREAT);

	uid_t user = MYUSER;
	gid_t group = MYGROUP;

	if (argc == 1) {
		if (fd != -1) {
			close (fd);
		}
	}

	else {
		for (int i = 0; i < argc; i++) {
			if (access (argv[i], F_OK) == -1) {
				printf ("%s cannot be found.\n", argv[i]);
			}
			else {
				if (access (argv[i], R_OK) == -1) {
					printf ("%s cannot be read.", argv[i]);
					chown (argv[i], user, group);
					printf ("User %i in group %i, now owns %s.\n", user, group, argv[i]);
				}
				if (access (argv[i], W_OK) == -1) {
					printf ("%s cannot be written.", argv[i]);
					chown (argv[i], user, group);
					printf ("User %i in group %i, now owns %s.\n", user, group, argv[i]);
				}
			}
		}
	}

	return 0;
}