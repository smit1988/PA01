//PA02
//Noah Smith
//9/9/2014

#include "answer02.h"

size_t my_strlen(const char * str)
{
  char * x;
  for(x = (char *) str; *x != '\0'; x++);
  return (x - str);
}

int my_countchar(const char * str, char ch)
{
  char * x;
  int count = 0;
  for(x = (char *) str; *x != '\0'; x++)
    {
      if(*x == ch)
	count++;
    }
  return count;
}

char * my_strchr(const char * str, int ch)
{
  char * x;
  //Search until end of string
  for(x = (char *) str; *x != '\0'; x++)
    {
      if(*x == ch)
	return x;
    }
  //Catch null value
  if(ch == '\0')
    return x;
  return NULL;
}

char * my_strrchr(const char * str, int ch)
{
  char * x;
  //Point to end of string
  for(x = (char *) str; *x != '\0'; x++);
  //Point to ch or at beginning of string
  for(x; *x != ch && x != (char *) str; x--);
  //Catch beginning of string
  if(*x == ch)
    return x;
  return NULL;
}
