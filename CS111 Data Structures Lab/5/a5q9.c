#include<stdio.h>
#include<stdlib.h>
int* hyper_sort(int* arr,int size){
	int ind=0,i0=0,i1=size-1,temp;
	int* ar=(int*)malloc(size*sizeof(int));	
	while(i1!=i0){
		if(arr[i1]>arr[i0]){
			ar[ind]=arr[i1];
			i1--;
		}else{
			ar[ind]=arr[i0];
			i0++;
		}
		ind++;	
	}
	ar[ind]=arr[i0];
	return ar;
}
void main(){
	int size;
	printf("Enter the size:\n");
	scanf("%d",&size);
	int* arr=(int*)malloc(size*sizeof(int));
	printf("Enter the elements\n");
	for(int i=0;i<size;i++)scanf("%d",&arr[i]);
	arr=hyper_sort(arr,size);
	printf("The descending sorted array is\n");
	for(int i=0;i<size;i++)printf("%d ",arr[i]);
	printf("\n");
}
