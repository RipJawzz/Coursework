#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int operator(char ch){
	if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^')return 1;
	else return 0;
	return 0;
}
int operand(char c){
	if((c>='0'&&c<='9')||(c>='a' && c<='z'))return 1;
	else return 0;
	return 0;
}
int bracket_open(char c){
	if(c=='{'||c=='('||c=='[')return 1;
	else return 0;
	return 0;
}
int bracket_close(char c){
	if(c==')'||c=='}'||c==']')return 1;
	else return 0;
	return 0;
}
int pre(char ch){
	if(ch=='^')return 1;
	else if(ch=='*')return 2;
	else if(ch=='/')return 3;
	else if(ch=='+')return 4;
	else if(ch=='-')return 5;
	else if(ch=='{'||ch=='('||ch=='[')return 6;
	return 0;
}
void inftopost(){
	int len,ind0=0,ind1=-1,ind2=-1;
	printf("Enter the size of the expression:\n");
	scanf("%d",&len);
	char cur;
	
	char infix[len];
	char* postfix=(char *)malloc(len*sizeof(char));
	char* stack=(char*)malloc(len*sizeof(char));
	printf("Enter the expression\n");
	scanf("%s",&infix);
	
	//char* bracket=(char*)malloc((len\2)*sizeof(char));
	
	while(ind0!=len){
		cur=infix[ind0];
		if(operand(cur)==1){
			ind1++;
			postfix[ind1]=cur;
		}
		else if(operator(cur)==1){
			if(ind2!=-1){
				while(pre(cur)>pre(stack[ind2]) && ind2!=-1){
					ind1++;
					postfix[ind1]=stack[ind2];
					ind2--;
				}
				ind2++;
				stack[ind2]=cur;	
			}
			else{
				ind2++;
				stack[ind2]=cur;
				
			}
		}
		else if(bracket_open(cur)==1){
			ind2++;
			stack[ind2]=cur;
		
		}
		else if(bracket_close(cur)==1){
			while(bracket_open(stack[ind2])!=1){
				ind1++;
				postfix[ind1]=stack[ind2];
				ind2--;
			}
			ind2--;
		}
		
		ind0++;
	}
	while(ind2!=-1){
		ind1++;
		postfix[ind1]=stack[ind2];
		ind2--;
	}
	for(int i=0;i<len;i++){
		printf("%c",postfix[i]);
	}
	printf("\n");
}
void main(){
	inftopost();
	
}
