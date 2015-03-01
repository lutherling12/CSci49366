#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>

#include <string.h>

void removeSpaces (char * str);

int main (int argc, char * argv [])
{
	char title[200];
	char author [200];

	char sample[] = "Remove my spaces";	

	printf ("%i\n", (int)strlen(sample));
	removeSpaces(sample);
	printf ("\"%s\"\n", sample);

	//int fd = open ("books.txt", O_RDWR);

	/*
	if (fd != -1) {
		printf ("%s %i\n", "books.txt fd is: ", fd);
		return 0;
	}
	else {
		printf ("%s\n", "books.txt file not found.");
		return 1;
	}
	*/
}

void removeSpaces (char str[]) {
	int length = strlen (str);

	for (int i = 0; i < length-1; i++) {
		if (str[i] == ' ') {
			printf("%c", str[i]);
			str[i] = '-';
		}
	}
}