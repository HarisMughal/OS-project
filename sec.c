#include<stdio.h>

int main(){
	int numPages , i , numberFrames;
	
	printf("Input number of frames\n");
	scanf("%d",&numberFrames);
	
	int frames[numberFrames] , pageFaults = 0 , table[100][3];
	
	printf("Input number of pages \n" );
	scanf("%d" , &numPages);
	
	int pages[numPages] , j , k;
	
	printf("Input pages number\n" );
	
	for (i = 0 ; i < numPages ; i++){
		scanf("%d",&pages[i]);
		if(i < numberFrames ){
			frames[i] = pages[i];
			table[ frames[i] ][0] = i;	// index of frame
			table[ frames[i] ][1] = 1;	// refrence bit
			table[ frames[i] ][2] = 1;	// is used by memorey?
			pageFaults++;
		}
		
	}
	int swap , index = 0;
	for(i = numnberFrames ; i < numPages ; i++){
		for(j = 0 ; j < numberFrames ; j++){	/// if is in frame the st refrence bit to 1
			if(frames[j] == pages [i]){
				table[ frames[j] ][1] = 1;
				break;
			}
			else if(j + 1 == numberFrames){
				while(1){
					if(table[ frames[index] ][1] == 1){	// change reference bit to 0 
						table[ frames[index] ][1] = 0;
					}
					else{		// if refernce bit is 0 replace it !

						table[ frames[index] ] [2] = 0;
						table[ frames[index] ] [0] = -1;
						frames [index] = pages[i];
						table[ frames[index] ] [0] = index;
						table[ frames[index] ] [1] = 1;
						table[ frames[index] ] [2] = 1;
						index = index+1 % numberFrames;
						break;
					}
					index = (index+1) % numberFrames;
				}
				for(swap = 0 ; swap < numberFrames ; swap++){
						printf("|%d|",frames[swap]);
				}
				printf("\n");
				pageFaults++;
	
			}
			
		}
		
	}
	
	printf("Number of page faults occoured is %d\n", pageFaults);
}
