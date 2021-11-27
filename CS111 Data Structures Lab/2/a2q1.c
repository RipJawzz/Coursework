#include<stdio.h>
#include<stdlib.h>
int* allocate(int n){
	int* arr=(int*)calloc(n,sizeof(int));
	return arr;
}
void insert(int* arr,int no,int i){
	*(arr+i)=no;
	if(i!=0){	
	int temp;

	while(*(arr+i)>*(arr+i-1)){
		temp=*(arr+i);
		*(arr+i)=*(arr+i-1);
		*(arr+i-1)=temp;
		i--;
		if(i==0)break;
	}	
	}
	
}
void print(int*arr , int n){
	for(int i=0;i<n;i++){
		printf("%d ",*(arr+i));	
	}
	printf("\n");
}
void partialsort(int* arr,int n,int no){
	int i1=0,temp;
	for(int i=no;i<n-1;i++){	
		i1=i;
		while(*(arr+i1)>*(arr+i1+1)){
			temp=*(arr+i1);
			*(arr+i1)=*(arr+i1+1);
			*(arr+i1+1)=temp;
			i1++;
			if(i1==n-1)break;
		}
	}
}
void main(){
	int n,no;
	int *arr;
	printf("Enter size of array\n");
	scanf("%d",&n);
	arr=allocate(n);
	printf("Enter the elements of the array\n");
	for(int i=0;i<n;i++){
		scanf("%d",&no);
		insert(arr,no,i);
	}
	print(arr,n);
	printf("The array is sorted in descending order so now in put the index from where you want ascending order:\n");
	scanf("%d",&no);
	partialsort(arr,n,no);
	print(arr,n);
	
}
