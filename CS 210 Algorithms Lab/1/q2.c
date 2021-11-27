#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void sort(int* arr, int n){
  int t,min;
  for(int i=n-1;i>=0;i--){
    min=0;
    for(int i1=0;i1<i;i1++){
      if(arr[i1]<arr[i1+1]){
        t=arr[i1];
        arr[i1]=arr[i1+1];
        arr[i1+1]=t;
      }
    }
  }
}
void main(){
 int n,min_h,max_h=0;
 float t;
 printf("Enter the number of integers.\n");
 scanf("%d",&n);
 int* arr=(int*)calloc(n,sizeof(int));
 printf("Enter the number:\n");
 for(int i=0;i<n;i++)
  scanf("%d",&arr[i]);
sort(arr,n);
printf("Inorder traversal of the BST:");
for(int i=0;i<n;i++)
  printf("%d ",arr[i]);
printf("\n");
if(n!=0)
  max_h=n--;

t=(log2(n*1.0+1));
min_h=(int)(t);
if(min_h==t)
  min_h--;
printf("Max height=%d\nMin height=%d\n",max_h,min_h);
}
