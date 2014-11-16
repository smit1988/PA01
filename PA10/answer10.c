//Noah Smith
//11/15/2014
//ece264

//The book was referenced for the structures of binary trees

//Make business structure with ID and start of name

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer10.h"

#define BUF 2000
#define NONE 50000

typedef struct Business_st{
  int ID;
  long int address;
  struct Business_st * next;
}Business_struct;

struct YelpDataBST {
  char * name;
  long int address;
  long int review;
  struct YelpDataBST * left;
  struct YelpDataBST * right;
};


Business_struct * Create_bus(long int address, int ID);
void Destroy_bus(Business_struct * bus);
int List_length(Business_struct * list);
Business_struct * List_merge(const char* businesses_path, Business_struct * lhs, Business_struct * rhs, int (*compar)(const char *, const char*));
Business_struct * List_sort(const char* businesses_path, Business_struct * list, int (*compar)(const char *, const char*));

Business_struct * Create_bus(long int address, int ID)
{
  Business_struct * make = NULL;
  make = malloc(sizeof(Business_struct));
  make->address = address;
  make->ID = ID;
  make->next = NULL;
  return make;
}

void Destroy_bus(Business_struct * bus)
{
  if(bus != NULL){
    if(bus->next != NULL)
      Destroy_bus(bus->next);
    free(bus);
  }
}

int List_length(Business_struct * list)
{
  Business_struct * length = list;
  int counter = 0;
  //if length is NULL off the bat, length 0
  while (length != NULL)
    {
      counter++;
      length = length->next;
    }
  return counter;
}

Business_struct * List_merge(const char* businesses_path, Business_struct * lhs, Business_struct * rhs, int (*compar)(const char *, const char*))
{
  //new list
  Business_struct start;
  Business_struct * new = &start;
  start.next = NULL;
  FILE * fptr;
  int length, count;
  char * name;
  char * name1;
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
	  fptr = fopen(businesses_path,"r");
	  if(fptr == NULL)
	    {
	      return NULL;
	    }
	  fseek(fptr,lhs->address,SEEK_SET);
	  length = 0;
	  count = 0;
	  name = malloc(sizeof(char) * BUF);
	  do{
	    name[length] = fgetc(fptr);
	    length++;
	  }while(name[length - 1] != '\t');
	  name[length - 1] = '\0';

	  fseek(fptr,rhs->address,SEEK_SET);
          length = 0;
          count = 0;
          name1 = malloc(sizeof(char) * BUF);
          do{
            name1[length] = fgetc(fptr);
            length++;
          }while(name1[length - 1] != '\t');
          name1[length - 1] = '\0';

	  if((compar(name,name1)) < 0)
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
	  free(name);
	  free(name1);
	  fclose(fptr);
	}
      new = new->next;
    }
  return (start.next);
}

Business_struct * List_sort(const char* businesses_path, Business_struct * list, int (*compar)(const char *, const char*))
{
  Business_struct lhs;
  Business_struct * left = &lhs;
  lhs.next = list;
  //longer
  Business_struct * rhs = list;
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
  lhs.next = List_sort(businesses_path, lhs.next, compar);
  rhs = List_sort(businesses_path, rhs, compar);
  return List_merge(businesses_path, lhs.next, rhs, compar);
}

struct YelpDataBST* create_business_bst(const char* businesses_path, const char* reviews_path)
{
  Business_struct start;
  Business_struct * new = &start;
  start.next = NULL;
  FILE * Bus_tsv;
  char advance = 'a';
  char * ID_char;
  int length, count, ID_bus;
  Bus_tsv = fopen(businesses_path,"r");
  if(Bus_tsv == NULL)
    {
      return NULL;
    }
  while(advance != EOF)
    {
      length = 0;
      count = 0;
      ID_char = malloc(sizeof(char) * BUF);
      do{
        ID_char[length] = fgetc(Bus_tsv);
        length++;
      }while(ID_char[length - 1] != '\t');
      ID_char[length - 1] = '\0';
      ID_bus = atoi(ID_char);
      free(ID_char);
      new->next = Create_bus(ftell(Bus_tsv),ID_bus);
      new = new->next;
      do{
        advance = fgetc(Bus_tsv);
      }while((advance != '\n') && (advance != EOF));
    }
  new = &start;
  char * name;
  advance = 'a';
  while(advance != EOF)
    {
      fseek(Bus_tsv,(new->next)->address,SEEK_SET);
      new = new->next;
      length = 0;
      name = malloc(sizeof(char) * BUF);
      do{
	name[length] = fgetc(Bus_tsv);
	length++;
      }while(name[length - 1] != '\t');
      name[length - 1] = '\0';
      printf("%d\t%s\n",new->ID,name);
      free(name);
      do{
        advance = fgetc(Bus_tsv);
      }while((advance != '\n') && (advance != EOF));
    }
  Destroy_bus(start.next);
  fclose(Bus_tsv);
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
