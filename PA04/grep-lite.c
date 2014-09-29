//Noah Smith
//Ece264
//9/26/2014

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * * argv)
{
  int ind, invert = FALSE, number = FALSE, quiet = FALSE;
  int lineCounted = 1;
  int lineNumber = 1;
  char str [2000];

  //Check for no input
  if(argc == 1){
    fprintf(stderr, "Likely no input was given\n");
    return 2;
  }

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
    if((strcmp(argv[ind], "-v") != 0) && (strcmp(argv[ind], "-n") != 0) && (strcmp(argv[ind], "-q") != 0) && (strcmp(argv[ind], "--invert-match") != 0) && (strcmp(argv[ind], "--line-number") != 0) && (strcmp(argv[ind], "--quiet") != 0)){
      fprintf(stderr, "One or more terms not '-v', '-n', or '-q'\n");
      return 2;
    }
    if((strcmp(argv[ind], "-v") == 0) || (strcmp(argv[ind], "--invert-match") == 0))
       invert = TRUE;
    if((strcmp(argv[ind], "-n") == 0) || (strcmp(argv[ind], "--line-number") == 0))
      number = TRUE;
    if((strcmp(argv[ind], "-q") == 0) || (strcmp(argv[ind], "--quiet") == 0))
      quiet = TRUE;
  }
  //The value of ind should be the last value of argv
  ind = argc - 1;
  //Check last term for -, if so print error and return 2
  if(argv[ind][0] == '-'){
    fprintf(stderr, "PATTERN starts with a '-'");
    return 2;
  }
  //Default, print every line that matches
  //Quiet, print nothing, return correct values
  //Invert, print nonmatching lines
  //Number, Print line numbers
  //fgets every line up to 2000 characters
  //strstr every line
  //First line number is 1
  //Return 0 if at least one matching line, 1 otherwise

  while(fgets(str, 2000, stdin) != NULL){
    //The value of ind should still be the last value of argv
    if(strstr(str, argv[ind]) != NULL){
      //found on this line
      if(invert != TRUE){
	//return value will be 0
	lineCounted = 0;
	if(quiet){
	  //Found a line, no reason to continue searching
	  return lineCounted;
	}
	else{
	  if(number)
	    printf("%d:", lineNumber);
	  printf("%s",str);
	}
      }
    }
    else{
      if(invert){
	//return value will be 0
	lineCounted = 0;
	if(quiet){
	  //Found a line, no reason to continue searching
	  return lineCounted;
	}
	else{
	  if(number)
	    printf("%d:", lineNumber);
	  printf("%s",str);
	}
      }
    }
    lineNumber++;
  }
  return lineCounted;
}
