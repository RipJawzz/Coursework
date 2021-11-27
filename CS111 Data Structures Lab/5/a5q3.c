#include<stdio.h>
#include<stdlib.h>
void selection_sort(int* arr,int size){
	int temp,minind;
	for(int i=0;i<size;i++){
		minind=i;
		for(int i1=i+1;i1<size;i1++){
			if(arr[minind]>arr[i1])minind=i1;
		}
		temp=arr[i];
		arr[i]=arr[minind];
		arr[minind]=temp;
	}

}
void print_all(int* arr,int size){
	for(int i=0;i<size;i++)printf("%d ",arr[i]);
	printf("\n");
}
void main(){
	int size;
	printf("Enter the size:\n");
	scanf("%d",&size);
	int* arr=(int*)malloc(size*sizeof(int));
	printf("Enter the elements\n");
	for(int i=0;i<size;i++)scanf("%d",&arr[i]);
	printf("Sorting array in ascending order using selection sort\n");
	selection_sort(arr,size);
	print_all(arr,size);	
}
