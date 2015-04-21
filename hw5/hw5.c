#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

int main (int argc, char ** argv) {
  struct passwd * temp;
  
  for (int i=0; i <= INT_MAX; i++) {
    temp = getpwuid (i);
    if (temp != NULL) {
      printf ("%s\n", temp->pw_name);
    }
    sleep (1); 
  }

  return 0;
}
