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
    return 0;
}

int arrayIndexRFind(int needle, const int * haystack, int len)
{
    return 0;
}

int arrayFindSmallest(int * array, int len)
{
    return 0;
}
