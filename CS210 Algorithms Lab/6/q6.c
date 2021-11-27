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
void recur(int** arr,int** res,int sol,int end,int i,int n){
  if(arr[0][i]>=end){
    res[0][sol]=arr[0][i];
    res[1][sol]=arr[1][i];
    sol++;
    end=arr[1][i];
  }
  i++;
  if(i<n)
    recur(arr,res,sol,end,i,n);
  else
    res[1][n+1]=sol;
}
void main(){
  int n;
  printf("Enter the number of tasks\n");
  scanf("%d",&n);
  int** arr=calloc(2,sizeof(int**));
  arr[0]=calloc(n,sizeof(int*));
  arr[1]=calloc(n,sizeof(int*));
  int** res=calloc(2,sizeof(int**));
  res[0]=calloc(n,sizeof(int*));
  res[1]=calloc(n+1,sizeof(int*));
  printf("Enter start and end times of the tasks\n");
  for(int i=0;i<n;i++){
    scanf("%d %d",&arr[0][i],&arr[1][i]);
  }
  special_sort(arr,n);
  printf("ORDER\n");
  recur(arr,res,0,0,0,n-1);
  for(int i=0;i<res[1][n];i++)
    printf("%d %d\n",res[0][i],res[1][i]);
}
