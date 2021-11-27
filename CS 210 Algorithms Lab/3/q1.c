#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
void set(int**,int,int);
void mul_n3(int**,int**,int**,int);
void div_conquer(int**,int**,int**,int);
void add_matrix(int**,int**,int**,int);
void print_matrix(int**,int);
void sub_matrix(int**,int**,int**,int);
void strassen(int**,int**,int,int,int**);

void main(){
  clock_t start,end;
  double time_taken;
  int k,dim,choice;
  printf("Enter k for the time analysis\n");
  scanf("%d",&k);
  dim=pow(2,k);

  int** matrix1=(int** )calloc(dim,sizeof(int*));
  int** matrix2=(int** )calloc(dim,sizeof(int*));
  int** matrix3=(int** )calloc(dim,sizeof(int*));

  for(int i=0;i<dim;i++){
    matrix1[i]=(int*)calloc(dim,sizeof(int));
    matrix2[i]=(int*)calloc(dim,sizeof(int));
    matrix3[i]=(int*)calloc(dim,sizeof(int));
  }

  set(matrix1,dim,10);
  set(matrix2,dim,10);
  //printf("Enter 1 for normal matrix_mul, 2 for Div and conq, 3 for strassen\n");
  //scanf("%d",&choice);
  printf("1st matrix\n");
  print_matrix(matrix1,dim);
  printf("\n");
  printf("2nd matrix\n");
  print_matrix(matrix2,dim);
  printf("\n");

  /*switch(choice){
    case 1:
    mul_n3(matrix1,matrix2,matrix3,dim);
    printf("normal multi done\n");
    print_matrix(matrix3,dim);
    break;
    case 2:
    div_conquer(matrix1,matrix2,matrix3,dim);
    printf("divide and conquer done\n");
    print_matrix(matrix3,dim);
    break;
    case 3:
    strassen(matrix1,matrix2,dim,dim,matrix3);
    printf("strassen done\n");
    print_matrix(matrix3,dim);
    break;
    default:
      printf("What do you expect after entering anthing other that 1/2/3?\n");
  }*/
    start=clock();
    mul_n3(matrix1,matrix2,matrix3,dim);
    end=clock();
    time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken in normal multi is %f units\n",time_taken);
    printf("normal multi done\n");
    //print_matrix(matrix3,dim);

    start=clock();
    div_conquer(matrix1,matrix2,matrix3,dim);
    end=clock();
    time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken div_conquer is %f units\n",time_taken);
    printf("divide and conquer done\n");
    //print_matrix(matrix3,dim);

    start=clock();
    strassen(matrix1,matrix2,dim,dim,matrix3);
    end=clock();
    time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken in strassen is %f units\n",time_taken);
    printf("strassen done\n");
    //print_matrix(matrix3,dim);

}
void sub_matrix(int** m1,int** m2,int** m3,int dim){
  for(int i=0;i<dim;i++){
    for(int i1=0;i1<dim;i1++){
      m3[i1][i]=m1[i1][i]-m2[i1][i];
    }
  }
}
void strassen(int**c,int** d, int size,int size2,int** result){
  if(size == 1)
  {
      result[0][0] = c[0][0] *d[0][0];
  }
  else {
      int i,j;
      int siZE =size/2;
      int **c11 = malloc(siZE * sizeof(int *));
      int **c12 = malloc(siZE * sizeof(int *));
      int **c21 = malloc(siZE * sizeof(int *));
      int **c22 = malloc(siZE * sizeof(int *));
      int **d11 = malloc(siZE * sizeof(int *));
      int **d12 = malloc(siZE * sizeof(int *));
      int **d21 = malloc(siZE * sizeof(int *));
      int **d22 = malloc(siZE * sizeof(int *));
      int **m1 = malloc(siZE * sizeof(int *));
      int **m2 = malloc(siZE * sizeof(int *));
      int **m3 = malloc(siZE * sizeof(int *));
      int **m4 = malloc(siZE * sizeof(int *));
      int **m5 = malloc(siZE * sizeof(int *));
      int **m6 = malloc(siZE * sizeof(int *));
      int **m7 = malloc(siZE * sizeof(int *));
      int **temp1 = malloc(siZE * sizeof(int *));
      int **temp2 = malloc(siZE * sizeof(int *));
      int **temp3 = malloc(siZE * sizeof(int *));
      int **temp4 = malloc(siZE * sizeof(int *));
      int **temp5 = malloc(siZE * sizeof(int *));
      int **temp6 = malloc(siZE * sizeof(int *));
      int **temp7 = malloc(siZE * sizeof(int *));
      int **temp8 = malloc(siZE * sizeof(int *));
      int **temp9 = malloc(siZE * sizeof(int *));
      int **temp10 = malloc(siZE * sizeof(int *));
      int **tempo = malloc(siZE * sizeof(int *));
      int **tempo1 = malloc(siZE * sizeof(int *));
      int **tempo2 = malloc(siZE * sizeof(int *));
      int **tempo3 = malloc(siZE * sizeof(int *));
      int **tempo4 = malloc(siZE * sizeof(int *));
      int **tempo5 = malloc(siZE * sizeof(int *));
      int **tempo6 = malloc(siZE * sizeof(int *));
      int **tempo7 = malloc(siZE * sizeof(int *));


      for(i=0;i<siZE;i++)
      {
          c11[i]= malloc(siZE*sizeof(int));
          c12[i]= malloc(siZE*sizeof(int));
          c21[i]= malloc(siZE*sizeof(int));
          c22[i]= malloc(siZE*sizeof(int));
          d11[i]= malloc(siZE*sizeof(int));
          d12[i]= malloc(siZE*sizeof(int));
          d21[i]= malloc(siZE*sizeof(int));
          d22[i]= malloc(siZE*sizeof(int));
          m1[i]= malloc(siZE*sizeof(int));
          m2[i]= malloc(siZE*sizeof(int));
          m3[i]= malloc(siZE*sizeof(int));
          m4[i]= malloc(siZE*sizeof(int));
          m5[i]= malloc(siZE*sizeof(int));
          m6[i]= malloc(siZE*sizeof(int));
          m7[i]= malloc(siZE*sizeof(int));
        temp1[i]= malloc(siZE*sizeof(int));
          temp2[i]= malloc(siZE*sizeof(int));
          temp3[i]= malloc(siZE*sizeof(int));
          temp4[i]= malloc(siZE*sizeof(int));
          temp5[i]= malloc(siZE*sizeof(int));
          temp6[i]= malloc(siZE*sizeof(int));
          temp7[i]= malloc(siZE*sizeof(int));
          temp8[i]= malloc(siZE*sizeof(int));
          temp9[i]= malloc(siZE*sizeof(int));
          temp10[i]= malloc(siZE*sizeof(int));
          tempo[i]= malloc(siZE*sizeof(int));
          tempo1[i]= malloc(siZE*sizeof(int));
          tempo2[i]= malloc(siZE*sizeof(int));
          tempo3[i]= malloc(siZE*sizeof(int));
          tempo4[i]= malloc(siZE*sizeof(int));
          tempo5[i]= malloc(siZE*sizeof(int));
          tempo6[i]= malloc(siZE*sizeof(int));
          tempo7[i]= malloc(siZE*sizeof(int));
      }
      for(i=0;i<siZE;i++)
      {
          for(j=0;j<siZE;j++)
          {
              c11[i][j]=c[i][j];
              c12[i][j]=c[i][j+siZE];
              c21[i][j]=c[i+siZE][j];
              c22[i][j]=c[i+siZE][j+siZE];
              d11[i][j]=d[i][j];
              d12[i][j]=d[i][j+siZE];
              d21[i][j]=d[i+siZE][j];
              d22[i][j]=d[i+siZE][j+siZE];
          }
      }

      add_matrix(c11,c22,temp1,siZE);
      add_matrix(d11,d22,temp2,siZE);
      strassen(temp1,temp2,siZE,size,m1);

      add_matrix(c21,c22,temp3,siZE);
      strassen(temp3,d11,siZE,size,m2);

      sub_matrix(d12,d22,temp4,siZE);
      strassen(c11,temp4,siZE,size,m3);

      sub_matrix(d21,d11,temp5,siZE);
      strassen(c22,temp5,siZE,size,m4);

      add_matrix(c11,c12,temp6,siZE);
      strassen(temp6,d22,siZE,size,m5);



      sub_matrix(c21,c11,temp7,siZE);
      add_matrix(d11,d12,temp8,siZE);
      strassen(temp7,temp8,siZE,size,m6);

      sub_matrix(c12,c22,temp9,siZE);
      add_matrix(d21,d22,temp10,siZE);
      strassen(temp9,temp10,siZE,size,m7);

      add_matrix(m1,m7,tempo,siZE);
      sub_matrix(m4,m5,tempo1,siZE);
      add_matrix(tempo,tempo1,tempo2,siZE);

      add_matrix(m3,m5,tempo3,siZE);
      add_matrix(m2,m4,tempo4,siZE);

      add_matrix(m3,m6,tempo5,siZE);
      sub_matrix(m1,m2,tempo6,siZE);

      add_matrix(tempo5,tempo6,tempo7,siZE);

      int a=0;
      int b=0;
      int c=0;
      int d=0;
      int e=0;
      int sizex= 2*siZE;
      for(i=0;i<sizex;i++)
      {
          for(j=0;j<sizex;j++)
          {
              if(j>=0 && j<siZE && i>=0 && i<siZE)
              {
                  result[i][j] = tempo2[i][j];
              }
              if(j>=siZE && j<sizex && i>=0 && i<siZE)
              {
                  a=j-siZE;
                  result[i][j] = tempo3[i][a];
              }
              if(j>=0 && j<siZE && i>= siZE && i < sizex)
              {
                  c=i-siZE;
                  result[i][j] = tempo4[c][j];
              }
              if(j>=siZE && j< sizex && i>= siZE && i< sizex )
              {
                  d=i-siZE;
                  e=j-siZE;
                  result[i][j] =tempo7[d][e];
              }
          }
      }

  }
}
void div_conquer(int** a,int** b,int** c,int dim){
  if(dim==1)
    c[0][0]=b[0][0]*a[0][0];
  else{
    int **a00 = malloc(dim/2 * sizeof(int *));
    int **a10 = malloc(dim/2 * sizeof(int *));
    int **a11 = malloc(dim/2 * sizeof(int *));
    int **a01= malloc(dim/2 * sizeof(int *));
    int **b00 = malloc(dim/2 * sizeof(int *));
    int **b01 = malloc(dim/2 * sizeof(int *));
    int **b11 = malloc(dim/2 * sizeof(int *));
    int **b10 = malloc(dim/2 * sizeof(int *));
    int **c00 = malloc(dim/2 * sizeof(int *));
    int **c01= malloc(dim/2 * sizeof(int *));
    int **c10= malloc(dim/2 * sizeof(int *));
    int **c11= malloc(dim/2 * sizeof(int *));
    int **first = malloc(dim/2 * sizeof(int *));
    int **second= malloc(dim/2 * sizeof(int *));

for(int i=0;i<dim/2;i++){

    a00[i] = malloc(dim/2*sizeof(int));
    a01[i] = malloc(dim/2*sizeof(int));
    a10[i] = malloc(dim/2*sizeof(int));
    a11[i] = malloc(dim/2*sizeof(int));

    b00[i] = malloc(dim/2*sizeof(int));
    b01[i] = malloc(dim/2*sizeof(int));
    b10[i] = malloc(dim/2*sizeof(int));
    b11[i] = malloc(dim/2*sizeof(int));

     c00[i] = malloc(dim/2*sizeof(int));
     c01[i] = malloc(dim/2*sizeof(int));
     c10[i] = malloc(dim/2*sizeof(int));
     c11[i] = malloc(dim/2*sizeof(int));

     first[i] = malloc(dim/2*sizeof(int));
      second[i] = malloc(dim/2*sizeof(int));

}


for(int i=0;i<dim/2;i++){
  for(int j = 0;j<dim/2;j++){
    a00[i][j] = a[i][j];
    a01[i][j] = a[i][j + dim/2];
    a10[i][j] = a[i + dim/2][j];
    a11[i][j] = a[i + dim/2][j + dim/2];

    b00[i][j] = b[i][j];
    b01[i][j] = b[i][j + dim/2];
    b10[i][j] = b[i + dim/2][j];
    b11[i][j] = b[i + dim/2][j + dim/2];
  }
}

div_conquer(a00,b00,first,dim/2);
div_conquer(a01,b10,second,dim/2);
add_matrix(first,second,c00,dim/2);

div_conquer(a00,b01,first,dim/2);
div_conquer(a01,b11,second,dim/2);
add_matrix(first,second,c01,dim/2);

  div_conquer(a10,b00,first,dim/2);
div_conquer(a11,b10,second,dim/2);
add_matrix(first,second,c10,dim/2);

div_conquer(a10,b01,first,dim/2);
div_conquer(a11,b11,second,dim/2);
add_matrix(first,second,c11,dim/2);

for(int i=0;i<dim/2;i++){
  for(int j = 0;j<dim/2;j++){

    c[i][j] = c00[i][j];
    c[i][j + dim/2] = c01[i][j];
    c[i + dim/2][j] = c10[i][j];
    c[i + dim/2][j + dim/2] = c11[i][j];
  }
}
  }
}
void print_matrix(int** matrix,int dim){
  for(int i=0;i<dim;i++){
    for(int i1=0;i1<dim;i1++)
      printf("%d ",matrix[i][i1]);
    printf("\n");
  }
}
void add_matrix(int** m1,int** m2,int** m3,int n){
  for(int i=0;i<n;i++){
    for(int i1=0;i1<n;i1++){
      m3[i][i1]=m1[i][i1]+m2[i][i1];
    }
  }
}
void mul_n3(int** m1,int** m2,int** m3,int dim){
  for(int i0=0;i0<dim;i0++)
    for(int i1=0;i1<dim;i1++)
      for(int i2=0;i2<dim;i2++){
        m3[i0][i1]+=m1[i0][i2]*m2[i2][i1];
      }
}
void set(int** matrix,int dim,int num){
  srand(time(0));
  for(int i=0;i<dim;i++)
    for(int i1=0;i1<dim;i1++)
      matrix[i][i1]=rand()%10;
}
