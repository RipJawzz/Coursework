#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
  char c;
  struct node* n;
  struct node* p;
}node;
typedef struct action{
  char* content;
  int cursor;
  int len;
  struct action* n;
  struct action* p;
}action;
typedef struct redo_type{
  int cmdi;
  int x;
  int y;
  char c;
  int full;
}redo_type;

int command_decode(char*);
node* content_new_node();
void initialize_list(node*,node*);
void print_content(node* head);
void insert_content(node*,char,int);
void delete_content(node*,int);
void delete_string_list(node*);
void cut_string(node*,node*,node*,node*,int,int,int);
void paste(node*,node*,node*,node*,int,int,int);
void copy_to_clipboard(node*,node*,int,int);
char* list_to_string(node*,int);
void string_to_list(node*,char*,int);

void initialize_action(action*,action*);
void insert_action(node*,action*,int,int);
void un0re_do(action*,action*);
action* action_new_node();
void delete_action_list(action*);


void main(){
  FILE* file;
  char* file_text,file_name[10];
  int n=-1,m=-1,cmdi=0,x=0,y=0,cursor=0;
  char datc=' ';
  char* cmds=(char*)calloc(15,sizeof(char));
  node* content_head=content_new_node();
  node* content_tail=content_new_node();
  node* clipboard_head=content_new_node();
  node* clipboard_tail=content_new_node();
  initialize_list(content_head,content_tail);
  initialize_list(clipboard_head,clipboard_tail);

  action* undo_head=action_new_node();
  action* undo_tail=action_new_node();
  action* redo_tail=action_new_node();
  action* redo_head=action_new_node();
  initialize_action(undo_head,undo_tail);
  initialize_action(redo_head,redo_tail);

  redo_type* redo_buff=(redo_type*)calloc(1,sizeof(redo_type));
  redo_buff->full=0;

  while(cmdi!=1){
    printf("Enter the command(enter HELP for help)\n");
    scanf("%s",cmds);
    fflush(stdin);
    cmdi=command_decode(cmds);
    if(cmdi==4||cmdi==5||cmdi==6||cmdi==9||cmdi==10){
      redo_buff->full=1;
      redo_buff->cmdi=cmdi;
    }
    switch(cmdi){
      case 1:
        printf("Exiting the program\n");
      break;
      case 2:
        printf("Printing content(length of content=%d)\n",n);
        if(n==-1)
          printf("Empty String\n");
        else
          print_content(content_head->n);
      break;
      case 3:

        printf("Cursor position: %d\n",cursor);
      break;
      case 4:

        n++;
        printf("Inserting\nEnter the character\n");
        scanf("%c",&datc);
        insert_content(content_head,datc,cursor);
        cursor++;
        redo_buff->c=datc;
        insert_action(content_head,undo_tail,cursor,n);
      break;
      case 5:

        printf("Seeking\nEnter the position to be seeked\n");
        scanf("%d",&x);
        if(x==-1)
          cursor=n;
        else if(x<=n && x>=0)
          cursor=x;
        redo_buff->x=x;
        insert_action(content_head,undo_tail,cursor,n);
      break;
      case 6:

        printf("Deleting\nEnter offset for deletion\n");
        scanf("%d",&x);
        if(n==-1)
          printf("Empty string\n");
        else{
          if(x==-1 && cursor>=1)
            cursor--;
          delete_content(content_head,cursor-1);
          n--;
          if(n<cursor)
            cursor--;
          redo_buff->x=x;
          insert_action(content_head,undo_tail,cursor,n);
        }
      break;
      case 7:
        delete_string_list(clipboard_head);
        printf("Enter bounds for copying to clipboard\n");
        scanf("%d %d",&x,&y);
        if(n!=-1 && x<=y && x>=0 && y<=n){
          m=y-x;
          copy_to_clipboard(content_head,clipboard_head,x,m);
        }
        else
          printf("Wrong input of x & y or string is empty\n");
      break;
      case 8:
        printf("Printing clipboard\n");
        if(m==-1)
          printf("Empty clipboard\n");
        else
          print_content(clipboard_head->n);
      break;
      case 9:

        delete_string_list(clipboard_head);
        printf("Enter the bounds for cutting\n");
        scanf("%d %d",&x,&y);
        if(n!=-1 && x<=y && y>=0 && y<=n){
          m=y-x;
          cut_string(content_head,content_tail,clipboard_head,clipboard_tail,x,y,n);
          n-=m;
          redo_buff->x=x;
          redo_buff->y=y;
          insert_action(content_head,undo_tail,cursor,n);
        }
        else
          printf("Wrong input of x & y or string is empty\n");
      break;
      case 10:

        printf("Pasting clipboard\nEnter the starting position of pasting\n");
        scanf("%d",&x);
        if(x<0 || x>n)
          printf("out of bounds\n");
        else if(n==-1 || m==-1)
          printf("Content or clipboard is empty\n");
        else{
          paste(content_head,content_tail,clipboard_head,clipboard_tail,n,m,x);
          redo_buff->x=x;
          insert_action(content_head,undo_tail,cursor,n);
        }
      break;
      case 11:
        printf("Undoing last action\n");
        if(undo_head->n==undo_tail)
          printf("No previous instructions remaining to undo\n");
        else{
          un0re_do(undo_tail,redo_tail);
          delete_string_list(content_head);
          if(undo_head->n!=undo_tail){
          n=undo_tail->p->len;
          cursor=undo_tail->p->cursor;
          string_to_list(content_head,undo_tail->p->content,n);
        }else{
          n=-1;
          cursor=0;
        }
        }
      break;
      case 12:
        printf("Redoing last action\n");
        if(redo_head->n!=redo_tail){
          delete_string_list(content_head);
          n=redo_tail->p->len;
          cursor=redo_tail->p->cursor;
          string_to_list(content_head,redo_tail->p->content,n);
          un0re_do(redo_tail,undo_tail);
        }else if(redo_buff->full==1){
          switch(redo_buff->cmdi){
            case 4:
              n++;
              printf("Inserting %c\n",redo_buff->c);
              insert_content(content_head,redo_buff->c,cursor);
              cursor++;
              insert_action(content_head,undo_tail,cursor,n);
            break;
            case 5:
              x=redo_buff->x;
              printf("Seeking %d\n",x);
              if(x==-1)
                cursor=n;
              else if(x<=n && x>=0)
                cursor=x;
                insert_action(content_head,undo_tail,cursor,n);
            break;
            case 6:
              x=redo_buff->x;
              printf("Deleting %d\n",x);
              if(n==-1)
                printf("Empty string\n");
              else{
                if(x==-1 && cursor>=1)
                  cursor--;
                delete_content(content_head,cursor);
                n--;
                if(n<cursor)
                  cursor--;
                insert_action(content_head,undo_tail,cursor,n);
              }
            break;
            case 9:
              delete_string_list(clipboard_head);
              x=redo_buff->x;
              y=redo_buff->y;
              printf("Cutting from %d to %d\n",x,y);
              if(n!=-1 && x<=y && y>=0 && y<=n){
                m=y-x;
                cut_string(content_head,content_tail,clipboard_head,clipboard_tail,x,y,n);
                n-=m;
                insert_action(content_head,undo_tail,cursor,n);
              }
              else
                printf("Wrong input of x & y or string is empty\n");
            break;
            case 10:
              x=redo_buff->x;
              printf("Pasting clipboard after %d\n",x);
              if(x<0 || x>n)
                printf("out of bounds\n");
              else if(n==-1 || m==-1)
                printf("Content or clipboard is empty\n");
              else{
                paste(content_head,content_tail,clipboard_head,clipboard_tail,n,m,x);
                insert_action(content_head,undo_tail,cursor,n);
              }
            break;
            default:
              printf("You are doomed\n");
          }
        }else
        printf("No previous instructions remaining to redo\n");
      break;
      case 13:
        printf("Enter the name of savefile with extension\n");
        scanf("%s",file_name);
        fflush(stdin);
        file = fopen(file_name,"w");
        file_text=list_to_string(content_head,n);
        fprintf(file,"%s",file_text);
        fclose(file);
      break;
      case 14:
        n=-1;
        m=0;
        cursor=0;
        delete_string_list(content_head);
        delete_string_list(clipboard_head);
        delete_action_list(undo_head);
        delete_action_list(redo_head);
        printf("Enter the name of savefile with extension\n");
        scanf("%s",file_name);
        fflush(stdin);
        file = fopen(file_name,"r");
        if(file==NULL)
          printf("File doesn't exist\n");
        else{
        datc = fgetc(file);
        while (datc != EOF && datc!='\n')
        {
            insert_content(content_head,datc,cursor);
            cursor++;
            n++;
            datc = fgetc(file);
        }}
        fclose(file);
        redo_buff->full=0;
      break;
      case 911:
        printf("EXIT\nPRINT\nPRINT_CURSOR\nINSERT\nSEEK\nDELETE\n");
        printf("COPY\nPRINT_CLIPBOARD\nCUT\nPASTE\nUNDO\nREDO\nSAVE\nOPEN\n");
      break;
      case 0:
        printf("Unidentifiable Command!\n");
      break;
      default:
        printf("You are doomed\n");
    }

  }

}

