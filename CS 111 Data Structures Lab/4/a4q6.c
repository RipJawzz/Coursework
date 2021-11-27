#include<stdio.h>
#include<stdlib.h>
struct Node{
	int data;
	struct Node* next;
};
struct Node* nnode(){
	struct Node* new=NULL;
	new=(struct Node*)malloc(sizeof(struct Node*));
	return new;
}
void cll_add_end(struct Node* head,struct Node* tail,int dat){
	struct Node* new=NULL;
	new=nnode();
	new->data=dat;
	new->next=head;
	tail->next=new;
}
void q_enq(struct Node* tail,int dat){
	tail->data=dat;
}
int q_deq(struct Node* head){
	int t=head->data;
	printf("%d\n",t);
	return t;
}
void print_all(struct Node* head,struct Node* temp){
	while(head!=temp){
		printf("%d ",head->data);
		head=head->next;
	}
	//printf("%d\n",head->data);
	printf("\n");
}
void exchange(struct Node** q1,struct Node** q2,struct Node** t1,struct Node** t2){
	struct Node* t=NULL;
	t=*q1;
	*q1=*q2;
	*q2=t;
	t=*t1;
	*t1=*t2;
	*t2=t;
}
void transfer(struct Node** q1,struct Node** q2,struct Node** t1,struct Node** t2){
	int te;
	while(*q1!=*t1){
		te=(*q1)->data;
		*q1=(*q1)->next;
		q_enq(*t2,te);
		*t2=(*t2)->next;
	}
}
void st_q_dll(){
	int choice=-1,m,te1;
	printf("Enter the size of the stack required\n");
	scanf("%d",&m);
	struct Node* q1=NULL;
	q1=nnode();
	q1->data=0;
	q1->next=q1;
	struct Node* t1=q1;
	struct Node* q2=NULL;
	q2=nnode();
	q2->data=0;
	q2->next=q2;
	struct Node* t2=q2;
	for(int i=0;i<m-1;i++){
		cll_add_end(q1,t1,0);
		t1=t1->next;
		cll_add_end(q2,t2,0);
		t2=t2->next;
	}
	t1=q1;
	t2=q2;
	while(choice!=0){
		printf("Enter your choice\n1:PUSH\n2:POP\n0:Exit this part\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
					if(t1->next==q1)printf("The stack is full\n");
					else{
						printf("Enter the new element\n");
						scanf("%d",&te1);
						q_enq(t2,te1);
						t2=t2->next;
						transfer(&q1,&q2,&t1,&t2);
						exchange(&q1,&q2,&t1,&t2);
					}
			break;
			case 2:
					if(q1==t1)printf("The stack is empty\n");
					else{
						te1=q_deq(q1);
						q1=q1->next;
					}
			break;
			case 3:
				print_all(q1,t1);
				print_all(q2,t2);
			break;
			default:printf("Enter a correct choice\n");
		}
	}


}
void q_cll(){
	int choice=-1,t1,m;
	printf("Enter the size of the queue required\n");
	scanf("%d",&m);
	struct Node* head=NULL;
	head=nnode();
	head->data=0;
	head->next=head;
	struct Node* temp=head;
	for(int i=0;i<m;i++){
		cll_add_end(head,temp,0);
		temp=temp->next;
	}
	temp=head;
	while(choice!=0){
		printf("Enter your choice\n1:Enqueue\n2:Dequeue\n0:Exit this part\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
					if(temp->next==head)printf("Queue is full\n");
					else{
						printf("Enter the new element\n");
						scanf("%d",&t1);
						q_enq(temp,t1);
						temp=temp->next;
					}
			break;
			case 2:
					if(head==temp)printf("The queue is already empty\n");
					else{
						t1=q_deq(head);
						head=head->next;
					}
			break;
			case 3:print_all(head,temp);break;
			default:printf("Enter a correct choice\n");
		}
	}

}
void main(){
	int choice=-1;
	while(choice!=0){
		printf("Enter your choice\n1:queue using circular sll\n2:stack using queue using sll\n0: Exit\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				q_cll();
			break;
			case 2:
				st_q_dll();
			break;
			case 0:printf("Thank you for using our application.\n");break;
			default:printf("Enter a valid option\n");
		}
	}

}
