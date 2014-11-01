//Noah Smith
//November 1, 2014
//Ece264

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer08.h"

List * List_createNode(const char * str)
{
  List * make = NULL;
  make = malloc(sizeof(List));
  make->str = strdup(str);
  make->next = NULL;
  return make;
}

void List_destroy(List * list)
{
  if(list->next != NULL)
    List_destroy(list->next);
  free(list->str);
  free(list);
}

int List_length(List * list)
{
  List * length = list;
  int counter = 0;
  //if length is NULL off the bat, length 0
  while (length != NULL)
    {
      counter++;
      length = length->next;
    }
  return counter;
}

List * List_merge(List * lhs, List * rhs, int (*compar)(const char *, const char*))
{
  return 0;
}

List * List_sort(List * list, int (*compar)(const char *, const char*))
{
  return list;
}
