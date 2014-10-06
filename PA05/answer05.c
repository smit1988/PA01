//Noah Smith
//PA05
//10/5/2014

//Credit for logic goes to Professor Lu
//Logic retrieved from Intermediate C Programming Chapter 14

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer05.h"

//partitionXX allocates memory to partitionXXMemory
void partitionAllMemory(int * arr, int ind, int left);
void partitionIncreasingMemory(int * arr, int ind, int left);
void partitionDecreasingMemory(int * arr, int ind, int left);
void partitionOddMemory(int * arr, int ind, int left);
void partitionEvenMemory(int * arr, int ind, int left);
void partitionOddAndEvenMemory(int * arr, int ind, int left);
void partitionPrimeMemory(int * arr, int ind, int left);
void printPartition(int * arr, int length);

void printPartition(int * arr, int length)
{
  int ind;
  printf("= ");
  for(ind = 0;ind < (length - 1);ind++)
    {
      printf("%d + ", arr[ind]);
    }
  printf("%d\n", arr[length - 1]);
}

void partitionAll(int value)
{
  int * arr;
  arr = malloc(sizeof(int) * value);
  partitionAllMemory(arr, 0, value);
  free(arr);
}

void partitionIncreasing(int value)
{
  return;
}

void partitionDecreasing(int value)
{
  return;
}

void partitionOdd(int value)
{
  int * arr;
  arr = malloc(sizeof(int) * value);
  partitionOddMemory(arr, 0, value);
  free(arr);
}

void partitionEven(int value)
{
  return;
}

void partitionOddAndEven(int value)
{
  return;
}

void partitionPrime(int value)
{
  return;
}

void partitionAllMemory(int * arr, int ind, int left)
{
  int val;
  if(left == 0)
    {
      printPartition(arr, ind);
      return;
    }
  for(val = 1;val <= left; val++)
    {
      arr[ind] = val;
      partitionAllMemory(arr, ind + 1, left - val);
    }
}

void partitionIncreasingMemory(int * arr, int ind, int left)
{
  return;
}

void partitionDecreasingMemory(int * arr, int ind, int left)
{
  return;
}

void partitionOddMemory(int * arr, int ind, int left)
{
  int val;
  if (left == 0)
    {
      printPartition(arr, ind);
      return;
    }
  for(val = 1;val <= left; val += 2)
    {
      arr[ind] = val;
      partitionOddMemory(arr, ind + 1, left - val);
    }
}

void partitionEvenMemory(int * arr, int ind, int left)
{
  return;
}

void partitionOddAndEvenMemory(int * arr, int ind, int left)
{
  return;
}

void partitionPrimeMemory(int * arr, int ind, int left)
{
  return;
}
