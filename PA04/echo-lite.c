//Noah Smith
//Ece 264
//9/28/2014

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * * argv)
{
  int ind;

  for(ind = 0; ind < argc; ind++) {
    printf("%s\n",argv[ind]);
  }

  return EXIT_SUCCESS;
}
