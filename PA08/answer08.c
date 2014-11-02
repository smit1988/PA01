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
  List start;
  List * new = &start;
  start.next = NULL;
  //keep track of head
  //if lhs is null, the remaining is rhs
  //if rhs is null, the remaining is lhs
  //if neither are null, the next element is the greater of the two
  //if at least one of the elements is left
  while((lhs != NULL) || (rhs != NULL))
    {
      if(rhs == NULL)
	{
	  new->next = lhs;
	  break;
	}
      else if(lhs == NULL)
	{
	  new->next = rhs;
	  break;
	}
      else
	{
	  //if lhs is greater
	  if((compar(lhs->str,rhs->str)) < 0)
	    {
	      new->next = lhs;
	      lhs = lhs->next;
	    }
	  //if rhs is greater or equal
	  else
	    {
	      new->next = rhs;
	      rhs = rhs->next;
	    }
	}
      new = new->next;
    }
  return (start.next);
}

List * List_sort(List * list, int (*compar)(const char *, const char*))
{
  List lhs;
  List * left = &lhs;
  lhs.next = list;
  //longer
  List * rhs = list;
  int i;
  int length = List_length(list);
  if(length <= 1)
    {
      return list;
    }
  for(i = 0; i < (length/2); i++)
    {
      left = left->next;
      rhs = rhs->next;
      if(((length/2) - i - 1))
	{
	 left->next = NULL;
	}
    }
  List_sort(lhs.next, compar);
  List_sort(rhs, compar);
  return List_merge(lhs.next, rhs, compar);
}
