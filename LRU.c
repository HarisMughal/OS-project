#include<stdio.h>

int main(){
	int numPages , i , numberFrames;
	
	printf("Input number of frames\n");
	scanf("%d",&numberFrames);
	
	int frames[numberFrames]  , pageFaults = 0;
	
	printf("Input number of pages \n" );
	scanf("%d" , &numPages);
	
	int pages[numPages] , j , k;
	
	printf("Input pages number\n" );
	
	for (i = 0 ; i < numPages ; i++){
		scanf("%d",&pages[i]);
		if(i < numberFrames ){
			frames[numberFrames - i -1] = pages[i];
			pageFaults++;
		}
		
	}
	int swap;
	for(i = numberFrames ; i < numPages ; i++){
		printf("\n");
		//framePtr = (framePtr + 1) % numberFrames;
		for(j = 0 ; j < numberFrames ; j++){
			if(frames[j] == pages [i]){

				for(k = j ; k >= 1 ; k--)
				{
					swap = frames[k-1];
					frames[k-1] = frames[k];
					frames[k] = swap;
				}
				break;
			}
			else{
				if(j + 1 == numberFrames){
					for(k = numberFrames - 2; k >=0 ; k-- ){
						frames[k+1] = frames[k];
					}
					frames[0] = pages[i];
					pageFaults++;
					for(j = 0 ; j < numberFrames ; j++){
						printf("|%d|",frames[j]);
					}
				}
			}
		}
		
	}
	
	printf("\nNumber of page faults occoured is %d\n", pageFaults);
}
