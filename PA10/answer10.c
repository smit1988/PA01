//Noah Smith
//11/15/2014
//ece264

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer10.h"

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

//Linked list of name, address location, and review location
//Sort linked list
//Create binary tree

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

  //Now the linked list needs to be sorted
  //First sort by business name
  //All the rest the data will have to be read to sort
  //Sort by state, city, address, star (descending), text of review
}

struct Business* get_business_reviews(struct YelpDataBST* bst,char* name, char* state, char* zip_code)
{
  return NULL;
}

void destroy_business_bst(struct YelpDataBST* bst)
{

}

void destroy_business_result(struct Business* b)
{

}
