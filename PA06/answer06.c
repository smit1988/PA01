#include "answer06.h"
#include <stdio.h>

//See how much whitespace is left, if 0 then head towards entrance
//Check to see if you are currently on the edge of the maze, don't look past it if so
//Set current position to Traveled and look around for whitespace
//Arbitrarily go west, then south, then east if multiple whitespace
//Remember where crossroads are, return to later on
//Something about loops (maybe will work itself out if running into mowed space is same as running into a wall)
//Deadend, retrace steps to last crossroad
//Determined there is no whitespace left, head towards the entrance

void mower(char ** maze, int row, int column, int whitespace);

void print_directions(char** maze, int w, int h) {
  //Count the initial whitespace
    int whitespace = 0;
    int count, count_two, entrance,row,column;
    for(count = 0; count < h; count++)
    {
      for(count_two = 0; count_two < w; count_two++)
	{
	  if(maze[count][count_two] == SPACE)
	    {
	      whitespace++;
	      //Register entrance
	      if(count == 0)
		entrance = count_two;
	    }
	}
    }
    //Set mower to entrance
    row = 0;
    column = entrance;
    mower(row, column, whitespace);
}

void mower(char ** maze, int row, int column, int whitespace){
  //Set current position to traveled
  maze[row][column] = TRACK;
  //Decrease number of whitespace
  whitespace--;
  //Don't look past maze
  //Look for whitespace
  if(column != 0)
    {
      if(maze[row][column - 1] == SPACE)
	{
	  //There's a space to the left
	  printf("W 1\n");
	  mower(row,column - 1);
	  printf("E 1\n");
	}
    }
  if(row != h)
    {
      if(maze[row + 1][column] == SPACE)
	{
	  //There's a space down
	  printf("S 1\n");
          mower(row + 1,column);
          printf("N 1\n");  
	}
    }
  if(column != w)
    {
      if(maze[row][column + 1] == SPACE)
	{
	  //There's a space to the right
	  printf("E 1\n");
          mower(row,column + 1);
          printf("W 1\n");
	}
    }
  if(row != 0)
    {
      if(maze[row - 1][column] == SPACE)
	{
	  //There's a space up
	  printf("N 1\n");
          mower(row - 1,column);
          printf("S 1\n");
	}
    }
}
