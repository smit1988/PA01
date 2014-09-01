#include <stdlib.h>
#include "answer01.h"

int arraySum(int * array, int len)
{
  int x, sum = 0;
  for(x = 0; x < len; x++){
    sum = *(array + x) + sum;
  }

  return sum;
}

int arrayCountNegative(int * array, int len)
{
  int x, count = 0;
  for(x = 0; x < len; x++){
    if(*(array + x) < 0)
      count++;
  }

  return count;
}

int arrayIsIncreasing(int * array, int len)
{
  int x;
  //Return 1 if array is empty
  if(len == 0)
    return 1;
  //Return 0 if the current array value is greater than the next    
  for(x = 0; x < (len - 1); x++){
    if(*(array + x) > *(array + x + 1))
      return 0;
  }
  //Return 1 otherwise
  return 1;
}

int arrayIndexRFind(int needle, const int * haystack, int len)
{
    return 0;
}

int arrayFindSmallest(int * array, int len)
{
    return 0;
}
