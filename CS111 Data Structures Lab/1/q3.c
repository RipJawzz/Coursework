#include<stdio.h>
#include<stdio.h>
struct matrix{
		int x;
		int y;
	};

int* allocate(int a,int b1){
	int* b=(int *)calloc(a*b1,sizeof(int));
	
	return b;
}
void value(int* a,int x,int y){
	printf("enter the values\n");	
	for(int i=0;i<x;i++){
		for(int i1=0;i1<y;i1++){
			printf("matrix[%d][%d] : ",i,i1);
			scanf(" %d",a+i1+i*y);
		}	
	}
}
void multiply(int* a1,int* b1,int* c1,int x,int y, int z){
		
	for(int i=0;i<x;i++){
		for(int i1=0;i1<y;i1++){
				for(int w=0;w<z;w++){
					*(c1+i*y+i1)+=*(a1+i*z+w)*(*(b1+w*z+i1));				
				}									
		}	
	}
}
void print(int *a,int x,int y){
	for(int i=0;i<x;i++){
		for(int i1=0;i1<y;i1++){
			printf("%d ",*(a+i*y+i1));
		}
		printf("\n");
	}

}
void main(){
	
	struct matrix a,b,c;
	printf("Enter the dimensions of the matrix as m*n : ");
	scanf(" %d",&a.x);
	scanf(" %d",&a.y);
	scanf(" %d",&b.x);
	scanf(" %d",&b.y);
	int* am,bm,cm;
	am=allocate(a.x,a.y);
	bm=allocate(b.x,b.y);
	c.x=a.x;c.y=b.y;	
	cm=allocate(c.x,c.y);
	value(am,a.x,a.y);
	print(am,a.x,a.y);
	value(bm,b.x,b.y);
	print(bm,b.x,b.y);

	multiply(am,bm,cm,a.x,b.y,a.y);
	print(cm,c.x,c.y);
}
