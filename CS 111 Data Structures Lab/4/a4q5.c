#include<stdio.h>
#include<stdlib.h>
struct Node{
  int data;
  struct Node* next;
  struct Node*prev;
};
struct Node* nnode(struct Node* new){
  new=(struct Node*)malloc(sizeof(struct Node*));
  new->next=NULL;
  new->prev=NULL;
  return new;
}
void print_all(struct Node* head){
	struct Node* temp=NULL;
	temp=head;
	
	while(temp->next!=head){
		printf("%d ",temp->data);
		temp=temp->next;
	}
	printf("%d\n",temp->data);
	
}
void add_ele_end(struct Node* head,struct Node* temp,int dat){
	struct Node* new=NULL;
	new=nnode(new);
	new->data=dat;
	temp=head->prev;
	temp->next=new;
	new->prev=temp;
	head->prev=new;
	new->next=head;
	
}
void push_st(struct Node* head,int dat,int index){
	for(int i=0;i<index;i++)head=head->next;
	head->data=dat;
}
void pop_st(struct Node* head,int index){
	for(int i=0;i<index;i++)head=head->next;
	printf("%d\n",head->data);
}
void stack_using_dll(){
	int m,choice=-1;
	int index=-1,t1;
	struct Node* head=NULL;
	struct Node* temp=NULL;
	head=nnode(head);
	head->next=head;
	head->prev=head;
	head->data=0;
	
	printf("Enter the size of the stack to be implemented using doubly liked list\n");
	scanf("%d",&m);
	for(int i=0;i<m-1;i++){
		add_ele_end(head,temp,0);
	}
	while(choice!=0){
		printf("Enter your choice\n1:PUSh\n2:POP\n0:exit this part\n");
		scanf("%d",&choice);
		switch(choice){
				
			case 1:
				if(index==m-1)printf("The stack is full\n");
				else{
					printf("Enter the new element\n");
					scanf("%d",&t1);
					index++;
					push_st(head,t1,index);
				}
			break;
			case 2:
				if(index==-1)printf("Stack is empty\n");
				
					else{					
						pop_st(head,index);
						--index;
					}
				
			break;
			
			default:printf("Enter a valid option");
		}
	}
}
void push_q1(struct Node* q1,int dat,int q1t){
	for(int i=0;i<q1t;i++)q1=q1->next;
	q1->data=dat;

}
int pop_q2(struct Node* q2,int q2t){
	for(int i=0;i<q2t;i++)q2=q2->next;	
	printf("%d\n",q2->data);
	return q2->data;
}
int pop_q1(struct Node* q1,int q1t){
	for(int i=0;i<q1t;i++)q1=q1->next;
	return q1->data;
}
void push_q2(struct Node* q2,int q2t,int dat){
	for(int i=0;i<=q2t;i++)q2=q2->next;
	q2->data=dat;
}
void transfer(struct Node* q1,struct Node* q2,int q1t,int q2t){
	int t1;	
	while(q1t!=-1){
		//printf("%d\n",q1t);		
		t1=pop_q1(q1,q1t);
		q1t--;
		push_q2(q2,q2t,t1);
		q2t++;
	}
}
void queue_using_st_dll(){
	int choice=-1,t1,m,q1t=-1,q2t=-1;
	printf("Enter the size of the queue required\n");
	scanf("%d",&m);
	struct Node* q1=NULL;
	struct Node* q2=NULL;
	struct Node* temp=NULL;
	q1=nnode(q1);
	q1->next=q1;
	q1->prev=q1;
	q1->data=0;
	q2=nnode(q2);
	q2->next=q2;
	q2->prev=q2;
	q2->data=0;
	for(int i=0;i<m-1;i++){
		add_ele_end(q1,temp,0);
		add_ele_end(q2,temp,0);
	}
	while(choice!=0){
		printf("Enter the choice\n1:enqueue\n2:dequeue\n0exit prog\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				if(q1t+q2t+2==m)printf("Queue is full\n");
				else{
					printf("Enter the new element\n");
					scanf("%d",&t1);
					push_q1(q1,t1,++q1t);
				}			
			break;

			case 2:
				if(q1t+q2t+2==0)printf("Queue is empty\n");
				else{
					if(q2t==-1){
						transfer(q1,q2,q1t,q2t);
						q2t=q1t;
						q1t=-1;
						t1=pop_q2(q2,q2t);
						--q2t;
					}
					else{
						t1=pop_q2(q2,q2t);
						--q2t;
					}
				}
			break;
			case 3:print_all(q1);
					print_all(q2);
					break;
			default:printf("Enter a valid option");
		}
	}
	
	
}
void main(){
	int choice=-1;
	while(choice){
		printf("Enter the choice\n1:stack using dll\n2:queue using stack using dll\n0:exit the prog\n");
		scanf("%d",&choice);
		switch(choice){
			case 0:printf("See you later");
			case 1:
				stack_using_dll();
			break;
			case 2:
				queue_using_st_dll();
			break;
			default:printf("Please check your option \n");
		}
	
	}	


}
