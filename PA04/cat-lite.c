//Noah Smith
//Ece264
//9/18/2014

//Code structure copied from Prof. Lu's example.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * * argv)
{
  int ind;
  //may need a bigger string
  char str[80];
  FILE *fptr;

  // Test for '-', empty, nonexistent file, and help. Otherwise, it's a file
  if(argc == 1){
    scanf("%79s",str);
    printf("%s\n",str);
    return EXIT_SUCCESS;
    //do something with standard input, then exit
  }
  else {
    //seek help
    for(ind = 1; ind < argc; ind++){
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
    }

    //seek bad file
    for(ind = 1; ind < argc; ind++) {
      if(fopen(argv[ind], "r") == NULL){
        fprintf(stderr, "cat cannot open %s\n",argv[ind]);
	return EXIT_FAILURE;
      }
    }

    //Everything should be error free, execute code
    for(ind = 1; ind < argc; ind++) {
      if(strcmp(argv[ind], "-") == 0){
	scanf("%79s",str);
	printf("%s\n",str);
        //do something for standard input
      }
      else{
	//do file stuff
      }
    }
  }
  return EXIT_SUCCESS;
}
