#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

void printStars ();

int main (int argc, char ** argv)
{
	if (argc == 1) {
		int fd = open ("sampleFile", O_CREAT|O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
		int writ = 0xDEADBEEF;

		if (fd != -1) {
			char str [] = "My permission should be set to 777. Might be 775 due to umask.";
			writ = write (fd, &str, (int)strlen (str));
			//writ = access ("sampleFile", W_OK);
			close (fd);
			
			printf ("(%o) %s\n", writ, str);
			return 0;
		}

		else {
			printf ("Couldn't make sampleFile in pwd.\n");
			return 1;
		}
	}

	struct stat buf;
	
/* 	
	Quick refresher on bit shifting.
	
	char sampleName[] = "sampleFile";
	printf ("Name: %s \t |Values: %o\n", sampleName, buf.st_mode);
	printf ("Name: %s \t |Values: %o\n", sampleName, (buf.st_mode >> 6));
	printf ("Name: %s \t |Values: %o\n", sampleName, buf.st_mode);
*/
	for (int i = 1; i < argc; i++) {

		printStars();
		
		if (stat (argv[i], &buf) == -1) {
			printf ("File %s not in pwd.\n", argv[i]);
		}
		else {
			printf ("Name: \t%s\n\n", argv[i]);
			printf ("\tOctal Value: \t\t%o\n", buf.st_mode);
			printf ("\tSet User ID: \t\t%o\n", (buf.st_mode & 0x8000) >> 15);
			printf ("\tSet Group ID: \t\t%o\n", (buf.st_mode & 0x4000) >> 14);
			printf ("\tSticky Bit: \t\t%o\n", (buf.st_mode & 0x2000) >> 13);
			printf ("\tFile Type: \t\t%o\n", (buf.st_mode & 0x1E00) >> 9);
			printf ("\tAccess Permission: \t%o\n", (buf.st_mode & 0x01FF) >> 0);
		}
	}

	printStars();

	return 0;
}

void printStars () {

	for (int i = 1; i <= 60; i++) {
		printf ("*");
	}
	printf("\n");

}

