#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node* l;
	struct node* r;
	struct node* p;
};
struct list{
	struct node* node;
	struct list* next;
	struct list* prev;
};

void q6_906();
void q6_906(){
	int no,varn,t,result=0,no_nodes;
	/*printf("Enter the number of node in the tree\n");
	scanf("%d",&no_nodes);*/
	printf("Enter the number of characters in the tree\n");
	//scanf("%d",&no);
	char str[20];
	//printf("Enter the preorder trav\n");
	//for(int i=0;i<no;i++){
	gets(str);
	//}
	printf("%s",str);
	/*printf("Enter the no of varibles\n");
	scanf("%d",&varn);
	int* arr_var=(int*)calloc(varn,sizeof(int));
	for(int i=0;i<varn;i++){
		scanf("%d ",&t);
		arr_var[i]=t;
	}
	char query[no_nodes];
	char tc;

	for(int i=0,i0=0;i<no;i++){
		tc=str[i];
		if(t!='\0'){
			if(tc=='x'){
				i++;
				tc=arr_var[str[i]];
			}
			query[i0]=tc;
			i0++;
		}
	}

	int query2[no_nodes];
	int t1=no_nodes-1,t2=0,q1,q2;
	while(t1>=0){
		if(query[t1]>='0'&& query[t1]<='9'){
			query2[t2]=query[t1]-48;
			t1--;
			t2++;
		}else{
			q1=query2[t2];
			q2=query2[t2-1];
			switch(query[t1]){
				case '+':
					q1=q1+q2;
				break;
				case '-':
					q1=q1-q2;
				break;
				case '/':
					q1=q1/q2;
				break;
				case '*':
					q1=q1*q2;
				break;
				default:
					printf("Pathetic error\n");
					break;

			}
			t2--;
			query2[t2]=q1;
		}
	}
	printf("The result is: %d \n",query2[t2]);*/
}

struct node* nnode();
struct list* lnode();
void insert_bst(struct node*,int);
struct node* find_ele(struct node*,int);
int get_depth(struct node*);
int get_height(struct node*);
void preorder_trav(struct node*);
void postorder_trav(struct node*);
void inorder_trav(struct node*);
struct node* find_pred(struct node*);
struct node* find_succ(struct node*);
void print_anc(struct node*);
void mm(struct node*);
void delete_using_pred(struct node*);
void delete_using_succ(struct node*);
void mirror(struct node*,struct node*);
void clone(struct node*,struct node*);
void del_tree(struct node*);
int count_leaf(struct node*);
int count_non_leaf(struct node*);
void print_inorder_xrec(struct node*);
struct list* push(struct list*,struct node*);
struct list* pop(struct list*);
void insert_xrec(struct node*,int);
struct node* ini_post_to_tree(struct node*,int*,int);
struct node* post_to_tree(struct node*,int*,int,int);

