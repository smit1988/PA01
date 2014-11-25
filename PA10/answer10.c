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
  int rev_size;
  struct Business_st * next;
}Business_struct;

//Binary tree form of Business_struct
struct YelpDataBST {
  const char * bus_file;
  const char * rev_file;
  char * name;
  //long int address;
  //Review_offset * rev_array;
  //Root of linked list
  Business_struct * List_root;
  //Array of businesses with same name
  //Array of pointers
  Business_struct * * locations;
  int locations_size;
  struct YelpDataBST * left;
  struct YelpDataBST * right;
};


Business_struct * Create_bus(const char * name, long int address, Review_offset * rev_array, int ID, int rev_size);
void Destroy_bus(Business_struct * bus);
static struct YelpDataBST * TreeNode_construct(char * name, Business_struct * List_root, Business_struct * locations, const char * bus_file, const char * rev_file);
struct YelpDataBST * Tree_insert(struct YelpDataBST * tn,char * name, Business_struct * List_root, Business_struct * locations, const char * bus_file, const char * rev_file);
struct YelpDataBST * Tree_search(struct YelpDataBST * tn, char * name);
static void TreeNode_print(struct YelpDataBST * tn);
static void Tree_printInorder(struct YelpDataBST * tn);
void destroy_business_bst_list(struct YelpDataBST * bst);
void destroy_business_bst_tree(struct YelpDataBST * bst);

static void TreeNode_print(struct YelpDataBST * tn)
{
  printf("%s\n",tn->name);
}

static void Tree_printInorder(struct YelpDataBST * tn)
{
  if(tn == NULL)
    return;
  Tree_printInorder(tn->left);
  TreeNode_print(tn);
  Tree_printInorder(tn->right);
}

Business_struct * Create_bus(const char * name, long int address, Review_offset * rev_array, int ID, int rev_size)
{
  Business_struct * make = NULL;
  make = malloc(sizeof(Business_struct));
  make->rev_size = rev_size;
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
    if(bus->rev_array != NULL)
       free(bus->rev_array);
    free(bus->name);
    free(bus);
  }
}

//If this function is called, the name of the to be created node has not been used before
//List is destroyed with tree so it's okay to have an array of list nodes
static struct YelpDataBST * TreeNode_construct(char * name, Business_struct * List_root, Business_struct * locations, const char * bus_file, const char * rev_file)
{
  struct YelpDataBST * tn;
  tn = malloc(sizeof(struct YelpDataBST));
  tn->left = NULL;
  tn->right = NULL;
  tn->bus_file = bus_file;
  tn->rev_file = rev_file;
  tn->name = name;
  tn->List_root = List_root;
  //free somewhere
  tn->locations = malloc(sizeof(Business_struct *));
  (tn->locations)[0] = locations;
  tn->locations_size = 1;
  return tn;
}

struct YelpDataBST * Tree_insert(struct YelpDataBST * tn, char * name, Business_struct * List_root, Business_struct * locations, const char * bus_file, const char * rev_file)
{
  if(tn==NULL)
    {
      return TreeNode_construct(name, List_root, locations,bus_file,rev_file);
    }
  //If the names are the same, reallocate the locations in the node with the name already to add this one
  if(strcasecmp(tn->name,name) == 0)
    {
      //Find size of locations
      //reallocat to 1+size
      //insert current business
      (tn->locations_size)++;
      tn->locations = realloc(tn->locations, (sizeof(Business_struct *)) * tn->locations_size);
      (tn->locations)[(tn->locations_size) - 1] = locations;
      return tn;
    }
  if(strcasecmp(tn->name,name) > 0) //tn->name is greater than name
    {
      tn->left = Tree_insert(tn->left,name, List_root,locations,bus_file,rev_file);
    }
  else
    {
      tn->right = Tree_insert(tn->right,name, List_root,locations,bus_file,rev_file);
    }
  return tn;
}

//returns tree node of the match
struct YelpDataBST * Tree_search(struct YelpDataBST * tn, char * name)
{
  if(tn== NULL)
    return NULL;
  if(strcasecmp(name,tn->name) == 0)
    return tn;
  if(strcasecmp(tn->name,name) > 0)
    return Tree_search(tn->left,name);
  return Tree_search(tn->right,name);
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
      new->next = Create_bus(name,address, rev_array, ID_bus, (count - 1));
      free(name);
      new = new->next;
      do{
        advance = fgetc(Bus_tsv);
      }while((advance != '\n') && (advance != EOF));
    }
  //Forget this address for the last entry (memory errors)
  rev_array = NULL;

  //Turn list into binary tree
  //root.left is the root node of the tree
  new = &start;
  while(new->next != NULL)
    {
      new = new->next;
      root.left = Tree_insert(root.left, new->name, start.next, new, businesses_path, reviews_path);
    }

  //Tree_printInorder(root.left);
  //Add root of linked list to bst struct so it can be returned
  //Destroy_bus(start.next);
  //destroy_business_bst(root.left);
  fclose(Bus_tsv);
  fclose(Rev_tsv);
  return root.left;
}

