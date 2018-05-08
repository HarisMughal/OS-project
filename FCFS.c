#include<stdio.h>

void waitingTimeFind(int num, int burstTime[],int waitingTime[], int arivalTime[])
{
    int workingTime[num];
    workingTime[0] = 0;
    waitingTime[0] = 0;
    int i;
    for ( i = 1; i < num ; i++)
    {
        workingTime[i] = workingTime[i-1] + burstTime[i-1];

        waitingTime[i] = workingTime[i] - arivalTime[i];

        if (waitingTime[i] < 0)
            waitingTime[i] = 0;
    }
}

void findTurnAroundTime(int num, int burstTime[],
                        int waitingTime[], int turnAroundTime[])
{
    int i;
    for ( i = 0; i < num ; i++)
        turnAroundTime[i] = burstTime[i] + waitingTime[i];
}

void findavgTime(int num, int burstTime[], int arivalTime[])
{
    int waitingTime[num], turnAroundTime[num];

    waitingTimeFind(num, burstTime, waitingTime, arivalTime);

    findTurnAroundTime(num, burstTime, waitingTime, turnAroundTime);
    printf("process Arrival Time Burst time Waiting time Turn around time\n");

    int totalWatingTime = 0, totalTurnAroundTime = 0;
    int i;
    for ( i = 0 ; i < num ; i++)
    {
        totalWatingTime = totalWatingTime + waitingTime[i];
        totalTurnAroundTime = totalTurnAroundTime + turnAroundTime[i];
        int completionTime = turnAroundTime[i] + arivalTime[i];
        printf("  %d\t\t%d\t\t%d\t\t%d\t\t%d\n",i+1 ,arivalTime[i],burstTime[i],waitingTime[i],turnAroundTime[i]);

    }

    float avgWait=  (float)totalWatingTime /num;
    printf( "\nAverage waiting time =%f\n",avgWait);

    float avgTurn = (float)totalTurnAroundTime / num;
    printf( "Average turn around time = %f",avgTurn);

}
int main()
{

    int num;

    printf("enter number of process\n");
    scanf("%d",&num);
    int burstTime[num] ;
    int arivalTime[num];

    int i;
    for(i = 0; i < num; i++)
    {

        printf("\n Enter information of %d:\n",  i+1);

        printf("Enter Arrival Time:\t");
        scanf("%d", &arivalTime[i] );


        printf("Enter Burst Time:\t");
        scanf("%d", &burstTime[i]);
        if(burstTime[i] <= 0 ){
        	printf("The burst time  can only be a positive integer\nPlease Input again\n ");
        	i--;
		}else if(arivalTime[i] < 0){
			printf("The arival time  can not be negative\nPlease Input again\n ");
        	i--;
		}


    }


    findavgTime(num, burstTime, arivalTime);

    return 0;
}


