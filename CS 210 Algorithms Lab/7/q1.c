#include<stdio.h>
#include<stdlib.h>
void special_sort(int** arr,int n){
  int t1,t2;
  for(int i=0;i<n;i++){
    for(int i1=0;i1<(n-i-1);i1++){
      if(arr[1][i1]>arr[1][i1+1]){
        t1=arr[0][i1];
        t2=arr[1][i1];
        arr[0][i1]=arr[0][i1+1];
        arr[1][i1]=arr[1][i1+1];
        arr[0][i1+1]=t1;
        arr[1][i1+1]=t2;
      }
    }
  }
}
void recur(int** arr,int end,int i,int n){
  if(arr[0][i]>=end){
    printf("%d %d\n",arr[0][i],arr[1][i]);
    end=arr[1][i];
  }
  i++;
  if(i<n)
    recur(arr,end,i,n);
}
void main(){
  int n;
  printf("Enter the number of tasks\n");
  scanf("%d",&n);
  int** arr=calloc(2,sizeof(int**));
  arr[0]=calloc(n,sizeof(int*));
  arr[1]=calloc(n,sizeof(int*));
  printf("Enter start and end times of the tasks\n");
  for(int i=0;i<n;i++){
    scanf("%d %d",&arr[0][i],&arr[1][i]);
  }
  special_sort(arr,n);
  printf("ORDER\n");
  recur(arr,0,0,n-1);
}
