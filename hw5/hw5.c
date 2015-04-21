#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

void printHeader ();

int main (int argc, char ** argv) {
  struct passwd * temp;
  
  for (int i=0; i <= INT_MAX; i++) {
    if (i % 20 == 0) {
      void printHeader ();
    }

    temp = getpwuid (i);

    if (temp != NULL) {
      printf ("%*i |", +10, i);
      printf ("%*s\n", -20, temp->pw_name);
    }
    else {
      printf ("%*i\n", +10, i);
      printf ("%*s\n", -20, "Unassigned");
    }
    sleep (1); 
  }

  return 0;
}

void printHeader () {

  for (int i = 1; i <= 80; i++) {
    printf ("*");
  }

  printf ("%*s", +10, "ID Number");
  printf ("%*s", -20, "Username");

  for (int i = 1; i <= 80; i++) {
    printf ("*");
  }  
}