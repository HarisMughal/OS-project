#include <stdio.h>


typedef struct pros {
    int id;
    int burstTime;
    int arivalTime;
};

void waitingTimeFunc(struct pros proc[], int num,int waitingTime[])
{
    int remainingTime[num];

    int i;
    for ( i = 0; i < num; i++)
        remainingTime[i] = proc[i].burstTime;

    int current = 0, currnetTime = 0, mini = 1000;
    int shortest = 0, endTime;
    int checker = 0;

    while (current != num) {

        int j;
        for ( j = 0; j < num; j++) {
            if ((proc[j].arivalTime <= currnetTime) &&
                    (remainingTime[j] < mini) && remainingTime[j] > 0) {
                mini = remainingTime[j];
                shortest = j;
                checker = 1;
            }
        }

        if (checker == 0) {
            currnetTime++;
            continue;
        }

        remainingTime[shortest]--;

        mini = remainingTime[shortest];
        if (mini == 0)
            mini = 100000;

        if (remainingTime[shortest] == 0) {

            current++;

            endTime = currnetTime + 1;

            waitingTime[shortest] = endTime -  proc[shortest].burstTime - proc[shortest].arivalTime;

            if (waitingTime[shortest] < 0)
                waitingTime[shortest] = 0;
        }
        currnetTime++;
    }
}

void findTurnAroundTime(struct pros proc[], int num,
                        int waitingTime[], int turnAroundTime[])
{

    int i;
    for ( i = 0; i < num; i++)
        turnAroundTime[i] = proc[i].burstTime + waitingTime[i];
}

void findAvgTime(struct pros proc[], int num)
{
    int waitingTime[num], turnAroundTime[num], totalWaitingTime = 0, totalTurnAroundTime = 0;

    waitingTimeFunc(proc, num, waitingTime);

    findTurnAroundTime(proc, num, waitingTime, turnAroundTime);

    printf("Processes Arrival Time Burst time Waiting time Turn around time\n");

    int i;
    for (i = 0; i < num; i++) {
        totalWaitingTime = totalWaitingTime + waitingTime[i];
        totalTurnAroundTime = totalTurnAroundTime + turnAroundTime[i];

        printf("  %d\t\t%d\t\t%d\t\t%d\t\t%d\num\n",proc[i].id ,proc[i].arivalTime,proc[i].burstTime,waitingTime[i],turnAroundTime[i]);
    }

    float avgWait =  (float)totalWaitingTime /num;
    printf( "Average waiting time =%f\n",avgWait);

    float avgTurn = (float)totalTurnAroundTime / num;
    printf( "Average turn around time = %f\n",avgTurn);

}

int main()
{
    int num;
    printf("enter number of process\n");
    scanf("%d",&num);
    struct	pros proc[num] ;
    int i;
    for(i = 0; i < num; i++)
    {
        proc[i].id = i ;

        printf("\n Enter information of %d:\n", proc[i].id);

        printf("Enter Arrival Time:\t");
        scanf("%d", &proc[i].arivalTime );


        printf("Enter Burst Time:\t");
        scanf("%d", &proc[i].burstTime);
        if(proc[i].burstTime <= 0 ){
        	printf("The burst time  can only be a positive integer\nPlease Input again\n ");
        	i--;
        	continue;
		}else if(proc[i].arivalTime < 0){
			printf("The arival time  can not be negative\nPlease Input again\n ");
        	i--;
        	continue;
		}            
                    


    }
    findAvgTime(proc, num);
    return 0;
}
