#include<stdio.h>
#include<math.h>
void main(){
  int n,min_h=0,max_h=0,t;
  printf("Enter n(the number of nodes in the AVL tree)\n");
  scanf("%d",&n);
  if(n!=0){
    t=(log2(n*1.0+1));
    min_h=(int)(t);
    if(min_h==t)
      min_h--;
    max_h=(int)(1.44*log2(n*1.0));
  }
  printf("Min:(1).%d (2).%d\n",min_h,min_h+1);
  printf("Max:(1).%d (2).%d\n",max_h,max_h+1);
}
