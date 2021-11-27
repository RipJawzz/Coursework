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
struct Node* add_begin(struct Node* head,struct Node* temp, int dat){
	struct Node* new=NULL;
	new=nnode(new);
	new->data=dat;
	temp=head->prev;
	temp->next=new;
	head->prev=new;
	new->next=head;
	new->prev=temp;
	return new;
}
void print(struct Node* head, struct Node* temp){
	printf("Using forward traversal: ");
	printf("%d ",head->data);
	temp=head->next;
	while(temp!=head){
		printf("%d ",temp->data);
		temp=temp->next;
	}
	printf("\nPrinting using reverse traversal: ");
	temp=head->prev;
	while(temp!=head){
		printf("%d ",temp->data);
		temp=temp->prev;
	}
	printf("%d\n",temp->data);

}
int count_ele(struct Node* head,struct Node* temp){
	int t=1;
	if(head==NULL)return 0;
	else if(head->next==head)return 1;
	temp=head->next;
	while(temp!=head){
		temp=temp->next;
		t++;
	}
	return t;
}
struct Node* remove_first(struct Node* head,struct Node* temp,int f){
	if(f==2){
		temp=head->next;
		free(temp);
		head->next=head;
		head->prev=head;
	}
	temp=head->prev;
	head=head->next;
	head->prev=temp;
	temp->next=head;
	return head;
	
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
void remove_ele_last(struct Node* head,struct Node* temp,int f){
	if(f==2){
		temp=head->next;
		free(temp);
		head->next=head;
		head->prev=head;
	}
	else{
		temp=head->prev->prev;
		temp->next=head;
		head->prev=temp;
	}
}
void main(){
	int t1,t2,choice=-1,f=0;
	struct Node* head=NULL;
	struct Node* temp=NULL;
	while(choice!=0){
			printf("Enter your choice\n");
			scanf("%d",&choice);
		switch(choice){
			
			case 1:
				printf("Enter the data to be inserted at the beginning of the list\n");
				scanf("%d",&t1);
				if(f==0){
					head=nnode(head);
					head->data=t1;
					head->next-head;
					head->prev=head;
				}
				else head=add_begin(head,temp,t1);
				f++;
			break;
			case 2:
					printf("Printing the list using both forward and backwzrd traversals\n");
					print(head,temp);
			break;
			case 3:
					t1=count_ele(head,temp);
					printf("The number of elements in the list is %d\n",t1);
			break;
			case 4:
					printf("Removing the first element of the list\n");
					if(f==1)free(head);
					else
						head=remove_first(head,temp,f);
					f--;
			break;
			case 5:
					printf("Enter the element to be added to the end of the list\n");
					scanf("%d",&t1);
					add_ele_end(head,temp,t1); 
					f++;
			break;
			case 6:
					printf("Removing the last element\n");
					
					if(f==1)free(head);
					else
						remove_ele_last(head,temp,f);
					f--;
			break;
		}
	}

}
