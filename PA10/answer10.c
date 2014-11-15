//Noah Smith
//11/15/2014
//ece264

//The book was referenced for the structures of binary trees
//My PA08 code was used for creating and sorting linked lists

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer10.h"

#define BUF 2000

typedef struct ListNode_st
{
  char * name;
  long int address;
  long int review;
  struct ListNode_st * next;
} List;

//Sort by business name, state, city, address, star rating(descending), text of review
//the two files share the business id
//contain business name, file offset for beginning of address for business.tsv, file offset for review text
struct YelpDataBST {
  char * name;
  long int address;
  long int review;
  struct YelpDataBST * left;
  struct YelpDataBST * right;
};

List * List_createNode(const char * name,long int address, long int review);
void List_destroy(List * list);
int List_length(List * list);
List * List_merge(List * lhs, List * rhs, int (*compar)(const char *, const char*));
List * List_sort(List * list, int (*compar)(const char *, const char*));

List * List_createNode(const char * name,long int address, long int review)
{
  List * make = NULL;
  make = malloc(sizeof(List));
  make->name = strdup(name);
  make->address = address;
  make->review = review;
  make->next = NULL;
  return make;
}

void List_destroy(List * list)
{
  if(list != NULL){
    if(list->next != NULL)
      List_destroy(list->next);
    free(list->name);
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

//currently going off name only
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
	  if((compar(lhs->name,rhs->name)) < 0)
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
      if(((length/2) - i) == 1)
	{
	  left->next = NULL;
	}
    }
  lhs.next = List_sort(lhs.next, compar);
  rhs = List_sort(rhs, compar);
  return List_merge(lhs.next, rhs, compar);
}

struct YelpDataBST* create_business_bst(const char* businesses_path, const char* reviews_path)
{
  //Work with business first
  //Read the business ID, store as a variable (not in struct)
  //Read the business name, add to linked list
  //At this point ftell should give the tab or the place after the tab, store it in the list
  //Keep both files open, read the business ID in reviews, if a match, store start of review to list
  //There could be multiple (maybe no?) reviews per business
  //If there are multiple, keep making new nodes with the same data from business_path but new review location
  //Once a nonmatching ID is read, maybe step back the cursor to read it again at the start of the next loop
  FILE * fptr;
  char * ID_char, name;
  long int address, review;
  int ID, length = 0;
  fptr = fopen(businesses_path,"r");
  if(fptr == NULL)
    {
      return NULL;
    }
  //Find business ID
  ID_char = malloc(sizeof(char) * BUF);
  do{
    ID_char[length] = fgetc(fptr);
    length++;
  }while(ID_char[length - 1] != '\t');
  ID_char[length - 1] = '\0';
  ID = atoi(ID_char);
  free(ID_char);
  //ID is now an int, next fgetc will be the first character of the business name

  //Now the linked list needs to be sorted
  //First sort by business name
  //All the rest the data will have to be read to sort
  //Sort by state, city, address, star (descending), text of review
  fclose(fptr);
  return NULL;
}

struct Business* get_business_reviews(struct YelpDataBST* bst,char* name, char* state, char* zip_code)
{
  return NULL;
}

//remember about list destroy at top
void destroy_business_bst(struct YelpDataBST* bst)
{

}

void destroy_business_result(struct Business* b)
{

}
