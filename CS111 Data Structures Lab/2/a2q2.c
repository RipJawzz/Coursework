#include<stdio.h>
#include<stdlib.h>
struct Node{
	int data;
	struct Node* next;
};
struct Node* nNode(struct Node* a){
	a=(struct Node*)malloc(sizeof(struct Node));
	return a;
}
void printlist(struct Node* head){
	while(head!=NULL){
		printf("%d ",head->data);
		head=head->next;	
	}
	printf("\n");
}
int count(struct Node* head){
	int c=0;
	while(head!=NULL){
		head=head->next;
		c++;
	}
	return c;
}
struct Node* insert_begin(struct Node* head, int num){
	struct Node* n=NULL;
	n=nNode(n);
	n->data=num;
	n->next=head;
	return n;
}
void insert_end(struct Node* head,int dat){
	struct Node* n=NULL;
	n=nNode(n);
	n->data=dat;
	while(head->next!=NULL){
		head=head->next;	
	}
	head->next=n;
	n->next=NULL;
}
struct Node* remove_first(struct Node* head){
	
	if(head->next==NULL){
		free(head);
		return NULL;	
	}
	
	struct Node* del=NULL;
	del=head;	
	head=head->next;
	free(del);
	return head;
	
}
void remove_last(struct Node* head){
	struct Node* n=NULL;
	while(head->next->next!=NULL)head=head->next;
	n=head->next;
	free(n);
	head->next=NULL;
}
void insert_pos(struct Node* head,int pos, int num){
	struct Node* n=NULL;
	n=nNode(n);
	n->data=num;	
	for(int i=0;i<pos-1;i++)
		head=head->next;
	n->next=head->next;
	head->next=n;
	
}
void remove_pos(struct Node* head,int pos){
	for(int i=0;i<pos-1;i++)head=head->next;
	head->next=head->next->next;
}
void key_insert(struct Node* head,int pos,int num){
	struct Node* temp=head;	
	int ind=0;
	while(head->data!=pos){
		ind++;
		head=head->next;
	}
	ind++;
	insert_pos(temp,ind,num);
	
}
int key_remove_index(struct Node* head,int num){
	int pos=0;
	while(head->data!=num){
		pos++;
		head=head->next;	
	}
	return pos;
}
void reverse(struct Node* head,int c){
	struct Node* n=head;
	int arr[c];
	for(int i=0;i<c;i++){
		arr[c-i-1]=n->data;
		n=n->next;	
	}
	for(int i=0;i<c;i++){
		head->data=arr[i];
		head=head->next;
	}
}
int sorted_pos13(struct Node* head,int num){
	int ind=0;
	while(head->data<num){
		ind++;
		head=head->next;
	}
	return ind;
}
void Sort_asc(struct Node* head){
	int len=count(head),temp;
	int arr[len];
	struct Node* n=head;
	for(int i=0;i<len;i++){
		arr[i]=n->data;
		n=n->next;
	}
	n=head;
	
	for(int i=len-2;i>=0;i--){
		for(int i1=0;i1<=i;i1++){
			if(arr[i1]>arr[i1+1]){
				temp=arr[i1];
				arr[i1]=arr[i1+1];
				arr[i1+1]=temp;
			}
		}
	}
	for(int i=0;i<len;i++){
		head->data=arr[i];
		head=head->next;
	}
}
void main(){
	int f=0,choice=-1;
	int num,pos;
	
	struct Node* head =NULL;
	head=nNode(head);
	while(choice!=0){
		printf("Enter choice of function:\n");
		scanf("%d",&choice);
	
	switch(choice){
		case 1:
			printf("Enter data of new node\n");
			scanf("%d",&num);
			if(f!=0)head = insert_begin(head,num);
			else {head->data=num;f=1;head->next=NULL;}
		break;
		case 2:
			printlist(head);
		break;
		case 3:
			if(f==0)num=0;
			else			
				num = count(head);
			printf("%d\n",num);
		break;
		case 4:
			printf("Removing 1st element\n");
			if(head->next==NULL)f=0;			
			head=remove_first(head);
			
		break;
		case 5:
			printf("Enter data of node at last of the list\n");
			scanf("%d",&num);
			if(f!=0)insert_end(head,num);
			else {head->data=num;f=1;head->next=NULL;}
		break;
		case 6:
			printf("Removing last element of array\n");
			remove_last(head);
		break;
		case 7:
			printf("Enter position and data for new node\n");
			scanf("%d %d",&pos,&num);
			if(pos==0)head=insert_begin(head,num);
			else if(pos==count(head))insert_end(head,num);
			else insert_pos(head,pos,num);
		break;
		case 8:
			printf("Enter the position of node to be deleted\n");
			scanf("%d",&pos);
			if(pos==0)head=remove_first(head);
			else if(pos==count(head))remove_last(head);
			else remove_pos(head,pos);
		break;
		case 9:
			printf("Enter the required key and value of new node\n");
			scanf("%d %d",&pos,&num);
			key_insert(head,pos,num);
		break;
		case 10:
			printf("Enter the ele to be removed on 1st occurence\n");
			scanf("%d",&num);
			pos=key_remove_index(head,num);
			remove_pos(head,pos);		
		break;
		case 11:
			printf("Reversing list\n");
			reverse(head,count(head));
		break;
		case 12:
			printf("Reversing list without using new list\n");
			reverse(head,count(head));
		break;
		case 13:
			printf("Enter a value to insert in a sorted list\n");
			scanf("%d",&num);
			pos=sorted_pos13(head,num);
			insert_pos(head,pos,num);
		break;
		case 14:
			printf("Sorting list in ascending order\n");
			Sort_asc(head);
		break;
	}
	}
}

