#include<stdio.h>

int main(){
	int numPages , i , numberFrames ;
	printf("Input number of frames\n");
	scanf("%d",&numberFrames);
	int frames[numberFrames] , framePtr = 0 , pageFaults = 0;
	printf("Input number of pages \n" );
	scanf("%d" , &numPages);
	int pages[numPages] , j;
	printf("Input pages number\n" );
	for (i = 0 ; i < numPages ; i++){
		scanf("%d", &pages[i]);
		if(i < numberFrames ){
			frames[i] = pages[i];
			pageFaults++;
		}
	}
	for(i = numberFrames ; i < numPages ; i++){
		for(j = 0 ; j < numberFrames ; j++){
			if(frames[j] == pages[i]){
				break;
			}
			else{
				if(j + 1 == numberFrames){
					pageFaults++;
					frames[framePtr] = pages[i];
					for(j = 0 ; j < numberFrames ; j++){
						printf("|%d|",frames[j]);
					}
					printf("\n");
					framePtr = (framePtr + 1) % numberFrames;
				}
			}
		}
	}
	printf("Number of page faults occoured is %d\n", pageFaults);
	
	
	
	
	
}
