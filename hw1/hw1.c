/******************************************************************************
Title:    Unix Tools - Assignment 1 - myNameIs
Author:   Luther Ling

Build:    make all
Usage:    ./a.out

Description:
The assignment covers writing to file through a file descriptor. It prompts the 
user for their name, and then writes their string to a newly created file called
"myNameIs" in present working directory via write(). The person's name must be
shorter than 4096 characters (null character included).
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#define BUFSIZE 4096

int main (int argc, char * argv [])
{
   char str[BUFSIZE];
   int length = 0;
   int newfd = 0;

   if (argc > 2) {
      printf ("Please use only first name. \n");
      exit (1);
   }

   if (argc == 1) {
      printf ("What is your name? \n");
      fgets (str, BUFSIZE, stdin);
      length = strlen (str);

      newfd = creat ("myNameIs", S_IRWXU);
      if (length <= BUFSIZE) {
        write (newfd, str, length);
      }
      else {
        printf ("Your name is too long. \n");
      }
   }
 
   if (argc == 2) {
      length = strlen (argv[1]);

      newfd = creat ("myNameIs", S_IRWXU);
      if (length <= BUFSIZE) {
         write (newfd, argv[1], length);
      }
      else {
         printf ("Your name is too long. \n");
      }
   }

   close (newfd);

   return 0;
}
