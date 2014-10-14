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

void print_directions(char** maze, int w, int h) {
  
}
