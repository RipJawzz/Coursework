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
void new_end(struct Node* head,int dat){
  struct Node* new=NULL;
  new=nnode(new);
  while(head->next!=NULL)head=head->next;
  new->data=dat;
  head->next=new;
  new->prev=head;
}
struct Node* new_start(struct Node* head,int dat){
  struct Node* new=NULL;
  new=nnode(new);
  new->data=dat;;
  new->next=head;
  head->prev=new;
  return new;
}
void merge(struct Node* h1,struct Node* h2){
	while(h1->next!=NULL){h1=h1->next;}
	h1->next=h2;
	h2->prev=h1;
}
void access_pos(struct Node* head,int pos){
	for(int i=1;i<pos;i++)head=head->next;
	printf("What do you want to do with this data?\n");
	int choice=0;
	printf("1.Print\n2.Change\n");
	scanf("%d",&choice);
	switch(choice){
		case 1:
			printf("%d\n",head->data);
		break;
		case 2:
			printf("Enter the new data:");
			scanf("%d",&choice);
			head->data=choice;
		break;
	}
}
void print_rec(struct Node* head){
	if(head!=NULL){
		printf("%d ",head->data);
		head=head->next;
		print_rec(head);
	}
}
struct Node* last_node(struct Node* head){
	while(head->next!=NULL)head=head->next;
	return head;
}
void print_rec_rev(struct Node* head){
	if(head!=NULL){
		printf("%d ",head->data);
		head=head->prev;
		print_rec_rev(head);
	}
}
struct Node* rev_rec(struct Node* head,struct Node* trash){
	
	if(head->next==NULL){
		head->next=head->prev;
		head->prev=NULL;
		return head;
	}	
	trash->next=head->next;
	head->next=head->prev;
	head->prev=trash->next;
	head=head->prev;
	head=rev_rec(head,trash);
	return head;
}
struct Node* merge_sorted(struct Node* h1,struct Node* h2){
	struct Node* new=NULL;
	struct Node* temp=NULL;
	new=nnode(new);

	if(h1->data<h2->data){
		new->next=NULL;
		new->prev=NULL;
		new->data=h1->data;
		h1=h1->next;
	}else{
		new->next=NULL;
		new->prev=NULL;
		new->data=h2->data;
		h2=h2->next;
	}
	temp=new;
	while(h1!=NULL || h2!=NULL){
		if(h1==NULL){
			while(h2!=NULL){
				new_end(temp,h2->data);
				h2=h2->next;
				temp=temp->next;
			
			}
		}
		else if(h2==NULL){
			while(h1!=NULL){
				new_end(temp,h1->data);
				h1=h1->next;
				temp=temp->next;
			
			}
		}
		else{
			if(h1->data<h2->data){
				new_end(temp,h1->data);
				h1=h1->next;
				temp=temp->next;
				
			}else{
				new_end(temp,h2->data);
				h2=h2->next;
				temp=temp->next;
				
			}
		}
	}
	return new;
}
void rect(struct Node* head){
	struct Node* temp=NULL;
	temp=nnode(temp);
	temp=head->next;
	while(temp!=NULL){
		if(head!=temp->prev)
			temp->prev=head;
		head=head->next;
		temp=temp->next;
	}

}
int count(struct Node* head){
	int t=0;
	while(head!=NULL){
		t++;
		head=head->next;
	}
	return t;
}
void rotate(struct Node* head,int no){
	struct Node* temp=NULL;
	int t1=0,t2=0;
	temp=nnode(temp);
	while(no-->0){
		temp=head;
		t1=temp->data;
		t2=temp->next->data;
		temp=temp->next;
		while(1){
			temp->data=t1;
			t1=t2;
			temp=temp->next;
			if(temp==NULL)break;
			t2=temp->data;
		}
		head->data=t1;
	}

}
void main(){
	int no=0,pos,dat=0,choice=-1;
	struct Node* h1=NULL;
	struct Node* h2=NULL;
	struct Node* last=NULL;
  	printf("Enter the no of nodes for 1st list:\n");
	scanf("%d",&no);
	printf("Enter data for %d nodes:\n",no);
	for(int i=0;i<no;i++){
		scanf("%d",&pos);
		if(i==0){
			h1=nnode(h1);
			h1->data=pos;
		}
		else new_end(h1,pos);
	}
	printf("Enter the no of nodes for 2nd list:\n");
	scanf("%d",&no);
	printf("Enter data for %d nodes:\n",no);
	for(int i=0;i<no;i++){
		scanf("%d",&pos);
		if(i==0){
			h2=nnode(h1);
			h2->data=pos;
		}
		else new_end(h2,pos);
	}
	while(choice!=0){
		printf("Enter your choice:-\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				printf("Merging the two lists, 1st to second and naming its 1st\n");
				merge(h1,h2);
		      	break;
	      		case 2:
				printf("Enter the position whose data is to be accessed\n:");
				scanf("%d",&pos);
				access_pos(h1,pos);
			break;
			case 3:
				printf("Merging the two lists as sorted\n");
				h1=merge_sorted(h1,h2);
			break;
			case 4:
				printf("Printing using recursion\n");
				print_rec(h1);
				printf("\n");
			break;
			case 5:
				printf("Printing reversed list using recursion\n");
				last=last_node(h1);
				print_rec_rev(last);
				printf("\n");
			break;
			case 6:
				printf("Reversing the list by using recursion\n");
				h1=rev_rec(h1,h2);
			break;
			case 7:
				printf("rectifying list\n");
				rect(h1);
			break;
			case 8:
				printf("Enter the number of clockwise rotations\n");
				scanf("%d",&no);
				pos=count(h1);
				no=no%pos;
				rotate(h1,no);
			break;
		}
	}


}
