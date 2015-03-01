#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>

#include <string.h>

#define T_BUFFER_SIZE 256
#define A_BUFFER_SIZE 256

void replaceSpaces (char str[], char replacementChar = '_');

int main (int argc, char * argv [])
{
	char title[A_BUFFER_SIZE];
	char author [T_BUFFER_SIZE];

	int fd = open ("books.txt", O_RDWR);
	off_t offsetNow;

	int rowNum = 0;

	if (argc != 4) {
		printf ("%s\n", 
			"command line arguments are \"<lineNum> <title> <author>\".");
		return 1;
	}

	rowNum = atoi (argv[1]);

	if (rowNum < 1) {
		printf ("%s\n", "first argument invalid row number.");
		return 1;
	}

	if (fd == -1) {
		printf ("%s\n", "books.txt file not found in pwd.");
		return 1;
	}

	else {
		printf ("%s %i\n", "books.txt fd is: ", fd);

		strncpy (title, argv[2], T_BUFFER_SIZE);
		strncpy (author, argv[3], T_BUFFER_SIZE);

		replaceSpaces (title);
		replaceSpaces (author);

		printf ("%s %s\n", title, author);

		return 0;
	}
}

void replaceSpaces (char str[], char replacementChar) {
	int length = strlen (str);

	for (int i = 0; i < length-1; i++) {
		if (str[i] == ' ') {
			printf("%c", str[i]);
			str[i] = replacementChar;
		}
	}
}