#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int operator(char ch){
	if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^')return 1;
	else return 0;
	return 0;
}
int operand(char c){
	if(c>='0'&&c<='9')return 1;
	return 0;
}
int eval(int a,int b,char c){
	int res=0;
	if(c=='+')return a+b;
	else if(c=='-')return a-b;
	else if(c=='/')return a/b;
	else if(c=='*')return a*b;
	else if(c=='^')return pow(a,b); 
	return 0;
}
void postfix_eval(){
	int len,ind0=0,ind1=-1;
	char cur;
	printf("Enter the size of the expression\n");
	scanf("%d",&len);
	char postfix[len];
	int* se=(int*)malloc(len*sizeof(int));
	printf("Enter the expression\n");
	scanf("%s",&postfix);
	while(operand(postfix[ind0])==1){
		ind1++;
		se[ind1]=(int)(postfix[ind0])-48;
		ind0++;
	}
	while(ind0!=len){
		cur=postfix[ind0];
		if(operand(cur)==1){
			ind1++;
			se[ind1]=(int)(cur)-48;
		}
		else if(operator(cur)==1){
			ind1--;
			se[ind1]=eval(se[ind1],se[ind1+1],cur);
			printf("%d ",se[ind1]);
		}
		ind0++;
	}
	printf("%d\n",se[0]);

}
void main(){
	postfix_eval();
	
}
