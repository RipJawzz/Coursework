#include<stdio.h>
#include<stdlib.h>
float cost_fn(float* arr,int len,float price){
  if(arr[len-1]!=0)
    return arr[len-1];
  if(len==1)
    arr[0]=price;
  else{
    float cost=((float)len)*price,new;
    for(int i=1;i<=len/2;i++){
      new=cost_fn(arr,i,price)+cost_fn(arr,len-i,price);
      if(new>cost)
        cost=new;
    }
    arr[len-1]=cost;
  }
  return arr[len-1];
}
void main(){
  int n;
  float res;
  printf("Enter the length\n");
  scanf("%d",&n);
  float* arr=(float*)calloc(n,sizeof(float));
  res=cost_fn(arr,n,1.0);
  printf("for %d length at price %f, max selling price is %f \n",n,1.0,res);
  free(arr);
  arr=(float*)calloc(n,sizeof(float));
  res=cost_fn(arr,n,0.5);
  printf("for %d length at price %f, max selling price is %f \n",n,0.5,res);
  free(arr);
  arr=(float*)calloc(n,sizeof(float));
  res=cost_fn(arr,n,0.25);
  printf("for %d length at price %f, max selling price is %f \n",n,0.25,res);
  free(arr);
  arr=(float*)calloc(n,sizeof(float));
  res=cost_fn(arr,n,0.2);
  printf("for %d length at price %f, max selling price is %f \n",n,0.2,res);

}
