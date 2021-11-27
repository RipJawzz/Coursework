#include<stdio.h>
#include<stdlib.h>
void mergesort(int* arr,int s,int e){
	int m=(s+e)/2;
	if(s!=e){	
		mergesort(arr,s,m);
		mergesort(arr,m+1,e);
	}	
	merging(arr,s,e);
}
void merging(int* arr,int s,int e){
	int temp,flag=1;
	for(int i=s;i<e;i++){
		for(int i1=s;i1<e-i;i1++){
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
}
void main(){
	int size;
	printf("Enter the size:\n");
	scanf("%d",&size);
	int* arr=(int*)malloc(size*sizeof(int));
	printf("Enter the elements\n");
	for(int i=0;i<size;i++)scanf("%d",&arr[i]);
	mergesort(arr,0,size-1);
	
	printf("The sorted array is\n");
	for(int i=0;i<size;i++)printf("%d ",arr[i]);
	printf("\n");
}
