#include<stdio.h>
#include<stdlib.h>
float cost_fn(float* arr,int len,float price){
  float cost=len*price,new;
  for(int i=1;i<=len/2;i++){
    new=arr[i-1]+arr[len-i-1];
    if(new>cost)
      cost=new;
  }
  arr[len-1]=cost;
  return cost;
}
float init(int n,float price){
  float* arr=(float*)calloc(n,sizeof(float));
  float res;
  for(int i=1;i<=n;i++)
    cost_fn(arr,i,price);
  res=arr[n-1];
  free(arr);
  return res;
}
void main(){
  int n;
  float res;
  printf("Enter the length\n");
  scanf("%d",&n);
  res=init(n,1.0);
  printf("for %d length at price %f, max selling price is %f \n",n,1.0,res);
  res=init(n,0.5);
  printf("for %d length at price %f, max selling price is %f \n",n,0.5,res);
  res=init(n,0.25);
  printf("for %d length at price %f, max selling price is %f \n",n,0.25,res);
  res=init(n,0.2);
  printf("for %d length at price %f, max selling price is %f \n",n,0.2,res);
}
