#include<stdio.h>
#include<stdlib.h>
struct book_t{
	int ukey;
	char *issn;
	char *name;
};
struct student_t{
	int roll;
	char *name;
};
struct Node{
	int type;
	struct book_t* b;
	struct student_t* s;
	struct Node* next;
};
void add_ele_i(struct Node** s_head,int pos){
	/*struct Node* temp=NULL;
	temp=(struct Node*)malloc(sizeof(struct Node*));
	pos--;
	struct Node* new=NULL;
	new=(struct Node*)malloc(sizeof(struct Node*));
	int size,rolln;
	
	printf("Enter the size of the student's name\n");
	scanf("%d",&size);
	char namen[size];
	printf("Enter the roll number and name\n");
	scanf("%d",&rolln);
	scanf("%s",&namen);
	printf("%d %s\n",rolln,namen);
	new->type=1;
	new->s=(struct student_t*)malloc(sizeof(struct student_t*));
	new->s->roll=rolln;
	new->s->name=namen;
	new->ns=NULL;
	printf("%d %s",new->s->roll,new->s->name);
	if(*s_head==NULL){
		*s_head=new;
	}else{
		temp=*s_head;
		while(pos-->0)temp=temp->ns;
		temp->ns=new;
	}*/
	struct Node* temp1=NULL;
	temp1=(struct Node*)malloc(sizeof(struct Node*));
	int rolln,size;
	printf("Enter the size of the student's name\n");
	scanf("%d",&size);
	char namen[size];
	printf("Enter the roll number and name\n");
	scanf("%d",&rolln);
	scanf("%s",&namen);
	printf("%d %s\n",rolln,namen);
	struct Node* temp=NULL;
	temp=(struct Node*)malloc(sizeof(struct Node*));
	temp->type=1;
	temp->s=(struct student_t*)malloc(sizeof(struct student_t*));
	temp->s->roll=rolln;
	temp->s->name=(char*)malloc(size*sizeof(char));
	temp->s->name=namen;
	free(namen);
	temp->next=NULL;
	printf("%d %s\n",temp->s->roll,temp->s->name);
	if(*s_head==NULL){
		*s_head=temp;
	}else{
		temp1=*s_head;
		while(--pos>=0)temp1=temp1->next;
		//temp->next=temp1->next;
		//temp1->next=temp;
	}
	
}
void print_all_s(struct Node* s_head){
	while(s_head!=NULL){
		printf("%d %s\n",s_head->s->roll,s_head->s->name);
		s_head=s_head->next;
	}
}
struct Node* op_stu(struct Node* s_head){
	int choice=-1,t0,t1;
	while(choice!=0){
		printf("Enter you choice\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				printf("Enter the position where the node is to be inserted\n");
				scanf("%d",&t0);
				add_ele_i(&s_head,t0);
			break;
			case 2:
			
			break;
			case 7:
				print_all_s(s_head);
			break;
			case 0:printf("Returning to main body\n");
			break;
			default:printf("Enter a valid choice\n");
		}
	}
	return s_head;
};
struct Node* op_book(struct Node* b_head){
	int choice=-1;
	while(choice!=0){
		printf("Enter you choice\n");
		scanf("%d",&choice);
		switch(choice){
		
		}
	}
	return b_head;
};
void main(){
	struct Node* s_head=NULL;
	struct Node* b_head=NULL;
	int choice=-1,t0,t1;
	while(choice!=0){
		printf("Enter your choice\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				s_head=op_stu(s_head);
			break;
			case 2:
				b_head=op_book(b_head);
			break;
			case 0:
				printf("Thank you for choosing our service\n");
			break;
			default:printf("Enter a valid choice\n");			
		
		}
	}
}