void un0re_do(action* t1,action* t2){
  action* temp=t1->p;
  t1->p=t1->p->p;
  t1->p->n=t1;
  t2->p->n=temp;
  temp->p=t2->p;
  temp->n=t2;
  t2->p=temp;
}
void initialize_action(action* head,action* tail){
  head->n=tail;
  tail->p=head;
  head->p=NULL;
  tail->n=NULL;
}
void string_to_list(node* head,char* arr,int n){
  for(int i=0;i<=n;i++)
    insert_content(head,arr[i],i);
}
char* list_to_string(node* head,int n){
  int i=0;
  char* arr=(char*)calloc(n+1,sizeof(char));
  head=head->n;
  while(head->n!=NULL){
    arr[i]=head->c;
    head=head->n;
    i++;
  }
  return arr;
}
void insert_action(node* head,action* tail,int cursor,int len){
  action* new=action_new_node();
  new->n=tail;
  new->p=tail->p;
  tail->p->n=new;
  tail->p=new;
  new->content=list_to_string(head,len);
  new->cursor=cursor;
  new->len=len;
}
action* action_new_node(){
  action* node=(action*)calloc(1,sizeof(action));
  node->n=NULL;
  node->p=NULL;
  return node;
}
void delete_action_list(action* head){
  action* temp=head->n;
  if(head->n->n!=NULL){
    while(temp->n!=NULL){
      temp=temp->n;
      free(temp->p);
    }
  }
}

