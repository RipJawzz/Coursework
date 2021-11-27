#include<stdio.h>
#include<stdlib.h>
#  define INT_MAX   2147483647

void place_bkt(int** bt ,int** bkt, int p,int q){
  int k=bt[p][q];
  bkt[0][p]++;
  bkt[1][q]++;
  if(p<k)
  place_bkt(bt,bkt,p,k);
  if(k+1<q)
  place_bkt(bt,bkt,k+1,q);
}

void div_(int** arr,int**bt,int** ct,int p,int q){
  int cost=INT_MAX,k,temp;
  for(int i=p;i<q;i++){
    temp=ct[p][i]+ct[i+1][q]+arr[0][p]*arr[1][q]*arr[1][i];
    if(cost>temp){
      cost=temp;
      k=i;
    }
  }
  ct[p][q]=cost;
  bt[p][q]=k;
}

void multi(int** arr,int** bt, int** ct,int n){
  int it;
  for(int i=1;i<n;i++){
    it=i;
    for(int i1=0;i1<n,it<n;i1++,it++){
      div_(arr,bt,ct,i1,it);
    }
  }
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

  //cost dp array
  int** ct=(int**)calloc(n,sizeof(int*));
  for(int i=0;i<n;i++)
    ct[i]=(int*)calloc(n,sizeof(int));

    //bkt dp
    int** bt=(int**)calloc(n,sizeof(int*));
    for(int i=0;i<n;i++)
      bt[i]=(int*)calloc(n,sizeof(int));


  for(int i=0;i<n;i++){
    printf("Enter dim of %c:\n",i+65);
    scanf("%d %d",&arr[0][i],&arr[1][i]);
  }

  multi(arr,bt,ct,n);
  place_bkt(bt,bkt,0,n-1);

  for(int i=0;i<n;i++){
    for(int i1=0;i1<n;i1++)
      printf("%d ",ct[i][i1]);
    printf("\n");
  }

  for(int i=0;i<n;i++){
    for(int i1=0;i1<bkt[0][i];i1++)
      printf("(");
    printf("%c",i+65);
    for(int i1=0;i1<bkt[1][i];i1++)
      printf(")");
  }

  printf("\n");
  printf("The cost is %d\n",ct[0][n-1]);
}
