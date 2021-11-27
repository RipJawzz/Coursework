#include<stdio.h>
int Pow(int x,int n){
  if(n==1)
    return x;
  int res=Pow(x,n/2);
  res=res*res;
  if(n%2)
    res=res*x;
  return res;

}
void main(){
  int res,x,n;
  printf("Enter x and n for x^n\n");
  scanf("%d %d",&x,&n);
  res=Pow(x,n);
  printf("%d^%d=%d\n",x,n,res);
}
