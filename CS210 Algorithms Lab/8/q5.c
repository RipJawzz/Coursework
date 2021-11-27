#include<stdio.h>
#include<stdlib.h>

typedef struct node{
  int ele;
  int inc;
  struct node* pa;
}node;

node* new_node(){
  node* new=(node*)calloc(1,sizeof(node));
  new->ele=0;
  new->inc=0;
  new->pa=NULL;
  return new;
}
void sum_of_subsets(node* head,int* arr,int ob,int n,int sum,int target){
  if(sum==target && head->inc==1){
    node* ne=head;
    while(ne->pa!=NULL){
      if(ne->inc==1)
        printf("%d ",ne->ele);
      ne=ne->pa;
    }
    printf("\n");
    ne->ele=1;
  }else if(ob>n || sum>target)
  {

  }else{
    node* lc=new_node();
    node* rc=new_node();
    lc->ele=arr[ob];
    rc->ele=lc->ele;
    rc->inc=1;
    lc->pa=head;
    rc->pa=head;
    sum_of_subsets(lc,arr,ob+1,n,sum,target);
    sum_of_subsets(rc,arr,ob+1,n,sum+rc->ele,target);
  }
}
void main(){
  int n,sum;
  node* head=new_node();
  printf("Enter the number of elements\n");
  scanf("%d",&n);
  int* arr=(int*)calloc(n,sizeof(int));
  printf("Enter the desired sum(positive)\n");
  scanf("%d",&sum);
  printf("Enter the elements(non negative)\n");
  for(int i=0;i<n;i++)
    scanf("%d",&arr[i]);
  sum_of_subsets(head,arr,0,n-1,0,sum);
  if(head->ele==0)
    printf("Not possible\n");
}
