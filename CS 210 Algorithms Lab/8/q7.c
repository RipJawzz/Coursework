#include<stdio.h>
#include<stdlib.h>
int brute_knapsack(int** arr,int* w,int size,int ob,int num_ob){
  if(ob==num_ob)
    return 0;
  int w1=*w+arr[0][ob],w2=*w;
  int p1=arr[1][ob],p2=0;
  if(w1<=size)
  p1+=brute_knapsack(arr,&w1,size,ob+1,num_ob);
  p2+=brute_knapsack(arr,&w2,size,ob+1,num_ob);
  if(w1<=size && p1>p2){
    *w=w1;
    return p1;
  }
  *w=w2;
  return p2;
}
void main(){
  int size,num_ob,p_max,w=0;
  printf("Enter the size of the knapsack and the number of weights\n");
  scanf("%d",&size);
  scanf("%d",&num_ob);
  printf("Enter the weight and price of the objects\n");

  int** arr=(int**)calloc(2,sizeof(int*));
  arr[0]=(int*)calloc(num_ob,sizeof(int));
  arr[1]=(int*)calloc(num_ob,sizeof(int));

  for(int i=0;i<num_ob;i++)
    scanf("%d %d",&arr[0][i],&arr[1][i]);

  p_max=brute_knapsack(arr,&w,size,0,num_ob);
  printf("Max price is %d and the weight filled is %d out of %d\n",p_max,w,size);
}
