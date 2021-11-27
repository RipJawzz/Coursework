#include<stdio.h>
#include<stdlib.h>
#  define INT_MAX   2147483647

int multi(int** arr,int** bkt,int p, int q,int check){
  int cost=INT_MAX,temp,k;
  if(p==q)
    return 0;
  for(int i=p;i<q;i++){
    temp=multi(arr,bkt,p,i,0)+multi(arr,bkt,i+1,q,0)+arr[0][p]*arr[1][q]*arr[1][i];
    if(temp<cost){
      cost=temp;
      k=i;
    }
  }
  if(check==1){
    temp=multi(arr,bkt,p,k,1)+multi(arr,bkt,k+1,q,1);
    bkt[0][p]++;
    bkt[1][q]++;
  }
  return cost;
}

void main(){
  int n,cost;
  printf("Enter the number of matrix\n");
  scanf("%d",&n);
  printf("Enter the dimensions of each matrix in order\n");

  int** arr=(int**)calloc(2,sizeof(int*));
  arr[0]=(int*)calloc(n,sizeof(int));
  arr[1]=(int*)calloc(n,sizeof(int));

  int** bkt=(int**)calloc(2,sizeof(int*));
  //0 open, 1 close
  bkt[0]=(int*)calloc(n,sizeof(int));
  bkt[1]=(int*)calloc(n,sizeof(int));

  for(int i=0;i<n;i++){
    printf("Enter dim of %c:\n",i+65);
    scanf("%d %d",&arr[0][i],&arr[1][i]);
  }

  cost=multi(arr,bkt,0,n-1,1);

  for(int i=0;i<n;i++){
    for(int i1=0;i1<bkt[0][i];i1++)
      printf("(");
    printf("%c",i+65);
    for(int i1=0;i1<bkt[1][i];i1++)
      printf(")");
  }

  printf("\n");
  printf("The cost is %d\n",cost);
}
