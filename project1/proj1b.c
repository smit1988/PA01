// Noah Smith smit1988
// Vikram Manja vmanja





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>




typedef struct Nodes
{
  
  int priority;
  int Time;
  int subtasks;
  int Servicetimes[32];
  int Loadbalance;
  struct Nodes * next; 

} ArrivalNode;

typedef struct Nodes2
{
  int Time;
  struct Nodes2 * next;

} DepartureNode;

ArrivalNode * Arrival_createNode(FILE * filepointer);



int main (int argc, char ** argv) 
{

  int TasksRemain = 0;
  int NumberofLines = 2;
  FILE * fp2 = NULL;
  char buffer[1024];
  int i = 0;
  int simtime;
  int time;
  int j = 0;
  int newdeptime;
  int worked = 0;

  ArrivalNode Arrival_head;
  DepartureNode Departure_head;
  int Free_Servers = 64;

  ArrivalNode * ptr1 = NULL, * CurrentNode = NULL, * ptr2= NULL, * NextNode = NULL;
  DepartureNode * Dep_ptr1 = NULL, * Dep_ptr2 = NULL;

  int Indicator=0, QueueLenght0 = 0, QueueLenght1 = 0;
/*---------------------------Creating ARRIVAL NODE-----------------------------*/  
ArrivalNode * Arrival_createNode(FILE * filepointer)

{
  ArrivalNode * NewNode = malloc(sizeof(ArrivalNode));
  fscanf (filepointer, "%d %d %d " , &NewNode->Time, &NewNode->priority, &NewNode->subtasks);
  int I = 0;
  for (I = 0; I <  NewNode->subtasks; I++)
  {
    fscanf(filepointer, "%d", &NewNode->Servicetimes[I]);
  }
  //PUT IN Loadbalancing Calculations
  NewNode->next = NULL;
  printf("Creating Arrival node\n" );
  return NewNode;
}


  if ( argc == 2)
  {
   fp2 = fopen(argv[1], "r"); // opening file

      while (feof(fp2) == 0) // counting lines
	 {
	  fgets(buffer,1023,fp2);
	  TasksRemain++;
	 }
    
    TasksRemain--;
    fseek(fp2, 0, SEEK_SET); // fp2 @ beginning of file

    NumberofLines = TasksRemain;

    printf("Starting Node creation\n");
  /*-----------------------------------CREATING LINKED LIST OF ARRIVALS--------------------------------*/
    Arrival_head.next = Arrival_createNode(fp2);
    ptr1 = Arrival_head.next;

    printf("Created first node\n");
    for (i = 1; i < NumberofLines -1; i++)
    {
      ptr1->next = Arrival_createNode(fp2);
      ptr1 = ptr1->next; 
      printf("%d", ptr1->Time);
    }

    
    
    //Initializing Times
    
    CurrentNode = Arrival_head.next;
    simtime = CurrentNode->Time;
    time = CurrentNode->Time;
    Departure_head.next = NULL;
/*************************************************--------------------WHILE LOOP-----------------------------******************/

    while ( (Arrival_head.next != NULL) || (Departure_head.next != NULL) ) //while departures/arrivals still exist
    {
      
    printf("WHILE\n");

    /*----------------------DEPARTURES---------------------------*/
      if (Departure_head.next != NULL) // Look for departures if they exist
      { 

        while ( (Departure_head.next)->Time == time) //If departures occur, pop front node and increment freeservers
        { 
          Free_Servers++;
          Dep_ptr1 = Departure_head.next;
          Dep_ptr2 = Dep_ptr1->next;
          Departure_head.next = Dep_ptr2;
          //Dep_ptr1->next = NULL;
          //free(Dep_ptr1->next);
          free(Dep_ptr1);

          printf("DEPARTING\n");
        }
      }
   
    if (Arrival_head.next == NULL){time = (Departure_head.next)->Time; continue;}



      /*----------------------------------Check queuelist for priority 0----------------------------------*/
      ptr1 = &Arrival_head;
      //printf("%d\n",(ptr1->next)->Time);
      while ( (ptr1->next)->Time < time) // || ( ( Indicator < 0) && (CurrentNode->Time = time) ) )  
      {
        printf("checking 0\n");
        if ( (ptr1->next)->priority == 0)
        {
          printf("found 0\n");
          
         if ( (ptr1->next)->subtasks < Free_Servers)
         {
          ptr2 = ptr1->next;
          if (ptr2 == CurrentNode)
            { if(ptr2->Time != (ptr2->next)->Time ) 
              {
                CurrentNode = ptr1;
              } 
              else 
              {
                CurrentNode = CurrentNode->next;
              }
            }
          QueueLenght0--;
          Free_Servers = Free_Servers - ptr2->subtasks;
          Dep_ptr1 = &Departure_head;
           // CREATING DEPARTURE NODES
          for(i = 0; i < (ptr2->subtasks) ; i++)
          {
            worked = 0;
            Dep_ptr1 = &Departure_head;
            newdeptime = time + ptr2->Servicetimes[i];
            printf("%d\n", newdeptime );
            
            if (Dep_ptr1->next == NULL)        // if Departures empty
              {
               Dep_ptr1->next = malloc(sizeof(DepartureNode));
               Dep_ptr1 = Dep_ptr1->next;
               Dep_ptr1->Time = newdeptime;
               Dep_ptr1->next = NULL;
               continue;
              }

            // departures not empty

            while (Dep_ptr1->next != NULL)
            {
              if ( (Dep_ptr1->next)->Time > newdeptime)
              {
                Dep_ptr2 = Dep_ptr1->next;
                Dep_ptr1->next = malloc(sizeof(DepartureNode));
                Dep_ptr1 = Dep_ptr1->next;
                Dep_ptr1->next = Dep_ptr2;
                Dep_ptr1->Time = newdeptime;
                worked = 1;
                break;
              }
             }  

             if (worked == 1){continue;} 

              if (Dep_ptr1->next == NULL)        // if Departures empty
              {
               Dep_ptr1->next = malloc(sizeof(DepartureNode));
               Dep_ptr1 = Dep_ptr1->next;
               Dep_ptr1->Time = newdeptime;
               Dep_ptr1->next = NULL;
               continue;
              }


            }


            
          ptr1->next = ptr2->next;
          //free(ptr2->subtasks);
          free (ptr2); // Pop arrival node
          continue;         
         }
        }
        ptr1 = ptr1->next;
        //Indicator++;
      }
/*-----------------------------Check queuelist for priority 1------------------------------------*/
      ptr1 = &Arrival_head;
      while ( (ptr1->next)->Time < time) //|| (( Indicator < 1) && (CurrentNode->Time = time) ) ) 
 
      {
        printf("Checkin 1 \n");

        if ( (ptr1->next)->priority == 1)
        {
         printf("Found 1\n");
         if ( (ptr1->next)->subtasks < Free_Servers)
         {
          ptr2 = ptr1->next;
          if (ptr2 == CurrentNode){ if(ptr2->Time != (ptr2->next)->Time ) {CurrentNode = ptr1;} else {CurrentNode = CurrentNode->next;} }
          QueueLenght1--;
          Free_Servers = Free_Servers - ptr2->subtasks;
          Dep_ptr1 = &Departure_head;

           // CREATING DEPARTURE NODES
          for(i = 0; i < (ptr2->subtasks) ; i++)
          {
            worked = 0;
            Dep_ptr1 = &Departure_head;
            newdeptime = time + ptr2->Servicetimes[i];
            printf("%d\n", newdeptime );
            
            if (Dep_ptr1->next == NULL)        // if Departures empty
              {
               Dep_ptr1->next = malloc(sizeof(DepartureNode));
               Dep_ptr1 = Dep_ptr1->next;
               Dep_ptr1->Time = newdeptime;
               Dep_ptr1->next = NULL;
               continue;
              }

            // departures not empty

            while (Dep_ptr1->next != NULL)
            {
              if ( (Dep_ptr1->next)->Time > newdeptime)
              {
                Dep_ptr2 = Dep_ptr1->next;
                Dep_ptr1->next = malloc(sizeof(DepartureNode));
                Dep_ptr1 = Dep_ptr1->next;
                Dep_ptr1->next = Dep_ptr2;
                Dep_ptr1->Time = newdeptime;
                worked =1;
                break;
              }
             }  

                  if (worked == 1){continue;} 

              if (Dep_ptr1->next == NULL)        // if Departures empty
              {
               Dep_ptr1->next = malloc(sizeof(DepartureNode));
               Dep_ptr1 = Dep_ptr1->next;
               Dep_ptr1->Time = newdeptime;
               Dep_ptr1->next = NULL;
               continue;
              }


            }


            
          ptr1->next = ptr2->next;
          //free(ptr2->subtasks);
          free (ptr2); // Pop arrival node
          continue;         
         }
         }
        
        ptr1 = ptr1->next;
     //   Indicator++;
        
      }


      Indicator=5; // random positive int
      
      
  /* CHECK IF ARRIVAL(s) OCCURED  */
      if ((QueueLenght1==0) && (QueueLenght0 ==0)) { Indicator = 0;}  

      if (CurrentNode->Time == time){ if (CurrentNode->priority == 0) {QueueLenght0++;} if (CurrentNode->priority == 1){QueueLenght1++;} 
        if(Indicator==0){Indicator--;} }
      NextNode = CurrentNode->next;
      if (NextNode->Time == CurrentNode->Time) { CurrentNode = CurrentNode->next;  if (CurrentNode->priority == 0) {QueueLenght0++;} if (CurrentNode->priority == 1){QueueLenght1++;} 
        if(Indicator == -1){Indicator--;} }
      
      j = Indicator;    


       ptr1 = &Arrival_head;
     // printf("%d\n",(ptr1->next)->Time);
      while ( (ptr1->next)->Time <= time) // || ( ( Indicator < 0) && (CurrentNode->Time = time) ) )  
      {
        printf("checking 0\n");
        if ( (ptr1->next)->priority == 0)
        {
          printf("found 0\n");
          
         if ( (ptr1->next)->subtasks < Free_Servers)
         {
          ptr2 = ptr1->next;
          if (ptr2 == CurrentNode)
            { if(ptr2->Time != (ptr2->next)->Time ) 
              {
                CurrentNode = ptr1;
              } 
              else 
              {
                CurrentNode = CurrentNode->next;
              }
            }
          QueueLenght0--;
          Free_Servers = Free_Servers - ptr2->subtasks;
          Dep_ptr1 = &Departure_head;

          // CREATING DEPARTURE NODES
          for(i = 0; i < (ptr2->subtasks) ; i++)
          {
            worked = 0;
            Dep_ptr1 = &Departure_head;
            newdeptime = time + ptr2->Servicetimes[i];
            printf("%d\n", newdeptime );
            
            if (Dep_ptr1->next == NULL)        // if Departures empty
              {
               Dep_ptr1->next = malloc(sizeof(DepartureNode));
               Dep_ptr1 = Dep_ptr1->next;
               Dep_ptr1->Time = newdeptime;
               Dep_ptr1->next = NULL;
               continue;
              }

            // departures not empty

            while (Dep_ptr1->next != NULL)
            {
              if ( (Dep_ptr1->next)->Time >= newdeptime)
              {
                Dep_ptr2 = Dep_ptr1->next;
                Dep_ptr1->next = malloc(sizeof(DepartureNode));
                Dep_ptr1 = Dep_ptr1->next;
                Dep_ptr1->next = Dep_ptr2;
                Dep_ptr1->Time = newdeptime;
                worked = 1;
                break;
              }
              Dep_ptr1 = Dep_ptr1->next;
             }  

             if (worked == 1){continue;} 

              if (Dep_ptr1->next == NULL)        // if Departures empty
              {
               Dep_ptr1->next = malloc(sizeof(DepartureNode));
               Dep_ptr1 = Dep_ptr1->next;
               Dep_ptr1->Time = newdeptime;
               Dep_ptr1->next = NULL;
               continue;
              }


            }


            
          ptr1->next = ptr2->next;
          //free(ptr2->subtasks);
          free (ptr2); // Pop arrival node
          continue;         
         }

         }
        
        ptr1 = ptr1->next;
        //Indicator++;
      }
/*-----------------------------Check queuelist for priority 1------------------------------------*/
      ptr1 = &Arrival_head;
      while ( (ptr1->next)->Time <= time) //|| (( Indicator < 1) && (CurrentNode->Time = time) ) ) 
 
      {
        printf("Checkin 1 \n");

        if ( (ptr1->next)->priority == 1)
        {
         printf("Found 1\n");
         if ( (ptr1->next)->subtasks < Free_Servers)
         {
          ptr2 = ptr1->next;
          if (ptr2 == CurrentNode){ if(ptr2->Time != (ptr2->next)->Time ) {CurrentNode = ptr1;} else {CurrentNode = CurrentNode->next;} }
          QueueLenght1--;
          Free_Servers = Free_Servers - ptr2->subtasks;
          Dep_ptr1 = &Departure_head;
      // CREATING DEPARTURE NODES
          for(i = 0; i < (ptr2->subtasks) ; i++)
          {
            worked = 0;
            Dep_ptr1 = &Departure_head;
            newdeptime = time + ptr2->Servicetimes[i];
            printf("%d\n", newdeptime);
            
            if (Dep_ptr1->next == NULL)        // if Departures empty
              {
               Dep_ptr1->next = malloc(sizeof(DepartureNode));
               Dep_ptr1 = Dep_ptr1->next;
               Dep_ptr1->Time = newdeptime;
               Dep_ptr1->next = NULL;
               continue;
              }

            // departures not empty

            while (Dep_ptr1->next != NULL)
            {
              if ( (Dep_ptr1->next)->Time > newdeptime)
              {
                worked = 1;
                Dep_ptr2 = Dep_ptr1->next;
                Dep_ptr1->next = malloc(sizeof(DepartureNode));
                Dep_ptr1 = Dep_ptr1->next;
                Dep_ptr1->next = Dep_ptr2;
                Dep_ptr1->Time = newdeptime;
                break;
              }
              Dep_ptr1 = Dep_ptr1->next;
             }  

              if (worked == 1){continue;} 

              if (Dep_ptr1->next == NULL)        // if Departures empty
              {
               Dep_ptr1->next = malloc(sizeof(DepartureNode));
               Dep_ptr1 = Dep_ptr1->next;
               Dep_ptr1->Time = newdeptime;
               Dep_ptr1->next = NULL;
               continue;
              }


            }


            
          ptr1->next = ptr2->next;
          //free(ptr2->subtasks);
          free (ptr2); // Pop arrival node
          continue;         
          }         
         }
        
        ptr1 = ptr1->next;
     //   Indicator++;
        
      }








    printf("Time update\n");
/*-----------------------------Update time and the current arrival node--------------*/
  while ((CurrentNode->next)->Time <= time) {CurrentNode = CurrentNode->next;} // update current node    

  printf("Updated current node\n");

  if (Departure_head.next == NULL) 
  {
    CurrentNode=CurrentNode->next;
    time = CurrentNode->Time;
    printf(" Time = %d\n", time);
    continue;
  }

  printf("Update current node/time\n");

  if (  ((Departure_head.next)->Time) < ((CurrentNode->next)->Time) )
  {
    time = (Departure_head.next)->Time;
  }
      // update time
  else 
  {
    CurrentNode=CurrentNode->next;
    time = CurrentNode->Time;
  }


printf(" \nTime = %d\n\n", time);


    } // end of WHILE



   


    /* Testing
    ArrivalNode * Head = Arrival_createNode(fp2);
    ArrivalNode * Head2 = Arrival_createNode(fp2);

    printf(" %d %d %d %d %d \n", Head->Servicetimes[0], Head->Servicetimes[1], Head->Servicetimes[2],Head->Servicetimes[3], Head->Servicetimes[4] );
    printf(" %d %d %d %d %d \n", Head2->Servicetimes[0], Head2->Servicetimes[1], Head2->Servicetimes[2],Head2->Servicetimes[3], Head2->Servicetimes[4] );

    printf("%d %d %d", Head->Time, Head->priority, Head->subtasks);
   */


 







 } // end if argc ==2


if (argc == 2) 
{
 fclose(fp2);
}

  return 0;
}
