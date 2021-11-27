#include<stdio.h>
#include<stdlib.h>
typedef struct good{
  char name;
  int qty;
  float ratio;
}good;
good* new_good(char name,int q,int p){
  good* ob=(good*)malloc(1*sizeof(good));
  ob->name=name;
  ob->qty=q;
  ob->ratio=p*1.0/q*1.0;
  return (good*)ob;
}
void sort(good** arr,int n){
  good* temp=(good*)malloc(1*sizeof(good));
  for(int i=0;i<n;i++){
    for(int i1=0;i1<n-1-i;i1++){
      if(arr[i1]->ratio<arr[i1+1]->ratio){
        temp=arr[i1];
        arr[i1]=arr[i1+1];
        arr[i1+1]=temp;
      }
    }
  }
}
void main(){
  int n,p,q,size;
  char name;
  printf("Enter the number of types of goods\n");
  scanf("%d",&n);
  good** arr=(good**)malloc(n*sizeof(good*));
  printf("Enter the name, quantity and price of the goods\n");
  for(int i=0;i<n;i++){
    fflush(stdin);
    scanf("%c",&name);
    scanf("%d",&q);
    scanf("%d",&p);
    arr[i]=new_good(name,q,p);
    //printf("%c %d %f\n",arr[i]->name,arr[i]->qty,arr[i]->ratio);
  }
  sort(arr,n);
  printf("Enter the size of knapsack\n");
  scanf("%d",&size);
  int g=0;
  float price=0;
  while(size>0 && g<n){
    printf("%c ",arr[g]->name);
    size-=arr[g]->qty;
    price+=arr[g]->ratio*arr[g]->qty*1.0;
    if(size>=0)
      printf("%d-units %f-net price till now\n",arr[g]->qty,price);
    else{
      price+=(size*1.0)*arr[g]->ratio;
      printf("%d-units %f-net price till now\n",arr[g]->qty+size,price);
      size=0;
    }
    g++;
  }

}
