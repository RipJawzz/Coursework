#include<stdio.h>
#include<stdlib.h>
void main(){
	int size,flag=1;
	printf("Enter th size of the array\n");
	scanf("%d",&size);
	int* arr=(int*)malloc(size*sizeof(int));
	printf("Enter the elements of the array\n");	
	for(int i=0;i<size;i++)scanf("%d",&arr[i]);
	printf("Bubble sorting for ascending\n");
	int temp;
	for(int i=0;i<size;i++){
		for(int i1=0;i1<size-i-1;i1++){
			if(arr[i1]>arr[i1+1]){
				temp=arr[i1];
				arr[i1]=arr[i1+1];
				arr[i1+1]=temp;
				flag=0;
			}
		}
		if(flag==1)break;
		flag=1;
	}
	printf("The sorted array is\n");
	for(int i=0;i<size;i++)printf("%d ",arr[i]);
	printf("\n");
}
