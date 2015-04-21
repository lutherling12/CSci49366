#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>

int main (int argc, char ** argv) {
  int counter = 0;
  struct passwd * temp;
   
  temp = getpwuid (counter);

  printf ("%s\n", temp->pw_name); 

  return 0;
}
