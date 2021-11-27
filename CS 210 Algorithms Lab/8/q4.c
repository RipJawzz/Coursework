#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
bool check_arr(int** arr,int n){
  int r,c;
  for(int i=0;i<n;i++){
    r=0;
    c=0;
    for(int i1=0;i1<n;i1++){
      r+=arr[i][i1];
      c+=arr[i1][i];
    }
    if(r>1 || c>1){
      return false;
    }
  }
  int d1,d2,d3,d4,t;
  for(int i=0;i<n;i++){
    t=i;
    d1=0;
    d2=0;
    d3=0;
    d4=0;
    for(int i1=0;i1<n,t<n;i1++,t++){
      d1+=arr[t][i1];
      d2+=arr[i1][t];
      d3+=arr[t][n-i1-1];
      d4+=arr[i1][n-t-1];
    }
    if(d1>1||d2>1||d3>1||d4>1){
    return false;
    }
  }
  return true;
}
bool check_diag(int** arr,int q_no,int x,int n){
  for(int i=1;i<n,q_no>=0;i++){
    if(((x+i)<n && arr[q_no][x+i]==1) || ((x-i)>=0 && arr[q_no][x-i]==1)){
      return false;
    }
    q_no--;
  }
  return true;
}
bool brute_queen(int** arr,int q_no,int n){
  if(q_no>n)
   return check_arr(arr,n);
 for(int i=0;i<n;i++){
   if(arr[n][i]==0 && check_diag(arr,q_no-2,i,n)){
   arr[q_no-1][i]=1;
   arr[n][i]++;
   if(brute_queen(arr,q_no+1,n)==true)
     return true;
  arr[n][i]--;
   arr[q_no-1][i]=0;
  }
 }
  return false;
}
void main(){
  int n;
  printf("Enter the number of queens(n) in the n*n chess board\n");
  scanf("%d",&n);
  int** arr=(int**)calloc(n+1,sizeof(int*));
  for(int i=0;i<=n;i++)
   arr[i]=(int*)calloc(n,sizeof(int));
   bool sol=brute_queen(arr,1,n);
   if(sol==false)
     printf("No solution exists\n");
   else{
     for(int i=0;i<n;i++){
       for(int i1=0;i1<n;i1++){
         if(arr[i][i1]==1)
           printf("Q ");
         else
           printf("_ ");
       }
       printf("\n");
     }
   }
}
