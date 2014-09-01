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
  int x;
  //Read the array from right to left
  for(x = (len - 1); x >= 0; x--){
    if(*(haystack + x) == needle)
      return x;
  }
  //Return -1 otherwise
  return (-1);
}

int arrayFindSmallest(int * array, int len)
{
  //Assign y to first index
  int x, y = 0;
  //Return 0 if empty array
  if(len == 0)
    return 0;
  for(x = 0; x < len; x++){
    //If current index value is smaller than assigned index value
    if(*(array + x) < *(array + y))
      y = x;
  }
  return y;
}
