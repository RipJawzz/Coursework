#include<stdio.h>
#include<stdlib.h>
void printall(int * arr,int m){
	for(int i=0;i<m+2;i++){
		printf("%d ",arr[i]);
		
	}
	printf("\n");
}
void main(){
	int choice=-1,t1,m,st=0,en=1,t2;
	printf("Enter the size of the circular queue\n");
	scanf("%d",&m);
	int* arr=(int*)calloc(m+2,sizeof(int));
	while(choice!=0){
		printf("Enter the choice\n1:add element\n2:remove last element\n0:exit prog\n");
		scanf("%d",&choice);
		switch(choice){
			case 0:printf("Exiting the prog\n");break;
			case 1:
				printf("Enter the new element\n");
				scanf("%d",&t1);
				if(st-en==1 || (st==0 && en==m+1))printf("Queue is full\n");
				else{
					arr[en]=t1;
					en++;
					en=en%(m+2);
				}
			break;
			case 2:
				printf("Removing last element\n");
				
				if(en-st==1 || (en==0 && st==m+1))printf("Queue is empty\n");
				else{	
					st++;
					st=st%(m+2);
					printf("%d\n",arr[st]);
					
					
				}
			break;
			case 3:
				printall(arr,m);
			break;
			default:printf("Enter a valid choice\n");
		}
	}

}
