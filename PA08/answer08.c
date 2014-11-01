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
  if(list != NULL){
    if(list->next != NULL)
      List_destroy(list->next);
    free(list->str);
    free(list);
  }
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
  //new list
  List * new = NULL;
  //keep track of head
  List * start = new;
  //if lhs is null, the remaining is rhs
  //if rhs is null, the remaining is lhs
  //if neither are null, the next element is the greater of the two
  //if at least one of the elements is left
  while((lhs != NULL) || (rhs != NULL))
    {
      if(rhs == NULL)
	{
	  new = lhs;
	  lhs = lhs->next;
	}
      else if(lhs == NULL)
	{
	  new = rhs;
	  rhs = rhs->next;
	}
      else
	{
	  //if lhs is greater
	  if(strcmp(lhs->str,rhs->str) > 0)
	    {
	      new = lhs;
	      lhs = lhs->next;
	    }
	  //if rhs is greater or equal
	  else
	    {
	      new = rhs;
	      rhs = rhs->next;
	    }
	}
      new = new->next;
      new = NULL;
    }
  return start;
}

List * List_sort(List * list, int (*compar)(const char *, const char*))
{
  return list;
}
