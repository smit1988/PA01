//Noah Smith
//11/15/2014
//ece264

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "answer10.h"

//This funciton is similar to the example reference page for realloc
void read_tab(FILE * fptr, char * buffer)
{
  int max = 2000;
  buffer = malloc(sizeof(char) * max);
  int count = 0;
  int length = 0;
  buffer[0] = '0';
  while((buffer[length] != '\t') && (buffer[length] != EOF))
    {
      if(count == max)
	{
	  max *= 2;
	  buffer = realloc(buffer, max);
	}
      buffer[length] = fgetc(fptr);
      if(buffer[length] == '\t')
	break;
      length++;
      count++;
    }
  buffer[length] = '\0';
  printf("%s",buffer);
}

int main(int argc, char ** argv)
{
  FILE * fptr = NULL;
  /*int ID;
  char * name;
  char * address;
  char * city;
  char * state;
  int zip_code;
  char * full_address;
  */
  fptr = fopen("/home/shay/a/ece264p0/share/yelp_data/businesses.tsv", "r");
  if(fptr == NULL)
    {
      fclose(fptr);
      return 0;
    }
  fclose(fptr);
  return 0;
}
