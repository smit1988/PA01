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

//Stores the business name, ID, offset for the start of the address, and offset for star rating if there is one
//In the future maybe change this to store a Review_array
typedef struct Business_st{
  char * name;
  int ID;
  long int address;
  //An array of reviews
  Review_offset * rev_array;
  //long int review;
  struct Business_st * next;
}Business_struct;

//Binary tree form of Business_struct
struct YelpDataBST {
  char * name;
  long int address;
  Review_offset * rev_array;
  struct YelpDataBST * left;
  struct YelpDataBST * right;
};


Business_struct * Create_bus(const char * name, long int address, Review_offset * rev_array, int ID, int count);
void Destroy_bus(Business_struct * bus);
static struct YelpDataBST * TreeNode_construct(long int address, Review_offset * rev_array, char * name);
struct YelpDataBST * Tree_insert(struct YelpDataBST * tn, long int address, Review_offset * rev_array, char * name);

Business_struct * Create_bus(const char * name, long int address, Review_offset * rev_array, int ID, int count)
{
  Business_struct * make = NULL;
  make = malloc(sizeof(Business_struct));
  make->name = strdup(name);
  make->address = address;
  //Leave the passed rev_array as is, just point to it
  make->rev_array = rev_array;
  make->ID = ID;
  make->next = NULL;
  return make;
}

void Destroy_bus(Business_struct * bus)
{
  if(bus != NULL){
    if(bus->next != NULL)
      Destroy_bus(bus->next);
    /*
    if(bus->rev_array != NULL)
       free(bus->rev_array);
    */
    free(bus->name);
    free(bus);
  }
}

static struct YelpDataBST * TreeNode_construct(long int address, Review_offset * rev_array, char * name)
{
  struct YelpDataBST * tn;
  //free this somewhere
  tn = malloc(sizeof(struct YelpDataBST));
  tn->left = NULL;
  tn->right = NULL;
  //free this somewhere
  tn->name = strdup(name);
  tn->address = address;
  //free this somwehre and make sure it isn't freed from the linked list
  tn->rev_array = rev_array;
  return tn;
}

struct YelpDataBST * Tree_insert(struct YelpDataBST * tn, long int address, Review_offset * rev_array, char * name)
{
  if(tn==NULL)
    {
      return TreeNode_construct(address, rev_array, name);
    }
  if(strcasecmp(tn->name,name) == 0)
    {
      //value already in there (shouldn't really happen in this program
      return tn;
    }
  if(strcasecmp(tn->name,name) > 0) //tn->name is greater than name
    {
      tn->left = Tree_insert(tn->left,address,rev_array,name);
    }
  else
    {
      tn->right = Tree_insert(tn->right,address,rev_array,name);
    }
  return tn;
}

struct YelpDataBST* create_business_bst(const char* businesses_path, const char* reviews_path)
{
  //start.next is the first node
  Business_struct start;
  Business_struct * new = &start;
  start.next = NULL;
  //root.left is the root node
  struct YelpDataBST root;
  //struct YelpDataBST * leaves = &root;
  root.left = NULL;
  Review_offset * rev_array = NULL;
  FILE * Bus_tsv;
  FILE * Rev_tsv;
  char advance = 'a';
  char * ID_char;
  char * name;
  int length, count, i, ID_bus = 0, ID_rev;
  long int address;
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
  while(ID_bus != 42152)
    {
      rev_array = NULL;
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

      //To pass the review array
      //Check if the ID's match, if not set the review array to NULL and move on
      //If the ID's match, a new entry will be added so allocate memory for it
      //Get the offset for the star rating
      //Get the offset for the review text
      //Go to the next line
      //Read next ID
      //If it is a match, leave as is and move on
      //If it is not a match backup to start of line
      //Restart the loop to see if the ID's match
      //don't forget to free
      //printf("ID_bus: %d\n",ID_bus);
      count = 1;
      while(ID_bus == ID_rev)
	{
	  rev_array = realloc(rev_array,sizeof(Review_offset) * count);
	  rev_array[count-1].stars = ftell(Rev_tsv);
	  //Progress to start of text
	  for(i = 0; i < 4; i++)
	    {
	      do{
		advance = fgetc(Rev_tsv);
	      }while(advance != '\t');
	    }
	  rev_array[count-1].text = ftell(Rev_tsv);
	  //printf("%ld %ld\n",rev_array[count-1].stars,rev_array[count-1].text);
	  //Next line
	  do{
	    advance = fgetc(Rev_tsv);
	  }while((advance != '\n') && (advance != EOF));
	  count++;
	  //Last entry, EOF wasn't working for some reason
	  if((ID_bus == 42152) && (count == 15))
	    {
	      break;
	    }
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
	}
      fseek(Rev_tsv,(-1 * length), SEEK_CUR);
      new->next = Create_bus(name,address, rev_array, ID_bus, count);
      free(name);
      /*
      if(rev_array != NULL)
	free(rev_array);
      */
      new = new->next;
      //printf("%s %ld\n",new->name,new->address);
      do{
        advance = fgetc(Bus_tsv);
      }while((advance != '\n') && (advance != EOF));
    }

  //Turn list into binary tree
  //root.left is the root node of the tree
  new = &start;
  while(new->next != NULL)
    {
      new = new->next;
      Tree_insert(root.left, new->address, new->rev_array, new->name);
    }

  Destroy_bus(start.next);
  destroy_business_bst(root.left);
  fclose(Bus_tsv);
  fclose(Rev_tsv);
  return NULL;
}

struct Business* get_business_reviews(struct YelpDataBST* bst,char* name, char* state, char* zip_code)
{
  return NULL;
}

//remember about list destroy at top
void destroy_business_bst(struct YelpDataBST* bst)
{
  if(bst == NULL)
    return;
  free(bst->name);
  free(bst->rev_array);
  destroy_business_bst(bst->left);
  destroy_business_bst(bst->right);
  free(bst);
}

void destroy_business_result(struct Business* b)
{

}

int main(int argc, char ** argv)
{
  create_business_bst("/home/shay/a/ece264p0/share/yelp_data/businesses.tsv", "/home/shay/a/ece264p0/share/yelp_data/reviews.tsv");
  return 0;
}
