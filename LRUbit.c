#include<stdio.h>
#include <pthread.h>
#include<unistd.h>

static int lock = 1 , bit = 1 ,size;

void signal();
void wait();
void* changer(void* frame);
int main(){
	int numPages , i , numberFrames;
	
	printf("Input number of frames\n");
	scanf("%d",&numberFrames);
	size = numberFrames;
	int frames[numberFrames][2] , frameTop  = 0 , frameBottom = numberFrames - 1 , pageFaults = 0;
	
	printf("Input number of pages \n" );
	scanf("%d" , &numPages);
	
	int pages[numPages] , j , k;
	
	printf("Input pages number\n" );
	
	for (i = 0 ; i < numPages ; i++){
		scanf("%d",&pages[i]);
		if(i < numberFrames ){
			frames[i][0] = pages[i];
			frames[i][1] = 1;
			pageFaults++;
		}
		
	}
	int swap;
	pthread_t id;
	pthread_create(&id, 0, changer, (void*)&frames);
	for(i = numberFrames ; i < numPages ; i++){
		for(j = 0 ; j < numberFrames ; j++){
			wait();
			if(frames[j][0] == pages [i]){
				frames[j][1] = 1;
				signal();
				break;
			}
			else if(j + 1 == numberFrames){
				signal();
				sleep(1);
				wait();
				for(k = 0 ; k < numberFrames ; k++ ){
	
				if(frames[k][1] == 0){
						frames[k][0] = pages[i];
						frames[k][1] = 1;
						signal();
						break;
					}
				}
				pageFaults++;
				for(k = 0 ; k < numberFrames ; k++){
					printf("|%d|",frames[k][0]);
				}
				printf("\n");
			}
			signal();

		}
		
	}
	bit = 0;
	pthread_join(id,NULL);
	printf("Number of page faults occoured is %d\n", pageFaults);
}

void signal(){
	lock++;
}
void wait(){
	while(lock <=0 );
	lock--;
}
void* changer(void* frame){
	int (*att)[size][2] = frame;
	int i = 0 , j = 1;

	while(bit){
		sleep(0.05);
		wait();
		//printf("%d->%d\n",(*att)[i][0],(*att)[i][1]);
		(*att)[i][1]= 0;
		signal();
		i = (i+1) % size; 
		sleep(0.5);
	}
}
