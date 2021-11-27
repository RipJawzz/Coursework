#include<stdio.h>
#include<math.h>
int len_num(long long int a){
  if(a<1)
    return 0;
  return (int)log10(a)+1;
}
long long int mul(long long int a,long long int b){
  int i=1;
  if(a<0){
    i=-i;
    a=-a;
  }
  if(b<0){
    i=-i;
    b=-b;
  }
  int l=len_num(a),h=l/2;
  float p1=pow(10,h),p2=pow(10,2*h);
  long long int d1=(long long int)p1,d2=(long long int)p2;
  if(l<=1)
    return (long long int)i*a*b;
  long long int res,al=a/d1,ar=a%d1,bl=b/d1,br=b%d1;
  res=i*(mul(al,bl)*(d2+d1)+(1+d1)*mul(ar,br)+mul(al-ar,br-bl)*d1);
  printf("%lld %lld: %lld,%lld %lld,%lld %d %d res=%lld\n",a,b,al,ar,bl,br,l,h,res);
  return res;
}
void main(){
  long long int a=0,b=0;
  printf("Enter the two numbers (same length)\n");
  scanf("%lld",&a);
  scanf("%lld",&b);
  a=mul(a,b);
  printf("The product is %lld\n",a);
}
