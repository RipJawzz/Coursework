#include<stdio.h>
#include<stdlib.h>
int* Max_subArray(int* arr,int start,int end){
  if(start==end){
    int* res3=(int*)calloc(3,sizeof(int));
    res3[0]=start;
    res3[1]=end;
    res3[2]=arr[end-1];
    return res3;
  }
  else{
    int* res1=(int*)calloc(3,sizeof(int));
    int* res2=(int*)calloc(3,sizeof(int));
    int* res3=(int*)calloc(3,sizeof(int));
    int mp=(end+start)/2,sum,summ;
    if(mp>start)
      res1=Max_subArray(arr,start,mp-1);
    if(end>mp)
      res2=Max_subArray(arr,mp+1,end);
    res3[2]=arr[mp-1];
    res3[0]=mp;
    res3[1]=mp;
    sum=0;
    summ=0;
    for(int i=mp-1;i>=1;i--){
      sum+=arr[i-1];
      if(sum>summ){
        res3[0]=i;
        summ=sum;
      }
    }
    res3[2]+=summ;
    sum=0;
    summ=0;
    for(int i=mp+1;i<=end;i++){
      sum+=arr[i-1];
      if(sum>summ){
        res3[1]=i;
        summ=sum;
      }
    }
    res3[2]+=summ;
    if(res1[2]>res2[2]){
      if(res1[2]>res3[2])
        return res1;
    }else{
      if(res2[2]>res3[2])
      return res2;
    }
    return res3;
  }
}
void main(){
  int n;
  int* res=(int*)calloc(3,sizeof(int));
  printf("Enter the length of the array\n");
  scanf("%d",&n);
  printf("Enter the elements\n");
  int* arr=(int*)calloc(n,sizeof(int));
  for(int i=0;i<n;i++)
    scanf("%d",&arr[i]);
  res=Max_subArray(arr,1,n);
  printf("Max sum=%d\nStart=%d\nEnd=%d\n",res[2],res[0],res[1]);
}
