
# Noah Smith smit1988
# Vikram Manja vmanja





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int GetTime(float LamOrServ);



int GetTime(float LamOrServ)
{
  double X = (double)rand()/ RAND_MAX; // Generates X value between 0 and 1
  int R0 = ceil(-(1/LamOrServ) * log(1-X));  // Generates IA time R value
  return R0;
}







int main (int argc, char ** argv)

{

 int TasksRemain = 0;
  int NumberofLines = 2;
  int TasksRemain0 = 2;
  int TasksRemain1 = 2;
  float Lambda0, Lambda1, AvgServiceTime;
  FILE * fp2;
  char buffer[1024];
  fp2 = NULL;
  Lambda0 = 0;
  Lambda1 = 0;
  AvgServiceTime = 0;

  if (argc > 2)  // MODE 1
    {
      Lambda0 = atof(argv[1]);
      Lambda1 = atof(argv[2]);
      AvgServiceTime = atof(argv[3]);

      TasksRemain = atoi(argv[4]);
      TasksRemain0 = TasksRemain;
      TasksRemain1 = TasksRemain;
    }

 /* if (argc ==2) 
    {
      fp2 = fopen(argv[1], "r");

      while (feof(fp2) == 0)
	{
	  fgets(buffer,1023,fp2);
	  TasksRemain++;
	}
      TasksRemain--;
      fseek(fp2, 0, SEEK_SET); // fp2 @ beginning of file
      NumberofLines = TasksRemain;
    }
*/

   // DECLARATIONS
   
    int Service_Array[NumberofLines];
  int Arrival_Counter;
  Arrival_Counter = 0;
  Service_Array[0] = 0;

  FILE * fp;
  int Server = 64, Queue_0 = 0, Queue_1 = 0, i,j, k, r = 0, NumberOfTimes, a =0, b =0, c =0;
      
  int QueueLength = 0;
  double swap1 = 0, swap2 = 0, swap3 =0;
  double time = 0, start_time = 0, ServiceTimeStart = 0, AverageCPU = 0;
  double CumulWaitingTime1 = 0, CumulWaitingTime0 = 0;
  double Previous_T = 0, Previous_Queue0 = 0, Previous_Queue1 = 0;



   double FEL[TasksRemain * 2][2] ; // Future events list

   double Current_FEL[68][2];      // Current Events list

   double Queue_List [TasksRemain * 2][3]; // Current Queue


   



  // INITIALIZING FEL TABLE
   for(i = 0; i  TasksRemain * 2 ; i++)
    {       
      FEL[i][0] = 2;
      FEL[i][1] = -1;
      Queue_List[i][0] = 2;
      Queue_List[i][1] = -1;
      Queue_List[i][2] = 65;
     
    }

  // INITIALLIZING CURRENT_FEL
    if (argc > 2)
    {
      FEL[0][0] = 0; /
      FEL[0][1] = 0;
      FEL[1][0] = 1;
      FEL[1][1] = 0;

      TasksRemain1--;
      TasksRemain0--; // Decrementing # arrivals
    }


  start_time = time;
  ServiceTimeStart = time;

  //BEGINNING OF WHILE LOOP
  while( ( (TasksRemain0 > 0) || (TasksRemain1 > 0) ) && (NumberofLines > 0) ) // Need condition for mode2
    {
      //Check for all of the current time events
      NumberOfTimes = 0;//Current number of time events
      for(i = 0; i < TasksRemain * 2; i++)
	{
	  if(FEL[i][1] == time)
	    {
	      //Copy one line of the FEL to the Current_FEL
	      Current_FEL[NumberOfTimes][0] = FEL[i][0];
	      Current_FEL[NumberOfTimes][1] = FEL[i][1];
	     
	      NumberOfTimes++;
	    }
	}



	 if(NumberOfTimes != 0)//probably unnecessary
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
			  Server++;

		      for (b = 0; b < (TasksRemain * 2); b++)  // SORTING QUEUE_LIST by time
				{
				  for (c = b + 1; c < (TasksRemain * 2); c++)
				    {
				      if (Queue_List[b][1] > Queue_List[c][1]) 
					{
					  swap1 =  Queue_List[b][1];
					  swap2 = Queue_List[b][0];
					  swap3 = Queue_List[b][2];
					  Queue_List[b][1] = Queue_List[c][1];
					  Queue_List[b][0] = Queue_List[c][0];
					  Queue_List[b][2] = Queue_List[c][2];
					  Queue_List[c][1] = swap1;
					  Queue_List[c][0] = swap2;
					  Queue_List[c][2] = swap3;
					}
				    }
				}

				 c=0;

				 for (a = 0; a < (TasksRemain * 2); a++) 

				 {

				 	if (Queue_List[a][0] == c ) //if priority c 
				 	{
				 		if (Queue_List[a][2] <= Server ) // if it can be serviced
				 		{
				 			Server -= Queue_List[a][2];
				 			if (c ==0){Queue_0--;}
				 			if (c ==1){Queue_1--;}

				 			for (b =0; b < Queue_List[a][2]; b++) // generate departure time for subtasks
				 			{
				 				 r = 0;
							     while (FEL[r][1] >= time)
								 {
								  r++;
								 }
							      if(argc > 2)
								 {
								  FEL[r][1] = time + GetTime(AvgServiceTime);
								  FEL[r][0] = -1;
								 }          
				 			}
				 		Queue_List[a][0] = 2;
				 		Queue_List[a][1] = -1;
				 		Queue_List[a][2] = 65;

				 		}
				 	}
				 	if((c==0) && (a==((TasksRemain*2)-1)))
				 	{
				 		c=1;
				 		a=-1;

				 	}

				 } 

							  	
		    }

		      else if(i == 0) // PRIORITY 0 ARRIVAL
			{
     	     r = 0;
		     while (Queue_List[r][1] != -1)
			 {
			  r++;       //finds garbage in Quelist
			 }

		    Queue_List[r][0] = 0;
		    Queue_List[r][1] = time;
		    Queue_List[r][2] = rand() % 32 + 1;

		    Queue_0++;		

			   for (b = 0; b < (TasksRemain * 2); b++)  // SORTING QUEUE_LIST by time
				{
				  for (c = b + 1; c < (TasksRemain * 2); c++)
				    {
				      if (Queue_List[b][1] > Queue_List[c][1]) 
					{
					  swap1 =  Queue_List[b][1];
					  swap2 = Queue_List[b][0];
					  swap3 = Queue_List[b][2];
					  Queue_List[b][1] = Queue_List[c][1];
					  Queue_List[b][0] = Queue_List[c][0];
					  Queue_List[b][2] = Queue_List[c][2];
					  Queue_List[c][1] = swap1;
					  Queue_List[c][0] = swap2;
					  Queue_List[c][2] = swap3;
					}
				    }
				}

				c = 0 ;
		     for (a = 0; a < (TasksRemain * 2); a++) 

				 {

				 	if (Queue_List[a][0] == c ) //if priority c 
				 	{
				 		if (Queue_List[a][2] <= Server ) // if it can be serviced
				 		{
				 			Server -= Queue_List[a][2];
				 			if (c ==0){Queue_0--;}
				 			if (c ==1){Queue_1--;}

				 			for (b =0; b < Queue_List[a][2]; b++) // generate departure time for subtasks
				 			{
				 				 r = 0;
							     while (FEL[r][1] >= time)
								 {
								  r++;
								 }
							      if(argc > 2)
								 {
								  FEL[r][1] = time + GetTime(AvgServiceTime);
								  FEL[r][0] = -1;
								 }          
				 			}
				 		Queue_List[a][0] = 2;
				 		Queue_List[a][1] = -1;
				 		Queue_List[a][2] = 65;

				 		}
				 	}
				 	if((c==0) && (a==((TasksRemain*2)-1)))
				 	{
				 		c=1;
				 		a=-1;
				 	}

				 } 

		 r = 0;
	    while (FEL[r][1] >= time)
		{
		  r++;
		}
	      
		
	    FEL[r][1] = time + GetTime(Lambda0);
		FEL[r][0] = 0;
		TasksRemain0--;
		
					  	
		    } // i = 0

			





		      else
			{
			
     	     r = 0;
		     while (Queue_List[r][1] != -1)
			 {
			  r++;
			 }

		    Queue_List[r][0] = 1;
		    Queue_List[r][1] = time;
		    Queue_List[r][2] = rand() % 32 + 1;

		    Queue_1++;		

			   for (b = 0; b < (TasksRemain * 2); b++)  // SORTING QUEUE_LIST by time
				{
				  for (c = b + 1; c < (TasksRemain * 2); c++)
				    {
				      if (Queue_List[b][1] > Queue_List[c][1]) 
					{
					  swap1 =  Queue_List[b][1];
					  swap2 = Queue_List[b][0];
					  swap3 = Queue_List[b][2];
					  Queue_List[b][1] = Queue_List[c][1];
					  Queue_List[b][0] = Queue_List[c][0];
					  Queue_List[b][2] = Queue_List[c][2];
					  Queue_List[c][1] = swap1;
					  Queue_List[c][0] = swap2;
					  Queue_List[c][2] = swap3;
					}
				    }
				}

				c = 0 ;
		     for (a = 0; a < (TasksRemain * 2); a++) 

				 {

				 	if (Queue_List[a][0] == c ) //if priority c 
				 	{
				 		if (Queue_List[a][2] <= Server ) // if it can be serviced
				 		{
				 			Server -= Queue_List[a][2];
				 			if (c ==0){Queue_0--;}
				 			if (c ==1){Queue_1--;}

				 			for (b =0; b < Queue_List[a][2]; b++) // generate departure time for subtasks
				 			{
				 				 r = 0;
							     while (FEL[r][1] >= time)
								 {
								  r++;
								 }
							      if(argc > 2)
								 {
								  FEL[r][1] = time + GetTime(AvgServiceTime);
								  FEL[r][0] = -1;
								 }          
				 			}
				 		Queue_List[a][0] = 2;
				 		Queue_List[a][1] = -1;
				 		Queue_List[a][2] = 65;

				 		}
				 	}
				 	if((c==0) && (a==((TasksRemain*2)-1)))
				 	{
				 		c=1;
				 		a=-1;
				 	}

				 } 

		 r = 0;
	    while (FEL[r][1] >= time)
		{
		  r++;
		}
	      
		
	    FEL[r][1] = time + GetTime(Lambda1);
		FEL[r][0] = 1;
		TasksRemain1--;
		
					  	
		    } // i = 1
			
		    } //?
		  } //?
	    } //? 
	  }     //?

	    //Sort FEL
      for (i = 0; i < (TasksRemain * 2); i++)
	{
	  for (j = i + 1; j < (TasksRemain * 2); j++)
	    {
	      if (FEL[i][1] > FEL[j][1])
	   	 {
		  swap1 =  FEL[i][1];
		  swap2 = FEL[i][0];
		  FEL[i][1] = FEL[j][1];
		  FEL[i][0] = FEL[j][0];
		  FEL[j][1] = swap1;
		  FEL[j][0] = swap2;
		 }
	
	    }
	}

    
     r = 0;
      while (FEL[r][1] <= time)
	{
	  r++;
	  if(r == (TasksRemain * 2 - 1))
	    break;
	}
      //last value
      time = FEL[r][1];
    }

    


    } //END of while loop
}     // End of main
