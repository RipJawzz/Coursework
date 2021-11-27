#include<stdio.h>
#include<stdlib.h>
int** allocate(int n){
	int** b=(int **)calloc(n*n,sizeof(int));
	
	return b;
}
void deallocate(int** a,int n){
	free(a);
}
void enter(int** a,int n){
	printf("enter the val\n");
	for(int i=0;i<n;i++){
		for(int i1=0;i1<=i;i1++){
			scanf("%d",a+i1+i*n);
		}	
	}
	for(int i=0;i<n;i++){
		for(int i1=0;i1<n;i1++){
			printf("%d ",*(a+i1+i*n));
		}
		printf("\n");	
	}
}
void main(){
	int n;
	printf("Enter the size of the matrix : ");
	scanf(" %d",&n);
	int** a=allocate(n);
	enter(a,n);	
	deallocate(a,n);
}
