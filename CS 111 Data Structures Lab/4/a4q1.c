#include<stdio.h>
#include<stdlib.h>
void main(){
	int m,choice=-1,t1;	
	printf("Enter the size of the stack\n");
	scanf("%d",&m);
	int* arr=(int*)calloc(m,sizeof(int));
	int index=-1;
	while(choice!=0){
		printf("Enter choice\n1:PUSH\n2:POP\n0:Exit\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				printf("Enter the new element\n");
				scanf("%d",&t1);
				if(index==m-1)printf("Stack is full!\n");
				else{
					index++;
					arr[index]=t1;
				}  
			break;
			case 2:
				printf("Poping element\n");
				if(index==-1)printf("Stack is empty\n");
				else{
					printf("%d\n",arr[index]);
					index--;
				} 
			break;
		}	
	}
}
