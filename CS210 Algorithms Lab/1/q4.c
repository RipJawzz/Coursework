#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void nine_complement(char* arr,int n){
  for(int i=0;i<=n-1;i++)
    arr[i]='9'-arr[i]+48;
  for(int i=n-1;i>=0;i--){
    if(arr[i]=='9')
      arr[i]='0';
    else{
      arr[i]++;
      break;
    }
  }
}

void main(){
  int n1,n2,nf,nl,carry=0,dig=0;
  char s1='+',s2='+',sf='+';
  printf("Enter the number of digits in the 1st & 2nd integer\n");
  scanf("%d %d",&n1,&n2);

  nf=(n1>n2)?n1:n2;
  nl=(n1>n2)?n1:n2;
  n1++;
  n2++;
  char* int1=(char*)calloc(n1,sizeof(char));
  char* int2=(char*)calloc(n2,sizeof(char));
  char* intf=(char*)calloc(nf,sizeof(char));

  printf("Enter the 2 numbers in the order as their length were given above with sign:\n");
  scanf("%s %s",int1,int2);

  s1=int1[0];
  s2=int2[0];
  if(n1>n2)
    sf=s1;
  else if(n1<n2)
    sf=s2;
  else{
    if(s1==s2){
      sf=s1;
      if(sf=='-'){
        s1='+';
        s2='+';
      }
    }
    else{
      for(int i=1;i<n1;i++){
        if(int1[i]>int2[i]){
          sf=s1;
          break;
        }else
        if(int1[i]<int2[i]){
          sf=s2;
          break;
        }
      }
    }
  }

  for(int i=1;i<=nf;i++){
    printf("%d:\n",i);
      if(i<n1){
        if(s1=='+')
          dig+=int1[n1-i]-48;
          else
          dig-=int1[n1-i]-48;
      }
      if(i<n2){
        if(s2=='+')
          dig+=int2[n2-i]-48;
        else
          dig-=int2[n2-i]-48;
      }
      dig+=carry;
      if(dig<0){
        dig+=10;
        carry=-1;
      }
      else{
        carry=dig/10;
        dig=dig%10;
      }
      intf[nf-i]=dig+48;
      printf("%d %d\n",dig,carry);
      dig=0;

  }

  printf("%c",sf);
  if(carry==-1)
    nine_complement(intf,nf);
  else if(carry!=0)
    printf("%d",carry);
  printf("%s\n",intf);
}
