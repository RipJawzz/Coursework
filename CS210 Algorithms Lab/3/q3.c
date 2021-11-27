#include<stdio.h>
#include<stdlib.h>
int count_inversion(int* arr,int len){
    int a=0,b=0,c=0,mp=len/2,i1=0,i2=0,f=0;

    int* arr1=(int*)calloc(mp,sizeof(int));
    for(int i=1;i<=mp;i++)
      arr1[i-1]=arr[i-1];
    if(mp>1)
      a=count_inversion(arr1,mp);

    int* arr2=(int*)calloc(len-mp,sizeof(int));
    for(int i=1;i<=len-mp;i++)
      arr2[i-1]=arr[i-1+mp];
    if(len-mp>1)
      b=count_inversion(arr2,len-mp);

    for(int i=0;i<len;i++){
      if((i2>=len-mp)||(i1<(mp) && arr1[i1]<=arr2[i2])){
        arr[i]=arr1[i1];
        i1++;
      }else{
        arr[i]=arr2[i2];
        c+=mp-i1;
        i2++;
      }
    }

    return a+b+c;
}
void main(){
  int n,inv;
  printf("Enter the number of elements\n");
  scanf("%d",&n);
  int* arr=(int*)calloc(n,sizeof(int));
  printf("Enter the elements\n");
  for(int i=0;i<n;i++)
    scanf("%d",&arr[i]);
  inv=count_inversion(arr,n);
  printf("\n");
  printf("inv=%d\n",inv);
}
