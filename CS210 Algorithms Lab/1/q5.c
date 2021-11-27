#include<stdio.h>
#include<stdlib.h>

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
  int n1,n2,m1,m2,nf,mf,offset,dig=0,carry=0;
  char s1,s2,sf;
  printf("Enter the size of the two real numbers without decimal:\n");
  scanf("%d %d",&n1,&n2);
  n1++;
  n2++;

  char* int1=(char*)calloc(n1,sizeof(char));
  char* int2=(char*)calloc(n2,sizeof(char));

  printf("Enter the two real numbers with their signs in the order as their sizes \nwere enterd above in the format (n m)=n*10^-m where n is an integer and m is the mentessa.\nDont contract n\n");
  scanf("%s %d %s %d",int1,&m1,int2,&m2);

  mf=(m1>m2)?m1:m2;
  nf=((n1-m1)>n2-m2)?n1-m1:n2-m2;
  nf+=mf-1;
  char* intf=(char*)calloc(nf,sizeof(char));
  for(int i=0;i<nf;i++)
    intf[i]='0';

  s1=int1[0];
  s2=int2[0];
  printf("%c %c\n",s1,s2);
  if(n1-m1>n2-m2)
    sf=s1;
  else if(n1-m1<n2-m2)
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
      for(int i=1;i<(n1>n2)?n1:n2;i++){
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
  offset=(m1>m2)?m1-m2:m2-m1;
    for(int i=1;i<=nf;i++){
        /*printf("i:----------------%d\n",i);
        printf("a:%d %d %d\n",m1,mf-i,n1);
        printf("b:%d %d %d\n",m2,mf-i,n2);*/
        if(m1>(mf-i)&&(i-mf)<(n1-m1)){
          //printf("a  %c\n",int1[n1-(i-mf+m1)]);
          if(s1=='+')
            dig+=int1[n1-(i-mf+m1)]-48;
            else
            dig-=int1[n1-(i-mf+m1)]-48;
        }
        //printf("dig %d\n",dig);
        if(m2>(mf-i)&&(i-mf)<(n2-m2)){
          //printf("b\n");
          if(s2=='+')
            dig+=int2[n2-(i-mf+m2)]-48;
          else
            dig-=int2[n2-(i-mf+m2)]-48;
        }
          //printf("dig %d\n",dig);
        dig+=carry;
        if(dig<0){
          //printf("c\n");
          dig+=10;
          carry=-1;
        }
        else{
          //printf("d\n");
          carry=dig/10;
          dig=dig%10;
        }
        //printf("\n%d %d\n",dig,carry);
        intf[nf-i]=dig+48;
        dig=0;

    }

  //printf("%c",sf);
    if(carry==-1)
      nine_complement(intf,nf);
    else if(carry!=0)
      printf("%d",carry);
    printf("%s*10^-%d\n",intf,mf);

}
