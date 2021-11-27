#include<stdio.h>
#include<stdlib.h>
void push1(int * st,int* top1,int data){
	*top1=*top1+1;
	st[*top1]=data;
}
void push2(int *st,int* top2,int data){
	*top2=*top2-1;
	st[*top2]=data;
}
void pop1(int* top1,int* st){
	printf("%d\n",st[*top1]);
	*top1=*top1-1;
}
void pop2(int* top2 ,int* st){
	printf("%d\n",st[*top2]);
	*top2=*top2+1;
}
void print_all(int* st,int len){
	for(int i=0;i<len;i++)printf("%d ",st[i]);
	printf("\n");
}
void main(){
	int size,choice=-1,t1;
	printf("Enter the size of the max combined sixe of the two stacks\n");
	scanf("%d",&size);
	int* st=(int*)calloc(size,sizeof(int));
	int top1=-1,top2=size;
	while(choice!=0){
		printf("Enter your choice:\n1:push 1\n2:pop 1\n3:push 2\n4:pop 2\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:if(top1+1==top2)printf("The stacks are full\n");
					else{
						printf("Enter the data \n");
						scanf("%d",&t1);
						push1(st,&top1,t1);
					}
			break;
			case 2:if(top1==-1)printf("The first stack is empty\n");
					else{
						pop1(&top1,st);
						}
			break;
			case 3:if(top1+1==top2)printf("The stacks are full\n");
					else{
						printf("Enter the data \n");
						scanf("%d",&t1);
						push2(st,&top2,t1);
					}
			break;
			case 4:if(top2==size)printf("The second stack is empty\n");
					else{
						pop2(&top2,st);
					}
			break;
			case 5:print_all(st,size);
			break;
			case 0:printf("Thank you for using our program\n");
			break;
			default:printf("Enter a valid choice\n");
		
		}
	}
	
}
