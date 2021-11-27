#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int rand_partition(int* arr,int p,int q){
  if(p==q)
    return p;
  int tr,piv=rand()%(q-p+1)+p;
  tr=arr[piv];
  arr[piv]=arr[q];
  arr[q]=tr;
  int a=p-1,b=p;
  while(b<q){
    if(arr[b]<arr[q]){
      a++;
      tr=arr[a];
      arr[a]=arr[b];
      arr[b]=tr;
      b++;
    }
    else
      b++;
  }
    a++;
  tr=arr[q];
  arr[q]=arr[a];
  arr[a]=tr;
  return a;
}
int kth_pos(int* arr,int p,int q,int k){
  int piv=rand_partition(arr,p,q),kth;
  if(piv==k){
    kth=arr[k];
  }else
  if(piv<k){
    kth=kth_pos(arr,piv+1,q,k);
  }else
  if(k<piv){
    kth=kth_pos(arr,p,piv-1,k);
  }
  return kth;
}
void main(){
  int n,k,tr;
  printf("Enter the number of elements\n");
  scanf("%d",&n);
  int* arr=(int*)calloc(n,sizeof(int));
  printf("Enter the elements\n");
  for(int i=0;i<n;i++)
    scanf("%d",&arr[i]);
  printf("Enter the position whose element is to be found in ascending order\n");
  scanf("%d",&k);
  k--;
  srand(time(0));
  int kth=kth_pos(arr,0,n-1,k);
  printf("The %d order element is %d\n",k+1,kth);
}
