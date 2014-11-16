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
  FILE * fptr1;
  char * ID_char;
  char * name;
  char advance;
  long int address, review;
  int ID_bus, ID_rev, count = 0, length = 0, max = BUF;
  List start;
  List * new = &start;
  start.next = NULL;
  fptr = fopen(businesses_path,"r");
  if(fptr == NULL)
    {
      return NULL;
    }
  fptr1 = fopen(reviews_path,"r");
  if(fptr1 == NULL)
    {
      return NULL;
    }
 
  while(1)//breaks at end if EOF
    {
      max = BUF;
      length = 0;
      count = 0;
      //Find business ID
      ID_char = malloc(sizeof(char) * BUF);
      do{
	ID_char[length] = fgetc(fptr);
	length++;
      }while(ID_char[length - 1] != '\t');
      ID_char[length - 1] = '\0';
      ID_bus = atoi(ID_char);
      free(ID_char);
      //ID is now an int, next fgetc will be the first character of the business name
      name = malloc(sizeof(char) * max);
      length = 0;
      name[0] = '0';
      do{
	if(count == max)
	  {
	    max *= 2;
	    name = realloc(name, max);
	  }
	name[length] = fgetc(fptr);
	length++;
	count++;
      }while(name[length - 1] != '\t');
      name[length - 1] = '\0';
      //The current position is the start of the address
      address = ftell(fptr);

      //Find all matching reviews
      do{
	length = 0;
	//Find review ID
	ID_char = malloc(sizeof(char) * BUF);
	do{
	  ID_char[length] = fgetc(fptr1);
	  length++;
	}while(ID_char[length - 1] != '\t');
	ID_char[length - 1] = '\0';
	ID_rev = atoi(ID_char);
	free(ID_char);
	if(ID_rev == ID_bus) //same business
	  {
	    count = 0;
	    while(count < 4)
	      {
		while((fgetc(fptr1)) != '\t'){}
		count++;
	      }
	    review = ftell(fptr1);
	    new->next = List_createNode(name, address, review);
	    new = new->next;
	    do{
	      advance = fgetc(fptr1);
	    }while((advance != '\n') && (advance != EOF));
	    if(advance == EOF)
	      {
		break;
	      }
	  }
	else
	  {
	    //either store value for next or rewind to reread
	    fseek(fptr1, (-1 * length), SEEK_CUR);
	  }
      }while(ID_rev == ID_bus);
      free(name);
      //Move on to next business
      do{
	advance = fgetc(fptr);
      }while((advance != '\n') && (advance != EOF));
      if(advance == EOF)
	{
	  break;
	}
  }
  
  /*new = start.next;
  printf("%s %ld %ld\n",new->name,new->address,new->review);
  new = new->next;
  printf("%s %ld %ld\n",new->name,new->address,new->review);
  new = new->next;
  printf("%s %ld %ld\n",new->name,new->address,new->review);
  new = new->next;
  printf("%s %ld %ld\n",new->name,new->address,new->review);
  new = new->next;
  printf("%s %ld %ld\n",new->name,new->address,new->review);
  new = new->next;
  printf("%s %ld %ld\n",new->name,new->address,new->review);
  new = new->next;
  printf("%s %ld %ld\n",new->name,new->address,new->review);
  new = new->next;
  printf("%s %ld %ld\n",new->name,new->address,new->review);
  new = new->next;
  printf("%s %ld %ld\n",new->name,new->address,new->review);
  new = new->next;
  printf("%s %ld %ld\n",new->name,new->address,new->review);
  */
  //Now the linked list needs to be sorted
  //First sort by business name
  //All the rest the data will have to be read to sort
  //Sort by state, city, address, star (descending), text of review
  List_destroy(start.next);
  fclose(fptr);
  fclose(fptr1);
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

int main(int argc, char ** argv)
{
  create_business_bst("/home/shay/a/ece264p0/share/yelp_data/businesses.tsv", "/home/shay/a/ece264p0/share/yelp_data/reviews.tsv");
  return 0;
}
