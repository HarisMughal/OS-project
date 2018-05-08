#include<stdio.h>
 
struct process
{
      char processName;
      int arivalTime, burstTime, completionTime, waitingTime, turnAroundTime, priority;
      int status;
};
 
void main()
{
	int numPros;
	 int i, currentTime = 0, burstTime = 0, largest;
      char c;
      float totalWait = 0, turnAroundTime = 0, avgWait, avgTurn;
      
	  printf("\nEnter Total Number of Processes:\t");
	  scanf("%d", &numPros);
	  struct process information[numPros + 1];
	  for(i = 0, c = 'A'; i < numPros; i++, c++)
      {
            information[i].processName = c;
            
			printf("\n Enter information of [%C]:\n", information[i].processName);
            
			printf("Enter Arrival Time:\t");
            scanf("%d", &information[i].arivalTime );
            
			printf("Enter Burst current Time:\t");
            scanf("%d", &information[i].burstTime);
            if(information[i].burstTime <= 0 ){
        		printf("The burst time  can only be a positive integer\nPlease Input again\n ");
        		i--;
        		c--;
        		continue;
			}else if(information[i].arivalTime < 0){
				printf("The arival time  can not be negative\nPlease Input again\n ");
        		i--;
        		c--;
        		continue;
			}            
            
			printf("Enter priority:\t");
            scanf("%d", &information[i].priority);
            
			information[i].status = 0;
      }
      
      struct process temp;
      int  j;
      for(i = 0; i < numPros - 1; i++)
      {
            for(j = i + 1; j < numPros; j++)
            {
                  if(information[i].arivalTime > information[j].arivalTime)
                  {
                        temp = information[i];
                        information[i] = information[j];
                        information[j] = temp;
                  }
            }
      }
      int burst[numPros];
      for(i = 0 ; i < numPros ; i ++)
      	burst[i] = information[i].burstTime;
	  information[numPros].priority = -9999;
	  printf("\nID\tarrival Time\tburst Time\tpriority Time\twaiting Time");
	  int n = numPros  , use = 0;
	  currentTime = 0 ;
      while(n > 0)
      {
            largest = numPros;
            for(i = 0; i < numPros ; i++)
            {
                  if(information[i].arivalTime <= currentTime && information[i].status != 1 && information[i].priority > information[largest].priority)
                  {
                        largest = i;
                        use = i;
                  }
            }
            if(information[use].burstTime > 0 && information[use].arivalTime <= currentTime){
            	burst[use]--;
            	if(burst[use] == 0){
            		information[use].completionTime = currentTime + 1;
            		information[use].turnAroundTime = information[use].completionTime - information[use].arivalTime;
            		information[use].waitingTime = information[use].turnAroundTime - information[use].burstTime;
            		if(information[use].waitingTime < 0 )
            			information[use].waitingTime = 0;
            		information[use].status = 1;
            		n--;
            		totalWait = totalWait + information[use].waitingTime;
            		turnAroundTime = turnAroundTime + information[use].turnAroundTime;
				}
			} 

            currentTime++;            
            
            
            
            
            
      }
      for(i = 0 ; i < numPros ; i++)
      	printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d", 
			information[i].processName, information[i].arivalTime, information[i].burstTime, information[i].priority, information[i].waitingTime);
      avgWait = totalWait / numPros;
      avgTurn = turnAroundTime / numPros;
      printf("\n\nAverage waiting Time:\t%f\n", avgWait);
      printf("Average Turnaround Time:\t%f\n", avgTurn);
  }
