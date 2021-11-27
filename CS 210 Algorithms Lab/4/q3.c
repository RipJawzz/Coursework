 #include<stdio.h>
 #include<stdlib.h>
 void printPoly(int*,int);
 void poly_multi(int*,int*,int*,int);
 
 void main(){
   int len;
   printf("Enter the number of coeeficients, should be 2^n\n");
   scanf("%d",&len);
   int* poly1=(int*)calloc(len,sizeof(int));
   int* poly2=(int*)calloc(len,sizeof(int));
   int* poly_res=(int*)calloc(len*2-1,sizeof(int));
   printf("Enter the coefficients of the first polynomial from ^0 to ^len\n");
   for(int i=0;i<len;i++)
    scanf("%d",&poly1[i]);
  printf("Enter the coefficients of the second polynomial from ^0 to ^len\n");
    for(int i=0;i<len;i++)
     scanf("%d",&poly2[i]);
    poly_multi(poly1,poly2,poly_res,len);
    printPoly(poly_res,len*2-2);
 }
 void poly_multi(int* poly1,int* poly2,int* res,int n){
   int d=n/2;
   if(n==1){
     res[0]=poly1[0]*poly2[0];
   }else{

   int* l1=(int*)calloc(d,sizeof(int));
   int* r1=(int*)calloc(d,sizeof(int));
   int* l2=(int*)calloc(d,sizeof(int));
   int* r2=(int*)calloc(d,sizeof(int));
   for(int i=0;i<d;i++){
     l1[i]=poly1[i];
     r1[i]=poly1[i+d];
     l2[i]=poly2[i];
     r2[i]=poly2[i+d];
   }
   int* lr1=(int*)calloc(d,sizeof(int));
   int* lr2=(int*)calloc(d,sizeof(int));
   for(int i=0;i<d;i++){
     lr1[i]=l1[i]+r1[i];
     lr2[i]=l2[i]+r2[i];
   }
   int* l1l2=(int*)calloc(2*d-1,sizeof(int));
   poly_multi(l1,l2,l1l2,d);
   int* r1r2=(int*)calloc(2*d-1,sizeof(int));
   poly_multi(r1,r2,r1r2,d);
   int* lr=(int*)calloc(2*d-1,sizeof(int));
   poly_multi(lr1,lr2,lr,d);
   for(int i=0;i<n-1;i++){
     res[i]+=l1l2[i];
     res[i+d]+=lr[i]-l1l2[i]-r1r2[i];
     res[i+2*d]+=r1r2[i];
   }
 }
}
 void printPoly(int* poly,int len){
   for(int i=len;i>=0;i--)
    printf("%dx^%d ",poly[i],i);
    printf("\n");
 }
