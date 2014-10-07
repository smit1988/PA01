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
void printPartitionDecreasing(int * arr, int length);


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

void printPartitionDecreasing(int * arr, int length)
{
  int ind;
  printf("= ");
  for(ind = 0;ind < (length - 1);ind++)
    {
      printf("%d + ", arr[length - 1 - ind]);
    }
  printf("%d\n", arr[ind]);
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
  int * arr;
  arr = malloc(sizeof(int) * value);
  partitionIncreasingMemory(arr, 0, value);
  free(arr);
}

void partitionDecreasing(int value)
{
  int * arr;
  arr = malloc(sizeof(int) * value);
  partitionDecreasingMemory(arr, 0, value);
  free(arr);
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
  int * arr;
  arr = malloc(sizeof(int) * value);
  partitionEvenMemory(arr, 0, value);
  free(arr);
}

void partitionOddAndEven(int value)
{
  int * arr;
  arr = malloc(sizeof(int) * value);
  partitionOddAndEvenMemory(arr, 0, value);
  free(arr);
}

void partitionPrime(int value)
{
  int * arr;
  arr = malloc(sizeof(int) * value);
  partitionPrimeMemory(arr, 0, value);
  free(arr);
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
  int val;
  if(left == 0)
    {
      printPartition(arr, ind);
      return;
    }
  //The initial minimum can't be lower than 1
  int min = 1;
  //After the first value, the min can't be lower than one plus the previous
  if(ind != 0)
    min = arr[ind - 1] + 1;
  //If the min is less than or equal to the remaining integer sum, continue
  for(val = min;val <= left; val++)
    {
      arr[ind] = val;
      partitionIncreasingMemory(arr, ind + 1, left - val);
    }
}

void partitionDecreasingMemory(int * arr, int ind, int left)
{
  int val;
  if(left == 0)
    {
      printPartitionDecreasing(arr, ind);
      return;
    }
  //The initial minimum can't be lower than 1
  int min = 1;
  //After the first value, the min can't be lower than one plus the previous
  if(ind != 0)
    min = arr[ind - 1] + 1;
  //If the min is less than or equal to the remaining integer sum, continue
  for(val = min;val <= left; val++)
    {
      arr[ind] = val;
      partitionIncreasingMemory(arr, ind + 1, left - val);
    }
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
  int val;
  if (left == 0)
    {
      printPartition(arr, ind);
      return;
    }
  for(val = 2;val <= left; val += 2)
    {
      arr[ind] = val;
      partitionEvenMemory(arr, ind + 1, left - val);
    }
}

void partitionOddAndEvenMemory(int * arr, int ind, int left)
{
  int val;
  if(left == 0)
    {
      printPartition(arr, ind);
      return;
    }
  for(val = 1;val <= left; val++)
    {
      int valid = 0;
      if(ind == 0)
	valid = 1;
      else
	valid = (arr[ind - 1] % 2) != (val % 2);
      if(valid == 1)
	{
	  arr[ind] = val;
	  partitionOddAndEvenMemory(arr, ind + 1, left - val);
	}
    }
}

void partitionPrimeMemory(int * arr, int ind, int left)
{
  int val;
  int prime = 0;
  if(left == 0)
    {
      printPartition(arr, ind);
      return;
    }
  //The first prime number is 2
  for(val = 2; val <= left; val++)
    {
      //Check for primeness
      for(prime = 2; (prime < val) && (prime != 1); prime++)
	{
	  //If not prime, prime will equal 1 and end both for interations
	  if((val % prime) == 0)
	    prime = 1;
	}
      if(prime != 1)
	{
	  arr[ind] = val;
	  partitionPrimeMemory(arr, ind + 1, left - val);
	}
    }
}