int main(){
	printf("Implementing BST\n");
	struct node* head=NULL;
	struct node* temp;
	struct node* cl=nnode();
	int choice=-1,f=0,t0,t1;
		char str[20];
	while(choice!=0){
		printf("Enter choice:(Enter 101 to see all choice codes)\n");
		scanf("%d",&choice);
		switch(choice){
			case 101:
				printf("1:Enter new node\n2:Find element\n3:get depth of element\n4:Get height of element\n5:delete using predecessor\n6:delete using successor\n7:Predecessor of a node\n8:sucessor of a node\n9:min,max in left sub tree\n10:in,max in right sub tree\n11:All ancestorsn\n12:All descendants\n13:\n14:Inorder trversal\n15:Preorder traversal\n16:postorder traversal\n17:level order traversal\n");
				printf("90:Mirror the current BST\n911:Clone the tree\n913:delete the tree\n916:Count number of leaf nodes\n917:COunt non leaf nodes\n91:inorder without recursioin\n921:insertion without recursion\n");
				printf("94:Create new BST using postorder traversal\n906 addiotional assignment q6\n");
			break;
			case 906:
			gets(str);
			printf("%s",str);
			//q6_906();
			break;
			case 17:
				printf("Level order traversal\n");
			//	if(head!=NULL)
				//	levelorder_trav(head);
			break;
			case 94:
				printf("Enter the number of elements\n");
				scanf("%d",&t0);
				printf("Enter the elements in postorder\n");
				int* array=(int*)calloc(t0,sizeof(int));
				for(int i=0;i<t0;i++){
					scanf("%d",&t1);
					array[i]=t1;
				}
				del_tree(head);
				if(t0!=0)
					head=ini_post_to_tree(head,array,t0);
				free(array);
			break;
			case 921:
				printf("Enter the value to be inserted\n");
				scanf("%d",&t0);
				if(f==0){
					f=1;
					struct node* head=nnode();
					head->l=NULL;
					head->r=NULL;
					head->p=NULL;
					head->data=t0;
				}else
					insert_xrec(head,t0);
			break;
			case 91:
				printf("Printing inorder traversal without using recursion\n");
				print_inorder_xrec(head);
			break;
			case 917:
				t0=count_non_leaf(head);
				printf("Number of non leaf nodes are:%d\n",t0);
			break;
			case 916:
				t0=count_leaf(head);
				printf("Number of leaf nodes are:%d\n",t0);
			break;
			case 913:
				printf("Deleting the tree\n");
				del_tree(head);
				f=0;
			break;
			case 911:
				printf("Cloning the tree\n");
				clone(head,cl);
			break;
			case 1:
				printf("Enter data to be inserted\n");
				scanf("%d",&t0);
				if(f==0){
					head=nnode();
					head->p=NULL;
					head->data=t0;
					head->l=NULL;
					head->r=NULL;
				}
				else{
					insert_bst(head,t0);
				}
				f++;
			break;
			case 2:
				printf("Enter element to be found\n");
				scanf("%d",&t0);
				temp=find_ele(head,t0);
			break;
			case 3:
				printf("Enter element whose depth is to be obtained\n");
				scanf("%d",&t0);
				temp=find_ele(head,t0);
				if(temp==NULL)
					printf("The element doesn't exist\n");
				else{
					t0=get_depth(temp);
					printf("The depth of the element is %d\n",t0);
				}
			break;
			case 4:
				printf("Enter element whose height is to be obtained\n");
				scanf("%d",&t0);
				temp=find_ele(head,t0);
				if(temp==NULL)
					printf("The element doesn't exist\n");
				else{
					t0=get_height(temp)-2;
					printf("The height of the elemnt is %d\n",t0);
				}
			break;
			case 5:
				printf("Enter ele to be deleted using predecessor\n");
				scanf("%d",&t0);
				temp=find_ele(head,t0);
				if(temp!=NULL)
					f--;
				if(f==0)
					free(head);
				else delete_using_pred(temp);
			break;
			case 6:
				printf("Enter ele to be deleted using sucessor\n");
				scanf("%d",&t0);
				temp=find_ele(head,t0);
				if(temp!=NULL)
					f--;
				if(f==0)
					free(head);
				else delete_using_succ(temp);
			break;
			case 7:
				printf("Enter node whose predecessor is to be found\n");
				scanf("%d",&t0);
				temp=find_ele(head,t0);
				temp=find_pred(temp);
				printf("%d is %d's predecessor\n",temp->data,t0);
			break;
			case 8:
				printf("Enter node whose successor is to be found\n");
				scanf("%d",&t0);
				temp=find_ele(head,t0);
				temp=find_succ(temp);
				printf("%d is %d's successor\n",temp->data,t0);
			break;
			case 9:
				printf("Enter the element whose left sub tree's min and max is to be found\n");
				scanf("%d",&t0);
				temp=find_ele(head,t0);
				if(temp->l==NULL)
					printf("Left sub tree is empty\n");
				else if(temp!=NULL)
					mm(temp->l);
			break;
			case 10:
				printf("Enter the element whose right sub tree's min and max is to be found\n");
				scanf("%d",&t0);
				temp=find_ele(head,t0);
				if(temp->r==NULL)
					printf("Right sub tree is empty\n");
				else if(temp!=NULL)
					mm(temp->r);

			break;
			case 11:
				printf("Enter ele whose all ancestors are to be printed\n");
				scanf("%d",&t0);
				temp=find_ele(head,t0);
				if(temp==NULL)
					printf("Element does't exist\n");
				else
					print_anc(temp);
			break;
			case 12:
				printf("Enter ele whose all descendants are to be printed\n");
				scanf("%d",&t0);
				temp=find_ele(head,t0);
				if(temp==NULL)
					printf("Element does't exist\n");
				else{
					preorder_trav(temp);
					printf("\n");
				}
			break;
			case 14:
				if(head!=NULL){
					printf("Inorder traversal:\n");
					inorder_trav(head);
					printf("\n");
				}else
					printf("Tree is empty\n");
			break;
			case 15:
				if(head!=NULL){
					printf("Preorder traversal:\n");
					preorder_trav(head);
					printf("\n");
				}else
					printf("Tree is empty\n");
			break;
			case 16:
				if(head!=NULL){
					printf("Postorder traversal:\n");
					postorder_trav(head);
					printf("\n");
				}else
					printf("Tree is empty\n");
			break;
			case 90:
				mirror(head,temp);
			break;
			case 0:
				printf("Exiting the program\n");
			break;
			default: ("Please enter the correct option\n");
		}
	}
	return 0;
}
struct node* nnode(){
	struct node* new=NULL;
	new=(struct node*)malloc(sizeof(struct node));
	return new;
};
struct list* lnode(){
	struct list* new=NULL;
	new=(struct list*)malloc(sizeof(struct list));
	return new;
}
struct node* ini_post_to_tree(struct node* head,int* arr,int len){
	int p;
	head=nnode();
	head->p=NULL;
	head->data=arr[0];
	head->l=NULL;
	head->r=NULL;
	for(p=1;p<len;p++)
			if(arr[p]>arr[0])
				break;
	if(len!=1){
	if(arr[len-1]<arr[0])
		p=len;
	if(arr[1]<=arr[0])
		head->l=post_to_tree(head,arr,1,p-1);
	if(arr[len-1]>=arr[0])
		head->r=post_to_tree(head,arr,p,len-1);
	}
	return head;
}
struct node* post_to_tree(struct node* node, int* arr, int s,int e){
	struct node* new=nnode();
	int p;
	new->p=NULL;
	new->l=NULL;
	new->r=NULL;
	new->data=arr[s];
		for(p=s+1;p<=e;p++)
			if(arr[p]>arr[s])
				break;
	if(s!=e){
				if(arr[e]<arr[s])
					p=e+1;
				if(arr[s+1]<=arr[s])
					new->l=post_to_tree(new,arr,s,p-1);
				if(arr[e]>=arr[s])
					new->r=post_to_tree(new,arr,p,e-1);
		}
	return new;
}
void insert_xrec(struct node* node,int dat){
	struct node* temp=NULL;
	do{
		if(temp!=NULL)
			node=temp;
		if(node->data==dat)
			break;
		else if(node->data<dat)
			temp=node->r;
		else
		 	temp=node->l;
		}while(temp!=NULL);
		temp=nnode();
		temp->data=dat;
		temp->p=node;
		temp->l=NULL;
		temp->r=NULL;
		if(node->data<dat)
			node->r=temp;
		else if(node->data>dat)
			node->l=temp;
}
struct list* pop(struct list* stack){
	if(stack->prev==NULL){
		free(stack);
		return NULL;
	}
	stack=stack->prev;
	free(stack->next);
	stack->next=NULL;
	return stack;
}
struct list* push(struct list* stack,struct node* n){
	struct list* new=lnode();
	new->node=n;
	new->next=NULL;
	new->prev=stack;
	if(stack!=NULL)
		stack->next=new;
	return new;
}

