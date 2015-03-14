#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define USERMASK
#define GROUPMASK
#define STICKYMASK
#define FILETYPEMASK


void printStars ();

int main (int argc, char ** argv)
{
	if (argc == 1) {
		open ("sampleFile", O_CREAT);
		return 0;
	}

	char sampleName[] = "sampleFile";
	int sampleBinary = 19;
	struct stat buf;

	stat (sampleName, &buf);

	printStars();

	printf ("*Name: %s \t |Binary Values: %o\n", sampleName, buf.st_mode);
	printf ("*Name: %s \t |Binary Values: %o\n", sampleName, (buf.st_mode >> 6));
	printf ("*Name: %s \t |Binary Values: %o\n", sampleName, buf.st_mode);

	printf ("*\tSet User ID: %i\n", (buf.st_mode & 0x8000) >> 15);
	printf ("*\tSet Group ID: %i\n", (buf.st_mode & 0x4000) >> 14);
	printf ("*\tSticky Bit: %i\n", (buf.st_mode & 0x2000) >> 13);
	printf ("*\tFile Type: %i\n", (buf.st_mode & 0x1E00) >> 12);
	printf ("*\tAccess Permission: %i\n", (buf.st_mode & 0x1E00) >> 9);

	printStars();

	return 0;
}

void printStars () {

	for (int i = 1; i <= 60; i++) {
		printf ("*");
	}
	printf("\n");

}

