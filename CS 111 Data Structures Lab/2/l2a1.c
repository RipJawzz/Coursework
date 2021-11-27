#include<stdio.h>
#include<stdlib.h>
//#include "a2q2.c"
struct Node{
	int data;
	struct Node* next;
};
struct lnode{
	int data;
	struct lnode* next;
	int pre;
};
struct Node* nnode(struct Node* n){
	n=(struct Node*)malloc(sizeof(struct Node*));
	return n;
}
struct lnode* llnode(struct lnode* n){
	n=(struct lnode*)malloc(sizeof(struct lnode*));

	return n;
}
void add_ele(struct Node* head,int dat){
	struct Node* new=NULL;
	new=nnode(new);	
	new->data=dat;
	new->next=NULL;
	while(head->next!=NULL)head=head->next;
	head->next=new;
	
}
void add_elel(struct lnode* head,int dat){
	struct lnode* new=NULL;
	new=llnode(new);	
	new->data=dat;
	new->pre=1;
	new->next=NULL;
	
	while(head->next!=NULL)head=head->next;
	head->next=new;
	
}
void print(struct Node* head){
	while(head!=NULL){
		printf("%d ",head->data);
		head-head->next;	
	}
	printf("\n");
}
void merge(struct Node* h1,struct Node* h2){
	while(h1->next!=NULL)h1=h1->next;
	h1->next=h2;
}
void print_ele(struct Node* head,int pos){
	while(pos-->0)head=head->next;
	printf("%d",head->data);
}
int detectloop(struct lnode* list) 
{ 
    struct lnode *slow_p = list, *fast_p = list; 
  
    while (slow_p && fast_p && fast_p->next) { 
        slow_p = slow_p->next; 
        fast_p = fast_p->next->next; 
        if (slow_p == fast_p) { 
            
            return 1; 
        } 
    } 
    return 0; 
} 
struct Node* merge_sort(struct Node* h1,struct Node* h2){
	struct Node* h3=NULL;
	struct Node* hd=NULL;
	h3=nnode(h3);
	hd=h3;
	if(h1->data>h2->data){
		h3->data=h2->data;
		h2=h2->next;	
	}
	else{
		h3->data=h1->data;
		h1=h1->next;	
	}
	
	while(h1!=NULL || h2!=NULL){
		if(h1==NULL){
			while(h2!=NULL){
				add_ele(h3,h2->data);
				h3=h3->next;
				h2=h2->next;
			}		
		}
		else if(h2==NULL){
			while(h1!=NULL){
				add_ele(h3,h1->data);
				h3=h3->next;
				h1=h1->next;
			}
		}
		else{
			if(h1->data>h2->data){
				add_ele(h3,h2->data);
				h3=h3->next;
				h2=h2->next;	
			}
			else{
				add_ele(h3,h1->data);
				h3=h3->next;
				h1=h1->next;	
			}
		}	
	}
	return hd;
}
void print_rec(struct Node* head){
	if(head!=NULL){
		printf("%d ",head->data);
		head=head->next;
		print_rec(head);
	}
}
void print_rec_rev(struct Node* head){
	if(head->next!=NULL)print_rec_rev(head->next);
	printf("%d ",head->data);
	
	
}
void rectify(struct lnode* head){
	while(head->next->pre==1){head->pre=0;head=head->next;}
	head->next=NULL;
}
struct Node* rev_rec(struct Node* head,struct Node* rev){
	struct Node* new=NULL;
	new=nnode(new);
	new=head;
	head=head->next;
	if(rev==NULL){rev=nnode(rev);rev->data=new->data;}
	else {new->next=rev;rev=new;}
	if(head!=NULL)rev=rev_rec(head,rev);	
	return rev;
}
void print_h3(struct lnode* head){
	while(head!=NULL){
		printf("%d ",head->data);
		head=head->next;
	}
	printf("\n");
}
void main(){
	struct Node* h1=NULL;
	struct Node* h2=NULL;
	struct lnode* h3=NULL;
	int n1,n2,t0,t1,t2;
	h3=llnode(h3);
	h3->next=NULL;
	h3->pre=1;
	h3->data=2;
	add_elel(h3,3);
	add_elel(h3,5);
	add_elel(h3,9);
	add_elel(h3,13);
	add_elel(h3,2);
	add_elel(h3,5);
	h3->next->next->next->next->next->next->next=h3->next->next;
	printf("Enter the num of ele in first and second singly liked list\n");	
	scanf("%d %d",&n1,&n2);
	printf("Enter the data of the first single linked list\n"); 
	for(int i=0;i<n1;i++){
		scanf("%d",&t0);
		if(h1==NULL){h1=nnode(h1);h1->data=t0;}
		else{add_ele(h1,t0);}
	}
	printf("Enter the data of the second single linked list\n"); 
	for(int i=0;i<n2;i++){
		scanf("%d",&t0);
		if(h2==NULL){h2=nnode(h2);h2->data=t0;}
		else{add_ele(h2,t0);}
	}
	int choice;
	while(choice!=0){
		printf("Enter 0 to terminate the program\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				printf("Merging the two list(first to second) and this will be the new modified 1st list\n");
				n1=n1+n2;
			break;
			case 2:
				printf("Enter the list number and position to access the element\n");
				scanf("%d %d",&t0,&t1);
				if(t0==1)print_ele(h1,t1);
				else print_ele(h2,t1);
			break;
			case 3:
				printf("Detecting loop in a list\n");
				t0=detectloop(h3);
				if(t0==1)printf("Loop detected\n");
				else printf("No loop detected\n");
			break;
			case 4:
				printf("rectifying the loop\n");
				rectify(h3);
			break;
			case 5:
				printf("Merging 1st and 2nd list (sorted) and storing in 1st list\n");
				h1=merge_sort(h1,h2);
			break;
			case 6:
				printf("Printing 1st list using recursion\n");
				print_rec(h1);
			break;
			case 7:
				printf("Printing list in reverse order using recursion\n");
				print_rec_rev(h1);
				printf("\n");
			break;
			case 8:
				printf("Reversing 1st list using recursion\n");
				free(h2);
				h1=rev_rec(h1,h2);
			break;
			case 9:printf("print h3 loop\n");
				print_h3(h3);
				break;
		}
	}
}
