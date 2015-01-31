#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>




int main(int argc, char ** argv)

{
  
  if (argc > 2)  // MODE 1
    {
      float Lambda0, Lambda1, AvgServiceTime, NumberOfTasks;

      Lambda0 = atof(argv[1]);
      Lambda1 = atof(argv[2]);
      AvgServiceTime = atof(argv[3]);
      NumberOfTasks = atof(argv[4]);

      int Server = 0, Queue_0 = 0, Queue_1 = 0, time = 0, i, k, NumberOfTimes;
      int TasksRemain = atoi(argv[4]);
      //FEL take numberoftasks * 5
      //FEL will be int array with 2 arguments: event (0 arrival,1 arrival,-1 departure, 
      //2 executed) and time
      int FEL[TasksRemain * 5][2];
      int Current_FEL[TasksRemain * 5][2]; //array of all the current time events

      while(TasksRemain > 0)
	{
	  //Check for all of the current time events
	  NumberOfTimes = 0;//Current number of time events
	  for(i = 0; i <= NumberOfTasks * 5 - 1; i++)
	    {
	      if(FEL[i][1] == time)
		{
		  //Copy one line of the FEL to the Current_FEL
		  Current_FEL[NumberOfTimes][0] = FEL[i][0];
		  Current_FEL[NumberOfTimes][1] = FEL[i][1];
		  NumberOfTimes++;
		}
	    }
	  //At this point Current_FEL contains all the time events, there are NumberOfTimes

	  if(NumberOfTimes != 0)
	    {
	      //Departures > priorities > nonpriorities
	      //After an event, change Current_FEL[x][0] to 2
	      for(i = -1; i <= 1; i++)//Look in order
		{
		  for(k = 0; k < NumberOfTimes; k++)//Go through all looking for i
		    {
		      if(Current_FEL[k][0] == i)
			{
			  //Do the event corresponding to i
			  if(i == -1)
			    {
			      //departure
			    }
			  else if(i == 0)
			    {
			      //priority
			    }
			   else
			     {
			       //nonpriority
			     }
			}
		    }
		}

	    }
	}
      

      //printf("%f %f %f %f", Lambda0, Lambda1, AvgServiceTime, NumberOfTasks);
    } 
    
  return 0;

}
