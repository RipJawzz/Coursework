#include<stdio.h>
#include<stdlib.h>
int* max_min(int* arr,int start,int end){
  int* mm=(int*)calloc(2,sizeof(int));
  if(start==end){
    mm[0]=arr[start-1];
    mm[1]=arr[end-1];
    return mm;
  }
  int max,min,mp=(end+start)/2;
  max=arr[mp-1];
  min=arr[mp-1];
  if(start<mp){
    mm=max_min(arr,start,mp-1);
    if(mm[0]>max)
      max=mm[0];
    if(mm[1]<min)
      min=mm[1];
    }
  if(mp<end){
    mm=max_min(arr,mp+1,end);
      if(mm[0]>max)
        max=mm[0];
      if(mm[1]<min)
        min=mm[1];
  }
  mm[0]=max;
  mm[1]=min;
  return mm;
}
void main(){
    int n;
    printf("Enter the size of the array\n");
    scanf("%d",&n);
    int* arr=(int*)calloc(n,sizeof(int));
    int* mm=(int*)calloc(2,sizeof(int));
    printf("Enter the elements\n");
    for(int i=0;i<n;i++)
      scanf("%d",&arr[i]);
    mm=max_min(arr,1,n);
    printf("Max:%d, Min:%d\n",mm[0],mm[1]);
}
