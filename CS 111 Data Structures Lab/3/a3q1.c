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

void print_fwd(struct Node* head){
	  while(head!=NULL){
	    printf("%d ",head->data );
	    head=head->next;
	  }
	printf("\n");
}
void print_back(struct Node* head){
	while(head!=NULL){
		printf("%d ",head->data);
		head=head->prev;
	}
	printf("\n");
}
struct Node* last_node(struct Node* head){
	while(head->next!=NULL)head=head->next;
	return head;
}
int count_ele(struct Node* head){
	if(head==NULL)return 0;
	int t=0;
	while(head!=NULL){
		head=head->next;
		t++;
	}
	return t;
}
struct Node* del_first(struct Node* head){
	head=head->next;
	free(head->prev);
	head->prev=NULL;
	return head;
}
struct Node* del_last(struct Node* last){
	last=last->prev;
	free(last->next);
	last->next=NULL;
	return last;
}
void add_ele_pos(struct Node* head, int dat,int pos){
  struct Node* new=NULL;
  new=nnode(new);
	new->data=dat;
  for(int i=0;i<pos-2;i++)head=head->next;
  new->next=head->next;
  head->next->prev=new;
  head->next=new;
  new->prev=head;
}
void del_pos(struct Node* head,int pos){
	for(int i=1;i<pos;i++){
		head=head->next;
	}
	head->next->prev=head->prev;
	head->prev->next=head->next;
	free(head);
}
int pos_key(struct Node* head,int key){
	int t=1;
	if(head==NULL)return -2;
	while(t>0){
		if(head->data==key)return t;
		else if(head==NULL)return -1;
		head=head->next;
		t++;
	}

}

void sort(struct Node* head,int f){
	int arr[f];
	struct Node* n=head;
	for(int i=0;i<f;i++){
		arr[i]=n->data;
		n=n->next;
	}
	n=head;
	int t;
	for(int i=0;i<f-1;i++){
		for(int i1=0;i1<f-1-i;i1++){
			if(arr[i1]>arr[i1+1]){
				t=arr[i1];
				arr[i1]=arr[i1+1];
				arr[i1+1]=t;
			}
		}
	}
	for(int i=0;i<f;i++){
		n->data=arr[i];
		n=n->next;
	}
}
void reverse(struct Node* head,int f){
	int arr[f];
	struct Node* n=head;
	for(int i=0;i<f;i++){
		arr[i]=n->data;
		n=n->next;
	}
	for(int i=0;i<f;i++){
		head->data=arr[f-i-1];
		head=head->next;
	}
}
struct Node* reverse_sp(struct Node* head){
	struct Node* new=NULL;
	head->prev=NULL;
	new=nnode(new);
  while(1){
	//printf("%d ",head->data);
    new->next=head->prev;
    head->prev=head->next;
    head->next=new->next;
    if(head->prev!=NULL)head=head->prev;
	else break;
    }
	head->prev=NULL;
	return head;
}
void main(){
  int no=0,pos=0,dat=0,choice=-1,f=0;
	struct Node* head=NULL;
	struct Node* last=NULL;
  while(choice!=0){
    printf("Enter your choice:-\n");
    scanf("%d",&choice);
    switch(choice){
      case 1:
	printf("Enter the data for new node\n");
	scanf("%d",&no);
	if(f==0)
		{f++;head=nnode(head);head->data=no;}
	else
		{head=new_start(head,no);f++;}
      break;
      case 2:
		printf("Printing using both traversals\n");
		print_fwd(head);
		last=last_node(head);
		print_back(last);
      break;
      case 3:
		no=count_ele(head);
		printf("Number of elements:%d\n",no);
      break;
      case 4:
		printf("Removing the first element of the list\n");
		if(f==0)printf("Already empty list\n");
		else if(f==1)free(head);
		else head=del_first(head);
		if(f!=0)f--;
		printf("No of elements remaining:%d\n",f);
      break;
      case 5:
		printf("Enter the element to be entered at the end of the list:\n");
		scanf("%d",&no);
		new_end(head,no);
      break;
      case 6:
		printf("Deleting the last element of the list\n");
		if(f==0)printf("Already empty list\n");
		else if(f==1)free(head);
		last=last_node(head);
		del_last(last);
		if(f!=0)f--;
		printf("No of elements remaining:%d\n",f);
      break;
      case 7:
		printf("Enter the position and data of new node\n");
		scanf("%d %d",&pos,&no);
		if(pos==1)head=new_start(head,no);
		else if(pos==f+1)new_end(head,no);
		else add_ele_pos(head,no,pos);
	break;
      case 8:
		printf("Enter the position to remove the node\n");
		scanf("%d",&pos);
		if(f==0)printf("The list is already empty\n");
		else if(pos==1)head=del_first(head);
		else if(pos==f)del_last(head);
		else del_pos(head,pos);
		if(f!=0)f--;
      break;
      case 9:
		printf("Enter the key and data of the new node\n");
		scanf("%d %d",&pos,&no);
		pos=pos_key(head,pos);
		if(pos==-1)printf("Element doesn't exist\n");
		else {
				add_ele_pos(head,no,pos);
				f++;
			}
      break;
	case 10:
		printf("Enter the data to be removed at first occurence\n");
		scanf("%d",&no);
		pos=pos_key(head,no);
		if(f==0) printf("The list is already empty\n");
		else if(head->data==no) head=del_first(head);
		else if(pos==f) del_last(head);
		else del_pos(head,pos);
		if(f!=0) f--;
	   break;
	case 11:
		printf("Reversing the elements in the list\n");
		head=reverse_sp(head);
	break;
	case 12:
		printf("Reversing the elements in the list without creating a new list\n");
		reverse(head,f);
	break;
	case 13:
		printf("Enter the element to be entered in an ascending list\n");
		scanf("%d",&no);
		new_end(head,no);
		f++;
		sort(head,f);

	break;
	case 14:
		printf("Sorting the list in ascending order\n");
		sort(head,f);
	break;
	}
  }


}
