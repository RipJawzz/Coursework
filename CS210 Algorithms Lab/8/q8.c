#include<stdlib.h>
#include<stdio.h>
typedef struct item{
  int price;
  int weight;
}item;
item new_item(int price,int weight){
  item new;
  new.price=price;
  new.weight=weight;
  return new;
}
typedef struct list{
  float UB;
  int price_till_now;
  int weight_rem;
  int index;
  struct list* next;
  struct list* prev;
}list;
list* new_list(){
  list* new=(list*)calloc(1,sizeof(list));
  new->next=NULL;
  new->prev=NULL;
  return new;
}
int compare(const void* a, const void* b){
  item* n1=(item*)a,*n2=(item*)b;
  float diff=-(n1->price*1.0/n1->weight*1.0)+(n2->price*1.0/n2->weight*1.0);
  if(diff<0)
    return -1;
  if(diff>0)
    return 1;
  return 0;
}
float UB(item* arr,int p,int n,int rem_weight){
  float cost=0;
  while(p<=n || rem_weight>0){
    if(arr[p].weight>rem_weight){
      rem_weight=0;
      cost+=rem_weight*1.0*arr[p].price*1.0/arr[p].weight*1.0;
    }
    else{
      rem_weight-=arr[p].weight;
      cost+=arr[p].price;
    }
    p++;
  }
  return cost;
}
void del_list(list* node){
  node->next->prev=node->prev;
  node->prev->next=node->next;
  free(node);
}
void add_end(list* tail,list* node){
  node->next=tail;
  node->prev=tail->prev;
  node->prev->next=node;
  node->next->prev=node;
}
int backtrack(item* arr,int p,int n,int rem_weight,int p_till_now,list* head,list* tail){
  list* node=new_list();
  int price,temp;
  float ub2=p_till_now;
  if(p<n)
    ub2=UB(arr,p+1,n,rem_weight)+p_till_now;
  float ub1=p_till_now;
  if(rem_weight>=arr[p].weight && p<n)
    ub1=UB(arr,p+1,n,rem_weight-arr[p].weight)+arr[p].price+p_till_now;

  if(ub1>ub2){
    if(ub2!=p_till_now){
      node->UB=ub2;
      node->price_till_now=p_till_now;
      node->weight_rem=rem_weight;
      node->index=p+1;
      add_end(tail,node);
    }
    if(rem_weight>=arr[p].weight && p<n)
      p_till_now=backtrack(arr,p+1,n,rem_weight-arr[p].weight,p_till_now+arr[p].price,head,tail);
  }else{
    if(ub1!=p_till_now){
      node->UB=ub1;
      node->price_till_now=p_till_now+arr[p].price;
      node->weight_rem=rem_weight-arr[p].weight;
      node->index=p+1;
      add_end(tail,node);
    }
    if(rem_weight>=arr[p].weight && p<n)
      p_till_now=backtrack(arr,p+1,n,rem_weight,p_till_now,head,tail);
  }

  node=head->next;
  while(head->next!=tail){
    if(node->UB<p_till_now){
      node=node->next;
      del_list(node->prev);
    }else{
      temp=backtrack(arr,node->index,n,node->weight_rem,node->price_till_now,node->next,tail);
      node=node->next;
      del_list(node->prev);
      if(temp>p_till_now)
        p_till_now=temp;
    }
  }
  return p_till_now;
}

void main(){
  int n,t1,t2,w;
  printf("Enter the number of items and max weight\n");
  scanf("%d %d",&n,&w);
  item arr[n];
  printf("Enter the n items price and weights\n");
  for(int i=0;i<n;i++){
    scanf("%d %d",&t1,&t2);
    arr[i]=new_item(t1,t2);
  }

  qsort(arr,n,sizeof(item),compare);

  list *head=new_list(),*tail=new_list();
  head->next=tail;
  tail->prev=head;
  int price=backtrack(arr,0,n-1,w,0,head,tail);
  printf("%d is the max price of items fitted in the bag\n",price);
}