void print_inorder_xrec(struct node* node){
	struct list* stack=NULL;
	do{

		 while(node!=NULL){
			 	stack=push(stack,node);
		 		node=node->l;
			}
			if(node==NULL && stack!=NULL){
				node=stack->node;
				stack=pop(stack);
				printf("%d ",node->data);
				node=node->r;
			}

	}while(stack!=NULL || node!=NULL);
	printf("\n");
}

void insert_bst(struct node* head,int dat){
		if(head->data>dat){
			if(head->l==NULL){
				struct node* new=nnode();
				new->l=NULL;
				new->r=NULL;
				new->data=dat;
				new->p=head;
				head->l=new;
			}
			else
				insert_bst(head->l,dat);
		}
		else{
			if(head->r==NULL){
				struct node* new=nnode();
				new->l=NULL;
				new->r=NULL;
				new->data=dat;
				new->p=head;
				head->r=new;
		}
			else
				insert_bst(head->r,dat);
		}
}
struct node* find_pred(struct node* head){
	if(head->l!=NULL){
		head=head->l;
		while(head->r!=NULL)
			head=head->r;
	}
	else{
		struct node* temp=head->p;
		struct node* t2=head;
			while(temp->l==head){
				head=temp;
				temp=temp->p;
				if(temp==NULL)
					break;
			}
		if(temp!=NULL)
			head=temp;
		else if(head->data>t2->data)
			head=t2;
	}
	return head;
}
void delete_using_succ(struct node* head){
	struct node* temp=find_succ(head);
	head->data=temp->data;
	if(head->l==NULL && head->r==NULL){
		if(head->p->l==head)
			head->p->l=NULL;
		else
			head->p->r=NULL;
		free(head);
	}else if(head->l==NULL || head->r==NULL){
		temp=head->p;
		if(head->l==NULL){
			if(temp->r==head)
				temp->r=head->r;
			else
				temp->l=head->r;
		}
		else{
			if(temp->r==head)
				temp->r=head->l;
			else
				temp->l=head->l;
		}
	}
	else
	if(temp->l==NULL && temp->r==NULL){
		if(temp->p->l==temp)
			temp->p->l=NULL;
		else
			temp->p->r=NULL;
		free(temp);
	}else if(temp->l==NULL || temp->r==NULL){
		head=temp->p;
		if(temp->l==NULL){
			if(head->r==temp)
				head->r=temp->r;
			else
				head->l=temp->r;
		}
		else{
			if(head->r==temp)
				head->r=temp->l;
			else
				head->l=temp->l;
		}
	}
}
void delete_using_pred(struct node* head){
	struct node* temp=find_pred(head);
	head->data=temp->data;
	if(head->l==NULL && head->r==NULL){
		if(head->p->l==head)
			head->p->l=NULL;
		else
			head->p->r=NULL;
		free(head);
	}else if(head->l==NULL || head->r==NULL){
		temp=head->p;
		if(head->l==NULL){
			if(temp->r==head)
				temp->r=head->r;
			else
				temp->l=head->r;
		}
		else{
			if(temp->r==head)
				temp->r=head->l;
			else
				temp->l=head->l;
		}
	}
	else
	if(temp->l==NULL && temp->r==NULL){
		if(temp->p->l==temp)
			temp->p->l=NULL;
		else
			temp->p->r=NULL;
		free(temp);
	}else if(temp->l==NULL || temp->r==NULL){
		head=temp->p;
		if(temp->l==NULL){
			if(head->r==temp)
				head->r=temp->r;
			else
				head->l=temp->r;
		}
		else{
			if(head->r==temp)
				head->r=temp->l;
			else
				head->l=temp->l;
		}
	}
}
struct node* find_succ(struct node* curr){
	if(curr->r!=NULL){
		curr=curr->r;
		while(curr->l!=NULL)
			curr=curr->l;
	}
	else{
		struct node* temp=curr->p;
		struct node* t2=curr;
			while(temp->r==curr){
				curr=temp;
				temp=temp->p;
				if(temp==NULL)
					break;
			}
		if(temp!=NULL)
			curr=temp;
		else if(curr->data>t2->data)
			curr=t2;
	}
	return curr;
}
struct node* find_ele(struct node* head,int dat){
	if(head==NULL)
		printf("The element doesn't exist\n");
	else if(head->data==dat)
		printf("The element exists\n");
	else{
		if(head->data>dat)
			head=find_ele(head->l,dat);
		else
			head=find_ele(head->r,dat);
	}
	return head;
}
int get_depth(struct node* head){
	int d=0;
	while(head->p!=NULL){
		d++;
		head=head->p;
	}
	return d;
}
int get_height(struct node* head){
	int hl=0,hr=0;
	if(head==NULL)
		return 0;
	hl=get_height(head->l);
	hr=get_height(head->r);
	if(hl>hr)
		return hl+1;
	else
		return hr+1;
}
void preorder_trav(struct node* head){
	if(head!=NULL){
		printf("%d ",head->data);
		preorder_trav(head->l);
		preorder_trav(head->r);
	}
}
void postorder_trav(struct node* head){
	if(head!=NULL){
		postorder_trav(head->l);
		postorder_trav(head->r);
		printf("%d ",head->data);
	}
}
void inorder_trav(struct node* head){
	if(head!=NULL){
		inorder_trav(head->l);
		printf("%d ",head->data);
		inorder_trav(head->r);
	}
}
void print_anc(struct node* curr){
	while(curr->p!=NULL){
		curr=curr->p;
		printf("%d ",curr->data);
	}
	printf("\n");
}
void mm(struct node* curr){
	struct node* temp=curr;
	while(temp->l!=NULL)
		temp=temp->l;
	printf("min ele=%d\n",temp->data);
	temp=curr;
	while(temp->r!=NULL)
		temp=temp->r;
	printf("max ele=%d\n",temp->data);
}
void mirror(struct node* node,struct node* temp){
	temp=node->l;
	node->l=node->r;
	node->r=temp;
	if(node->l!=NULL)
		mirror(node->l,temp);
	if(node->r!=NULL)
		mirror(node->r,temp);
}
void clone(struct node* node,struct node* cl){
	cl->data=node->data;
	if(node->l!=NULL){
		struct node* nl=nnode();
		cl->l=nl;
		clone(node->l,nl);
	}else
		cl->l=NULL;
		if(node->r!=NULL){
			struct node* nr=nnode();
			cl->r=nr;
			clone(node->r,nr);
		}else
			cl->r=NULL;

}
void del_tree(struct node* node){
	if(node!=NULL){
		del_tree(node->l);
		del_tree(node->r);
	free(node);
	}
}
int count_leaf(struct node* node){
	if(node==NULL)
		return 0;
	if(node->l==NULL && node->r==NULL)
		return 1;
	return count_leaf(node->l)+count_leaf(node->r);
}
int count_non_leaf(struct node* node){
	if(node==NULL)
		return 0;
		if(node->l==NULL && node->r==NULL)
			return 0;
	return count_non_leaf(node->l)+count_non_leaf(node->r)+1;
}
