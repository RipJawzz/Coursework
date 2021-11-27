#include<stdio.h>
#include<stdlib.h>
int flag=0,n=0;
void printall(int *arr){
	//printf("Order\n");
	for(int i=0;i<n;i++){
		printf("%d ",arr[i]);
	}
	/*printf("\nNumber\n");
	
	for(int i=0;i<n;i++){
		printf("%d ",t[i]);
	}*/
	printf("\n");
}
void incr(int* arr,int* t,int i){
	//printf("i=%d\n",i);
	
	//if(i==n-1 && arr[i]==n-1){
		//incr(arr,t,0);
	//}
//	else 
	if(arr[i]==n){
		--t[n-1];
		arr[i]=1;
		t[0]++;
		incr(arr,t,++i);
	}
	else{
		--t[arr[i]-1];
		arr[i]++;
		++t[arr[i]-1];	
	}
}
int abc(int* t){
	
	for(int i=0;i<n-1;i++){
		if(t[i]==0 && t[i+1]>0){return 0;}
	}
	return 1;
}
void check(int* arr){
	flag=1;
	for(int i=0;i<n;i++){
		if(arr[i]!=i+1){
			flag=0;
			break;
		}
	}
}
void main(){
	int no=0,f1=1;
	
	
	printf("Enter the number of horses:\n");
	scanf("%d",&n);
	
	
	int* arr=(int*)calloc(n,sizeof(int));
	int* t=(int*)calloc(n,sizeof(int));

	printf("The different combinations are:\n");
	for(int i=0;i<n;i++){
		arr[i]=1;
		t[i]=0;
	}
	t[0]=n;
	//printall(arr,t);
	while(flag==0){
		
			
		if(f1==1){
			printall(arr);
			no++;
		}
		incr(arr,t,0);
		f1=abc(t);
		//printf("%d\n",f1);
		check(arr);
	}
	printall(arr);
			no++;
	printf("The total combinations are : %d\n",no);
}
