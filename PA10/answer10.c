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

//Stores the offset of the text and the star rating for a single review
typedef struct Review_offset_st{
  long int text;
  long int stars;
}Review_offset;

//Stores all reviews for a given business through an array of Review_offset structures
typedef struct Review_offset_array_st{
  //malloc size of review_offset * number of entries
  Review_offset * offsets;
}Review_array;

//Stores the business name, ID, offset for the start of the address, and offset for star rating if there is one
//In the future maybe change this to store a Review_array
typedef struct Business_st{
  char * name;
  int ID;
  long int address;
  long int review;
  struct Business_st * next;
}Business_struct;

//Binary tree form of Business_struct
struct YelpDataBST {
  char * name;
  int ID;
  long int address;
  long int review;
  struct YelpDataBST * left;
  struct YelpDataBST * right;
};


Business_struct * Create_bus(char * name, long int address, long int review, int ID);
void Destroy_bus(Business_struct * bus);
//int List_length(Business_struct * list);
//Business_struct * List_merge(const char* businesses_path, Business_struct * lhs, Business_struct * rhs, int (*compar)(const char *, const char*));
//Business_struct * List_sort(const char* businesses_path, Business_struct * list, int (*compar)(const char *, const char*));

Business_struct * Create_bus(char * name, long int address, long int review, int ID)
{
  Business_struct * make = NULL;
  make->name = strdup(name);
  make = malloc(sizeof(Business_struct));
  make->address = address;
  make->review = review;
  make->ID = ID;
  make->next = NULL;
  return make;
}

void Destroy_bus(Business_struct * bus)
{
  if(bus != NULL){
    if(bus->next != NULL)
      Destroy_bus(bus->next);
    free(bus->name);
    free(bus);
  }
}

/*
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
*/

struct YelpDataBST* create_business_bst(const char* businesses_path, const char* reviews_path)
{
  Business_struct start;
  Business_struct * new = &start;
  start.next = NULL;
  FILE * Bus_tsv;
  FILE * Rev_tsv;
  char advance = 'a';
  char * ID_char;
  char * name;
  int length, count, ID_bus, ID_rev;
  long int address, review;
  Bus_tsv = fopen(businesses_path,"r");
  if(Bus_tsv == NULL)
    {
      return NULL;
    }
  Rev_tsv = fopen(reviews_path,"r");
  if(Rev_tsv == NULL)
    {
      return NULL;
    }

  //creates linked list of business ID's, start of name offset, pointer to array of reviews
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
      //ID is now an int, next fgetc will be the first character of the business name
      length = 0;
      name = malloc(sizeof(char) * BUF);
      do{
        name[length] = fgetc(Bus_tsv);
        length++;
      }while(name[length - 1] != '\t');
      name[length - 1] = '\0';
      //Now name is the name of the business in the loop and the the fgetc will be the first character of the address
      address = ftell(Bus_tsv);
      //Find all matching reviews
      //Find review ID
      length = 0;
      ID_char = malloc(sizeof(char) * BUF);
      do{
        ID_char[length] = fgetc(Rev_tsv);
	length++;
      }while(ID_char[length - 1] != '\t');
      ID_char[length - 1] = '\0';
      ID_rev = atoi(ID_char);
      free(ID_char);
      /*The current code will back up to the start of the line
if the ID's match, the review long int will be set to the start of the review ID
if the ID's don't match, the review will be set to an arbitrary value "none"
"none" shouldn't be a good value but is sketchy code right now
       */
      fseek(Rev_tsv, (-1 * length), SEEK_CUR);
      if(ID_rev == ID_bus)
	{
	  review = ftell(Rev_tsv);
	}
      else
	{
	  review = NONE;
	}
      fseek(Rev_tsv, length, SEEK_CUR);
      //Move to next start or EOF
      while(ID_rev == ID_bus)
	{
	  if(ID_bus == 42152)
	    break;
	  do{
	    advance = fgetc(Rev_tsv);
	  }while((advance != '\n') && (advance != EOF));
	  if(advance != EOF)
	    {
	      length = 0;
	      ID_char = malloc(sizeof(char) * BUF);
	      do{
		ID_char[length] = fgetc(Rev_tsv);
		length++;
	      }while(ID_char[length - 1] != '\t');
	      ID_char[length - 1] = '\0';
	      ID_rev = atoi(ID_char);
	      free(ID_char);
	    }
	}
      fseek(Rev_tsv, (-1 * length), SEEK_CUR);
      new->next = Create_bus(name,address, review, ID_bus);
      free(name);
      new = new->next;
      printf("%ld %ld\n",new->address,new->review);
      do{
        advance = fgetc(Bus_tsv);
      }while((advance != '\n') && (advance != EOF));
    }

  /*
  //Turn list into binary tree
  static struct YelpDataBST * TreeNode_construct(long int business, long int review, int ID, char * name)
  {
    YelpDataBST * tn;
    tn = malloc(sizeof(YelpDataBST));
    tn->left = NULL;
    tn->right = NULL;
    //free this somewhere
    tn->name = strdup(name);
    tn->ID = ID;
    tn->business = business;
    tn->review = review;
    return tn;
  }

  YelpDataBST * Tree_insert(YelpDataBST * tn, long int business, long int review, int ID, char * name)
  {
    if(tn==NULL)
      {
	return TreeNode_construct(business, review, ID, name);
      }
    if(strcasecmp(tn->name,name) == 0)
      {
	//value already in there (shouldn't really happen in this program
	return tn;
      }
    if(strcasecmp(tn->name,name) > 0) //tn->name is greater than name
      {
	tn->left = Tree_insert(tn->left,business,review,ID,name);
      }
    else
      {
	tn->right = Tree_insert(tn->right,business,review,ID,name);
      }
    return tn;
  }
  */
  /*
  start.next = List_sort(businesses_path,start.next,strcmp);
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
  */
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
