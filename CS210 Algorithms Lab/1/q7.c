#include<stdio.h>
#include<stdlib.h>
void add(char* intf,char* int1,int offset,int n1,int nf){
  int dig=0,carry=0;
  for(int i=1;i<=nf;i++){
      if(i<n1)dig+=int1[n1-i]-48;
      dig+=intf[nf-i-offset]-48;
      dig+=carry;
      carry=dig/10;
      dig=dig%10;
      intf[nf-i-offset]=dig+48;
      dig=0;
      if(i>n1 && carry==0)
        break;
  }
}
void main(){
  int n1,n2,m1,m2,nf,mf,ti;
  char s1,s2,sf;
  printf("Enter the size of the two real numbers without decimal:\n");
  scanf("%d %d",&n1,&n2);

  nf=n1*n2;
  if(n1==1||n2==1)
    nf++;
  n1++;
  n2++;
  char* int1=(char*)calloc(n1,sizeof(char));
  char* int2=(char*)calloc(n2,sizeof(char));
  char* intf=(char*)calloc(nf,sizeof(char));
  char* tc=NULL;

  for(int i=0;i<nf;i++)
    intf[i]='0';
    printf("%s\n",intf);
  printf("Enter the two real numbers with their signs in the order as their sizes \nwere enterd above in the format (n m)=n*10^-m where n is an integer and m is the mentessa.\nDon't contract the integer\n");
  scanf("%s %d %s %d",int1,&m1,int2,&m2);
  printf("%s %d\n",int2,m2);
  mf=m1+m2;
  s1=int1[0];
  s2=int2[0];
  if(s1==s2)
    sf='+';
    else
    sf='-';

  if(n1<n2){
    ti=n1;
    n1=n2;
    n2=ti;
    tc=int1;
    int1=int2;
    int2=tc;
  }

  for(int i=1;i<n2;i++){
    for(int i1=0;i1<int2[n2-i]-48;i1++){
      printf("%d %d %s\n",i,i1,intf);
      add(intf,int1,i-1,n1,nf);
    }
  }
  printf("%c%s*10^-%d\n",sf,intf,mf);
}
