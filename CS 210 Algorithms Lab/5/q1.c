#include<stdio.h>
float cost_fn(int len,float price){
  if(len==1)
    return 1.0*price;
  if(len==0)
    return 0.0;
  float cost=((float)len)*price,new;
  for(int i=1;i<len;i++){
    new=cost_fn(i,price)+cost_fn(len-i,price);
    if(new>cost)
      cost=new;
  }
  return cost;
}
void main(){
  int n;
  float res;
  printf("Enter size of rod\n");
  scanf("%d",&n);
  res=cost_fn(n,1.0);
  printf("for %d length at price %f, max selling price is %f \n",n,1.0,res);
  res=cost_fn(n,0.5);
  printf("for %d length at price %f, max selling price is %f \n",n,0.5,res);
  res=cost_fn(n,0.25);
  printf("for %d length at price %f, max selling price is %f \n",n,0.25,res);
  res=cost_fn(n,0.2);
  printf("for %d length at price %f, max selling price is %f \n",n,0.2,res);
}
