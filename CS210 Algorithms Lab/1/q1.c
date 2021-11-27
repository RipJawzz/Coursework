#include<stdio.h>
#include<stdlib.h>
#define N 20
char ni=' ',fu='#';
void initiate(char arr1[N][N],int ch,int x,int y){
  switch(ch){
    case 1:
      //Boat
      if(x<=(N-3) && y<=(N-3)){
      arr1[x][y]=fu;
      arr1[x+1][y]=fu;
      arr1[x][y+1]=fu;
      arr1[x+2][y+1]=fu;
      arr1[x+1][y+2]=fu;
    }else
      printf("Out of bounds\n");
    break;
    case 2:
      //Loaf
      if(x<=(N-4) && y<=(N-4)){
      arr1[x+1][y]=fu;
      arr1[x+2][y]=fu;
      arr1[x][y+1]=fu;
      arr1[x+3][y+1]=fu;
      arr1[x+1][y+2]=fu;
      arr1[x+3][y+2]=fu;
      arr1[x+2][y+3]=fu;
    }else
      printf("Out of bounds\n");
    break;
    case 3:
        //Toad
        if(x<=(N-4) && y<=(N-3) && y>=1){
        arr1[x][y+1]=fu;
        arr1[x+1][y+1]=fu;
        arr1[x+2][y+1]=fu;
        arr1[x+1][y]=fu;
        arr1[x+2][y]=fu;
        arr1[x+3][y]=fu;
      }else
        printf("Out of bounds\n");
    break;
    case 4:
        //Beacon
        if(x<=(N-4) && y<=(N-4)){
        arr1[x][y]=fu;
        arr1[x+1][y]=fu;
        arr1[x][y+1]=fu;
        arr1[x+1][y+1]=fu;
        arr1[x+2][y+2]=fu;
        arr1[x+2][y+3]=fu;
        arr1[x+3][y+2]=fu;
        arr1[x+3][y+3]=fu;
      }else
        printf("Out of bounds\n");
    break;
    case 5:
      //Glider
      if(x<=(N-3) && y<=(N-3)){
      arr1[x][y]=fu;
      arr1[x+1][y+1]=fu;
      arr1[x+2][y+1]=fu;
      arr1[x][y+2]=fu;
      arr1[x+1][y+2]=fu;
    }else
      printf("Out of bounds\n");
    break;
    case 6:
      //LWSS
      if(x<=(N-5) && y<=(N-4)){
      arr1[x][y]=fu;
      arr1[x+3][y]=fu;
      arr1[x+4][y+1]=fu;
      arr1[x][y+2]=fu;
      arr1[x+4][y+2]=fu;
      arr1[x+1][y+3]=fu;
      arr1[x+2][y+3]=fu;
      arr1[x+3][y+3]=fu;
      arr1[x+4][y+3]=fu;
    }else
      printf("Out of bounds\n");
    break;
    //default:

  }
}
void check(char arr1[N][N],char arr2[N][N]){
  int c=0;
  for(int i=0;i<N;i++){
    for(int i1=0;i1<N;i1++){
      if(i>0 && i1>0 && arr1[i-1][i1-1]==fu)c++;
      if(i1>0 && arr1[i][i1-1]==fu)c++;
      if(i>0 && arr1[i-1][i1]==fu)c++;
      if((i+1)<N && i1>0 && arr1[i+1][i1-1]==fu)c++;
      if(i>0 && (i1+1)<N && arr1[i-1][i1+1]==fu)c++;
      if((i1+1)<N && arr1[i][i1+1]==fu)c++;
      if((i+1)<N && arr1[i+1][i1]==fu)c++;
      if((i+1)<N && (i1+1)<N && arr1[i+1][i1+1]==fu)c++;

      if(arr1[i][i1]==fu){
        if(2<=c && c<=3)
          arr2[i][i1]=fu;

      }
      else{
        if(c==3)
          arr2[i][i1]=fu;
      }
      //printf("%d",c);
      c=0;
    }
    //printf("\n");
}
  for(int i=0;i<N;i++){
    for(int i1=0;i1<N;i1++){
      arr1[i][i1]=arr2[i][i1];
      arr2[i][i1]=ni;
    }
  }
}
void main(){
  int ch=1;
  int inix,iniy;
  char arr1[N][N],arr2[N][N];
  for(int i=0;i<N;i++){
    for(int i1=0;i1<N;i1++){
      arr1[i][i1]=ni;
      arr2[i][i1]=ni;
    }
  }
  printf("Enter the choice for required object\n1:Loaf\n2:Boat\n3:Toad\n4:Beacon\n5:Glider\n6:Light Weight Spaceship\n0:To start the gamen\n");

  while(ch!=0){
    scanf("%d",&ch);
    if(ch!=0){
      printf("Enter the x<=20 and y<=20 coordinates\n");
      scanf("%d %d",&inix,&iniy);
      inix--;
      iniy--;
    }
  switch(ch){
    case 1:
      printf("Initiating Loaf\n");
      initiate(arr1,ch,inix,iniy);
    break;
    case 2:
      printf("Initiating Boat\n");
      initiate(arr1,ch,inix,iniy);
    break;
    case 3:
      printf("Initiating Toad \n");
      initiate(arr1,ch,inix,iniy);
    break;
    case 4:
      printf("Initiating Beacon\n");
      initiate(arr1,ch,inix,iniy);
    break;
    case 5:
      printf("Initiating Glider\n");
      initiate(arr1,ch,inix,iniy);
    break;
    case 6:
      printf("Initiating Light Weight Spaceship\n");
      initiate(arr1,ch,inix,iniy);
    break;
    case 0:
      printf("Starting the game\n");
    break;
    default:
      printf("Enter a valid choice!\n");
  }
}

  while(1){
    for(int i=0;i<N;i++){
      for(int i1=0;i1<N;i1++){
        printf("%c",arr1[i][i1]);
      }
      printf("\n");
    }
    check(arr1,arr2);
    printf("------------------------------------------------------------------\n");
    sleep(1);
  }
}
