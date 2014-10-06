//Noah Smith
//PA05
//10/5/2014

//Credit for logic goes to Professor Lu
//Logic retrieved from Intermediate C Programming Chapter 14

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer05.h"

void printPartition(int * arr, int length)
{
  int ind;
  for(ind = 0;ind < (length - 1);ind++)
    {
      printf("%d + ", arr[ind]);
    }
  printf("%d\n", arr[length - 1]);
}

