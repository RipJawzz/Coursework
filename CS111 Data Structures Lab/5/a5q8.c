#include<stdio.h>
#include<stdlib.h>
int BS(int* arr,int st,int en,int ob){
	int m=(st+en)/2;
	if(st==en){
		printf("%d\n",st);
		if(ob==arr[st])return st;	
		else return -1;
	}
	if(ob<=arr[m])m=BS(arr,st,m,ob);
	else m=BS(arr,m+1,en,ob);
	return m;
}
void main(){
	int size,ob,ind=-1;
	printf("Enter the size:\n");
	scanf("%d",&size);
	int* arr=(int*)malloc(size*sizeof(int));
	printf("Enter the elements\n");
	for(int i=0;i<size;i++)scanf("%d",&arr[i]);
	printf("Enter the ele to be found\n");
	scanf("%d",&ob);
	ind=BS(arr,0,size-1,ob);
	printf("The ele has been found in %d\n",ind);
}
