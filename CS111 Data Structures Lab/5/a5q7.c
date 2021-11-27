#include<stdio.h>
#include<stdlib.h>
void main(){
	int size,ob;
	printf("Enter the size:\n");
	scanf("%d",&size);
	int* arr=(int*)malloc(size*sizeof(int));
	printf("Enter the elements\n");
	for(int i=0;i<size;i++)scanf("%d",&arr[i]);
	printf("Enter the value to be found\n");
	scanf("%d",&ob);
	int ind=-1;
	while(--size>0){
		if(arr[size]==ob){
			ind=size;
			break;	
		}
	}
	
	printf("The last occurence of the ele is %d\n",ind);
}
