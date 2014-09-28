//Noah Smith
//Ece264
//9/26/2014

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * * argv)
{
  int ind;
  //Check for help
  for(ind = 1; ind < argc; ind++){
    if(strcmp(argv[ind], "--help") == 0){
      printf("Usage: grep-lite [OPTION]... PATTERN\n"
             "Search for PATTERN in standard input. PATTERN is a\n"
             "string. grep-lite will search standard input line by\n"
             "line, and (by default) print out those lines which\n"
             "contain pattern as a substring.\n\n"
             "  -v, --invert-match     print non-matching lines\n"
             "  -n, --line-number      print line numbers with output\n"
             "  -q, --quiet            suppress all output\n\n"
             "Exit status is 0 if any line is selected, 1 otherwise;\n"
             "if any error occurs, then the exit status is 2.");
      return EXIT_SUCCESS;
    }
  }
  //Check middle terms for anything that isn't -v,-n,-q (or print error, return 2)
  for(ind = 1; ind < (argc - 1); ind++){
    if((strcmp(argv[ind], "-v") != 0) && (strcmp(argv[ind], "-n") != 0) && (strcmp(argv[ind], "-q") != 0)){
      fprintf(stderr, "One or more terms not '-v', '-n', or '-q'\n");
      return 2;
    }
  }
  //Check last term for -, if so print error and return 2
  //fgets every line up to 2000 characters
  //strstr every line
  //keep track of which lines match, may be inverted
  //First line number is 1, print number if specified
  //Print every matching line
  //If quiet, only return correct exit code
  //Return 0 if at least one matching line, 1 otherwise

}
