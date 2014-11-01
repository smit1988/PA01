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
  List * left = lhs;
  List * right = rhs;
  //new list
  List * new = NULL;
  //keep track of head
  List * start = new;
  //if at least one of the elements is left
  while((left != NULL) || (right != NULL))
    {
      if(right == NULL)
	{
	  new = left;
	  left = left->next;
	}
      else if(left == NULL)
	{
	  new = right;
	  right = right->next;
	}
      else
	{
	  //if lhs is greater
	  if(compar(left->str,right->str) > 0)
	    {
	      new = left;
	      left = left->next;
	    }
	  //if rhs is greater or equal
	  else
	    {
	      new = right;
	      right = right->next;
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