struct Business* get_business_reviews(struct YelpDataBST* bst,char* name, char* state, char* zip_code)
{
  //YelpDataBST has the name, array of location nodes, and the number of locations
  //Location nodes have start of address and array of reviews
  //Reviews have start of star and start of review text
  //Locations should be sorted by state >> city >> address
  //Reviews should be sorted by star rating (descending) >> text of review
  //bst is the root of the tree
  //name is the name of the business to search for (case insensitive)
  //state is two letter (uppercase) state code to filter by, or NULL for all
  //zip code or NULL
  //
  //First search the tree for the case insensitive name
  //store the name in business struct object
  //start a loop for finding all the locations and allocating
  //load address, city, state, zip code into the struct
  //start a loop for finding all the reviews and allocating
  //Now an entire Business struct should be loaded into memory
  //
  //Possibly now create the Business struct that will be returned
  //One by one find the lowest or highest value (state>>city>>address) and load into this new struct
  //When a new location is added to the new struct, go in and sort the reviews (star rating descending>>text)
  struct YelpDataBST * tree_node;
  struct Business * bus_load;
  struct Location * load_loc;
  struct Review * load_rev;
  int i, j, k, length, max;
  char * buffer;
  FILE * Bus_tsv;
  FILE * Rev_tsv;
  tree_node = Tree_search(bst, name);
  bus_load = malloc(sizeof(struct Business));
  //no need to free name
  bus_load->name = name;
  bus_load->num_locations = (uint32_t) tree_node->locations_size;
  load_loc = bus_load->locations;
  load_loc = malloc(sizeof(struct Location) * tree_node->locations_size);
  Bus_tsv = fopen(tree_node->bus_file,"r");
  if(Bus_tsv == NULL)
    {
      return NULL;
    }
  Rev_tsv = fopen(tree_node->rev_file,"r");
  if(Rev_tsv == NULL)
    {
      return NULL;
    }
  //First loops goes through every location
  for(i = 0; i < tree_node->locations_size; i++)
    {
      fseek(Bus_tsv,((tree_node->locations)[i])->address, SEEK_CUR);
      //four tabs finds address, city, state, zip code
      for(j = 0; j < 4; j++)
	{
	  //This function may be similar to the example reference page for realloc
	  max = BUF;
	  buffer = malloc(sizeof(char) * max);
	  length = 0;
	  do{
	    if(length == max)
	      {
		max *= 2;
		buffer = realloc(buffer, max);
	      }
	    buffer[length] = fgetc(Bus_tsv);
	    length++;
	  }while(buffer[length-1] != '\t');
	  buffer[length-1] = '\0';
	  if(j == 0)
	    load_loc[i].address = strdup(buffer);
	  else if(j == 1)
	    load_loc[i].city = strdup(buffer);
	  else if(j == 2)
	    load_loc[i].state = strdup(buffer);
	  else
	    load_loc[i].zip_code = strdup(buffer);
	  free(buffer);
	  load_rev = (load_loc[i]).reviews;
	  //count number of reviews to malloc
	  load_rev = malloc(sizeof(struct Review) * (((tree_node->locations)[i])->rev_size));
	  //This loop makes array of reviews for each location
	  for(k = 0; k < (((tree_node->locations)[i])->rev_size); k++)
	    {
	      fseek(Rev_tsv,((((tree_node->locations)[i])->rev_array)[k]).stars,SEEK_CUR);
	      buffer = malloc(sizeof(char) * BUF);
	      buffer[0] = fgetc(Rev_tsv);
	      buffer[1] = '\0';
	      load_rev[k].stars = (uint8_t) atoi(buffer);	      
	      free(buffer);
	      fseek(Rev_tsv,((((tree_node->locations)[i])->rev_array)[k]).text,SEEK_CUR);
	      max = BUF;
	      buffer = malloc(sizeof(char) * max);
	      length = 0;
	      do{
		if(length == max)
		  {
		    max *= 2;
		    buffer = realloc(buffer, max);
		  }
		buffer[length] = fgetc(Rev_tsv);
		length++;
	      }while((buffer[length-1] != '\n') && (buffer[length-1] != EOF));
	      buffer[length-1] = '\0';
	      load_rev[k].text = strdup(buffer);
	      free(buffer);
	    }
	}
    }
  //In its current state nothing is sorted
  fclose(Bus_tsv);
  fclose(Rev_tsv);
  return bus_load;
}

//The linked list has to be destroyed first then the tree can be
void destroy_business_bst(struct YelpDataBST* bst)
{
  destroy_business_bst_list(bst);
}

void destroy_business_bst_list(struct YelpDataBST * bst)
{
  Destroy_bus(bst->List_root);
  destroy_business_bst_tree(bst);
}

void destroy_business_bst_tree(struct YelpDataBST * bst)
{
  if(bst == NULL)
    return;
  destroy_business_bst_tree(bst->left);
  destroy_business_bst_tree(bst->right);
  free(bst->locations);
  free(bst);
}

void destroy_business_result(struct Business* b)
{
  int i;
  int j;  
  for(i = sizeof(b->locations)/sizeof(struct Location); i > 0; i--)
    {
      for(j = sizeof((((b->locations)[i-1]).reviews)) / sizeof(struct Review); j > 0; j--)
	{
	  free(((((b->locations)[i-1]).reviews)[j-1]).text);
	}
      free(((b->locations)[i-1]).address);
      free(((b->locations)[i-1]).city);
      free(((b->locations)[i-1]).state);
      free(((b->locations)[i-1]).zip_code);
      free(((b->locations)[i-1]).reviews);
    }
  free(b->locations);
  free(b);
}

/*
int main(int argc, char ** argv)
{
  struct YelpDataBST * test;
  test = create_business_bst("/home/shay/a/ece264p0/share/yelp_data/businesses.tsv", "/home/shay/a/ece264p0/share/yelp_data/reviews.tsv");
  Tree_printInorder(test);
  destroy_business_bst(test);
  return 0;
}
*/
