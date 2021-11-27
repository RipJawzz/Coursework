#include<stdio.h>
#include<stdlib.h>
struct b{
	int ukey;
	char *issn;
	char *name;
};
struct s{
	int roll;
	char *name;
};
struct Node{
	void* ptr;
	struct Node* next;
};
void main(){
	struct b b1;
	struct s s1;
	b1.ukey=100;
	b1.issn=(char*)malloc(sizeof(char)*10);
	b1.issn="nigger";
	s1.roll=69;
	s1.name=(char*)malloc(sizeof(char)*10);
	s1.name="big hoe";
	struct Node* head=(struct Node*)malloc(sizeof(struct Node*));;
	//struct Node* next=(struct Node*)malloc(sizeof(struct Node));
	 head->ptr=&b1;
	printf("%d\n",head->ptr->ukey);
}

