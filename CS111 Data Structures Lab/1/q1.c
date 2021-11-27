#include<stdio.h>
#include<stdlib.h>
void print(int* a){
	int n=sizeof(a)/4;
	for(int i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
}

int* findMinMax(int* a){
	int min=a[0],mini=0,maxi=0,max=a[0],n=sizeof(a)/4;
	for(int i=1;i<n;i++){
		if(min>a[i]){min=a[i];mini=i;}
		if(max<a[i]){max=a[i];maxi=i;}
	}
	int* b=(int*)malloc(2*sizeof(int));
	b[0]=mini;
	b[1]=maxi;
	return b;
}

void swapMinMax(int* a,int* b ){
	int temp;
	temp=a[b[1]];
	a[b[1]]=a[b[2]];
	a[b[2]]=temp;

}

int sum(int* a){
	int s=0,n=sizeof(a)/4;
	for(int i=0;i<n;i++)s+=a[i];
	return s;

}
float avg(int s,int n){
	return ((float)s/(float)n);
}
int find(int* a,int f){
	int n=sizeof(a)/4,pos=-1;
	for(int i=0;i<n;i++)
		if(a[i]==f)pos=i;
	return pos;
}
void address(int* a){
	int n=sizeof(a)/4;
	for(int i=0;i<n;i++){
		printf("%p ",(a+i));
	}
	printf("\n");
}
void main(){
	int n;
	printf("Enter the size ");
	scanf("%d",&n);
	int* a=(int*)malloc(n*sizeof(int));
	printf("Enter the elements : ");
	for(int i=0;i<n;i++)scanf(" %d",&a[i]);
	print(a);
	int* b=findMinMax(a);
	swapMinMax(a,b);
	
	int s=sum(a);
	printf("%d \n",s);
	float average=avg(s,n);
	printf("%f \n",average);
	/*printf("Enter a no to find the element : ");
	int pos,fi;
	scanf(" %d",&fi);
	pos=find(a,fi);
	printf("%d\n",pos);*/
	address(a);
	
}
