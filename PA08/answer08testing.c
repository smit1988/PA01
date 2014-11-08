#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct ListNode_st
{
  char * str;
  struct ListNode_st * next;
} List;

static void List_print(List * list)
{
  List * tail = list;
  while(tail != NULL) {
    printf("\"%s\" ==> ", tail->str);
    tail = tail->next;
  }
  printf("NULL\n");
}

int main()
{
  List * something = NULL;
  //List * the = NULL;
  //the.next = NULL;
  something = malloc(sizeof(List));
  something->str = malloc(2*sizeof(char));
  something->str[0] = 'H';
  something->str[1] = 'i';
  //the = something;
  List_print(something);
  free(something->str);
  free(something);
  return 0;
}