void paste(node* content_head,node* content_tail,node* clipboard_head,node* clipboard_tail,int n,int m,int x){
  for(int i=0;i<x;i++)
    content_head=content_head->n;
  if((x+m)>n){
    content_head->n=clipboard_head->n;
    content_tail->p=clipboard_tail->p;
    content_head->n->p=content_head;
    content_tail->p->n=content_tail;
    clipboard_head->n=clipboard_tail;
    clipboard_tail->p=clipboard_head;
    while(content_head->p!=NULL)
      content_head=content_head->p;
    copy_to_clipboard(content_head,clipboard_head,x,m);
  }
  else{
    content_head=content_head->n;
    clipboard_head=clipboard_head->n;
    for(int i=0;i<=m;i++){
      content_head->c=clipboard_head->c;
      content_head=content_head->n;
      clipboard_head=clipboard_head->n;
    }

  }
}
void cut_string(node* content_head,node* content_tail,node* clipboard_head,node* clipboard_tail,int x,int y,int n){
  for(int i=0;i<x;i++)
    content_head=content_head->n;
  for(int i=n;i>y;i--)
    content_tail=content_tail->p;
    clipboard_head->n=content_head->n;
    clipboard_tail->p=content_tail->p;
    content_head->n=content_tail;
    content_tail->p=content_head;
    clipboard_head->n->p=clipboard_head;
    clipboard_tail->p->n=clipboard_tail;
}
void copy_to_clipboard(node* content,node* clipboard,int x,int m){
  node* temp;
  for(int i=0;i<=x; i++)
    content=content->n;
  for(int i=0;i<=m;i++){
    temp=content_new_node();
    temp->c=content->c;
    content=content->n;

    temp->n=clipboard->n;
    temp->p=clipboard;
    clipboard->n=temp;
    temp->n->p=temp;
    clipboard=temp;
    }

}
void delete_content(node* head,int cursor){
  for(int i=0;i<cursor;i++)
    head=head->n;
  node* temp=head->n;
  head->n=temp->n;
  temp->n->p=head;
  free(temp);
}
void insert_content(node* head,char c,int cur){

    for(int i=0;i<cur;i++)
      head=head->n;
    node* new=content_new_node();
    new->n=head->n;
    new->p=head;
    new->c=c;
    new->n->p=new;
    head->n=new;
}
void print_content(node* head){
  while(head->n!=NULL){
      printf("%c",head->c);
      head=head->n;
  }
  printf("\n");
}
void initialize_list(node* first,node* second){
  first->c=' ';
  second->c=' ';
  first->n=second;
  second->p=first;
}
node* content_new_node(){
  node* new=(node*)calloc(1,sizeof(node));
  new->c=' ';
  new->n=NULL;
  new->p=NULL;
  return new;
}
int command_decode(char* arr){
  int cmdi=0;
  if(strcmp("EXIT",arr)==0)
    cmdi=1;
  else if(strcmp("PRINT",arr)==0)
    cmdi=2;
  else if(strcmp("PRINT_CURSOR",arr)==0)
    cmdi=3;
  else if(strcmp("INSERT",arr)==0)
    cmdi=4;
  else if(strcmp("SEEK",arr)==0)
    cmdi=5;
  else if(strcmp("DELETE",arr)==0)
    cmdi=6;
  else if(strcmp("COPY",arr)==0)
    cmdi=7;
  else if(strcmp("PRINT_CLIPBOARD",arr)==0)
    cmdi=8;
  else if(strcmp("CUT",arr)==0)
    cmdi=9;
  else if(strcmp("PASTE",arr)==0)
    cmdi=10;
  else if(strcmp("UNDO",arr)==0)
    cmdi=11;
  else if(strcmp("REDO",arr)==0)
    cmdi=12;
  else if(strcmp("SAVE",arr)==0)
    cmdi=13;
  else if(strcmp("OPEN",arr)==0)
    cmdi=14;
  else if(strcmp("HELP",arr)==0)
    cmdi=911;
  return cmdi;
}
void delete_string_list(node* head){
  node* temp=head->n;
  if(head->n->n!=NULL){
    while(temp->n!=NULL){
      temp=temp->n;
      free(temp->p);
    }
    head->n=temp;
    temp->p=head;
  }
}
