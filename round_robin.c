#include<stdio.h>

void  sort(int arivalTime[],int burstTime[],int numPros) {

    int   c, d, swap,hold;
    for (c = 0 ; c < ( numPros - 1 ); c++)
    {
        for (d = 0 ; d < numPros - c - 1; d++)
        {
            if (arivalTime[d] > arivalTime[d+1]) 
            {
                swap       = arivalTime[d];
                arivalTime[d]   = arivalTime[d+1];
                arivalTime[d+1] = swap;

                hold = burstTime[d];
                burstTime[d] = burstTime[d+1];
                burstTime[d+1]= hold;
            }
        }
    }
}


void findWaitingTime(int numPros,int burstTime[], int waitingTime[], int arivalTime[],int quantum)
{

    int remainingBurst[numPros] , complete=numPros;
    int i;
    for (i = 0 ; i < numPros ; i++)
        remainingBurst[i] =  burstTime[i];

    int completionTime = 0;
    i=0;

    while(complete>0)
    {
        if(i==numPros)
            i=0;

        if (remainingBurst[i] > 0 && arivalTime[i]<=completionTime)
        {
            if (remainingBurst[i] > quantum)
            {

                completionTime += quantum;
                remainingBurst[i] -= quantum;
            }

            else
            {
                completionTime = completionTime + remainingBurst[i];
                waitingTime[i] = completionTime - burstTime[i]-arivalTime[i];
                remainingBurst[i] = 0;
                complete--;
            }
        }

        if(arivalTime[i]>=completionTime) {
            completionTime++;
            i--;
        }
        i++;
    }
}

void findTurnAroundTime(int numPros,
                        int burstTime[], int waitingTime[], int turnAroundTime[])
{
    int i;
    for ( i = 0; i < numPros ; i++)
        turnAroundTime[i] = burstTime[i] + waitingTime[i];
}

void findavgTime(int numPros, int burstTime[],int arivalTime[],int quantum)
{
    int waitingTime[numPros], turnAroundTime[numPros], totalWait = 0, totalTurn = 0;

    findWaitingTime(numPros, burstTime, waitingTime, arivalTime,quantum);

    findTurnAroundTime(numPros, burstTime, waitingTime, turnAroundTime);

    printf("Processes\t\tarrival time\t\tBurst time\t\tWaiting time\t\tTurn aroundtime\n") ;

    int i;
    for ( i=0; i<numPros; i++)
    {
        totalWait = totalWait + waitingTime[i];
        totalTurn = totalTurn + turnAroundTime[i];
        printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\n", i+1 ,arivalTime[i], burstTime[i] ,waitingTime[i] ,turnAroundTime[i]) ;
    }
    float x = (float)totalWait / numPros;
    printf ("\nAverage waiting time =%f",x);

    float y = (float)totalTurn / (float)numPros;
    printf ("\nAverage turn around time =%f",y);

}

int main()
{
    int numPros;
    printf("enter # of process \n");
    scanf("%d",&numPros);

    int burstTime[numPros];
    int arivalTime[numPros];
    printf("enter arrival time \n");
    int i;

    for( i=0; i<numPros; i++)
    {
        printf("id %d  ",i+1);
        scanf("%d",&arivalTime[i]);
        if(arivalTime[i] < 0 ){
        	printf("The arival time  can not be negative\nPlease Input again\n ");
        	i--;
		}
        printf("\n");
    }

    printf("enter burst time \numPros");

    for( i=0; i<numPros; i++)
    {
        printf("id %d  ",i+1);
        scanf("%d",&burstTime[i]);
		if(burstTime[i] <= 0 ){
        	printf("The burts time  can not be less than 0\nPlease Input again\n ");
        	i--;
		}        
        printf("\n");
    }

    sort(arivalTime,burstTime,numPros);

    int quantum;
    printf("enter quantum time\n");
    scanf("%d",&quantum)  ;

    findavgTime(numPros, burstTime, arivalTime,quantum);
    return 0;
}
