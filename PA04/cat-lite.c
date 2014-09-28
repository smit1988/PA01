//Noah Smith
//Ece264
//9/18/2014

//Code structure copied from Prof. Lu's example.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char * * argv)
{
  // We want some variables to store which "switches" were set
  int showHelp = FALSE;
  int badSwitch = FALSE;
  int standardIn = FALSE;

  FILE *fptr;

  // Test for '-', empty, nonexistent file, and help. Otherwise, it's a file
  if(argc == 1)
    //do something with standard input, then exit
  else {
    int ind = 1; // we always skip 0, which is the program path
    for( ; ind < argc; ++ind) {
      if(strcmp(argv[ind], "--help") == 0) {
        printf("Usage: cat-lite [--help] [FILE]...\n"
               "With no FILE, or when FILE is -, read standard input.\n\n"
               "Examples:\n"
               "  cat-lite README   Print the file README to standard output.\n"
               "  cat-lite f - g    Print f's contents, then standard input,\n"
               "                    then g's contents.\n"
	       "  cat-lite          Copy standard input to standard output.\n");
        return EXIT_SUCCESS;
      }
      else if(strcmp(argv[ind], "-") == 0)
        standardIn = TRUE;
      else if(fopen(argv[ind] == NULL)
        badSwitch = TRUE;
      else if(strcmp(argv[ind], "--serve-icecream") == 0)
        serveIceCream = TRUE;
      else {
        badSwitch = TRUE; // best not to run if there's an error
        fprintf(stderr, "Unknown switch: '%s'\n", argv[ind]);
      }
    }
  }

  // Usually you want to bail if the switches aren't perfect...
  // because this helps developers make more reliable software.
  if(badSwitch) {
    // cat cannot open the file that caused the error
    //    fprintf(stderr, "cat cannot open %s\n",argv[1]);
    return EXIT_FAILURE;
  }

  // If --help is passed, you usually show help and do nothing else
  if(showHelp) {
    printf("Usage: cat-lite [--help] [FILE]...\n"
           "With no FILE, or when FILE is -, read standard input.\n\n"
           "Examples:\n"
           "  cat-lite README   Print the file README to standard output.\n"
	   "  cat-lite f - g    Print f's contents, then standard input,\n"
           "                    then g's contents.\n"
	   "  cat-lite          Copy standard input to standard output.\n");
	   return EXIT_SUCCESS;
  }

  // And here we do something intelligent:
  printf("Do you get icecream? ");
  if(serveIceCream)
    printf("YES!!!\n");
  else
    printf("Sorry, try again next-time.\n");

  return EXIT_SUCCESS;
}
