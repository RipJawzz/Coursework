#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAX_PROCESS 100
#define line_length 30
//Struct to store process table
typedef struct {
         char * name;
         int arrival;
         int cpuburst;
         int turnaround;
         int wait;
}Process;

//functions declared
void PrintProcessTable();
void ReadProcessTable(char*);
void PrintStatistics();
void FCFS();
void RR(int);
void SRBF();
void line(int);

//Global data
Process processtable[MAX_PROCESS];
int current_time=0,process_count=0;

//funcion to draw a line of length l
void line(int l){
  for(int i=0;i<l;i++)
    printf("-");
  printf("\n");
}

//Function to print process table taken input from file
void PrintProcessTable(){
  Process p;
  for(int i=0;i<process_count;i++){
    p=processtable[i];
    printf("%s %d %d\n",p.name,p.arrival,p.cpuburst);
  }
}

//Reads file input by user "filename" and fills all Process data into processtable
void ReadProcessTable(char * filename){
  FILE* file=fopen(filename,"r");
  char str[20];
  int a,b;
  if(file==NULL){
    printf("File doesn't exist\n");
    exit(1);
  }
  else{
    //Reading from file and saving in processtable
    fscanf(file,"%s %d %d",str,&a,&b);
    while(!feof(file)){
      Process p;
      p.name=calloc(10,sizeof(char));
      strcpy(p.name,str);
      p.arrival=a;
      p.cpuburst=b;
      processtable[process_count]=p;
      process_count++;
      fscanf(file,"%s %d %d",str,&a,&b);
    }
  }
}

//function to print statistics:[Turnaround time, Wait time, Avg turnaround time, Avg wait time]
void PrintStatistics(){
  float turnaround=0,wait=0;
  printf("Turnaround times:   ");
  for(int i=0;i<process_count;i++){
    Process p=processtable[i];
    printf("%s[%d]",p.name,p.turnaround);
    turnaround+=p.turnaround*1.0;
    if(i<process_count-1)
      printf(", ");
    else
      printf("\n");
  }

  printf("Wait times:         ");
  for(int i=0;i<process_count;i++){
    Process p=processtable[i];
    printf("%s[%d]",p.name,p.wait);
    wait+=p.wait*1.0;
    if(i<process_count-1)
      printf(", ");
    else
      printf("\n");
  }

  turnaround=turnaround/(process_count*1.0);
  wait=wait/(process_count*1.0);
  printf("\nAvg turnaround=%f\nAvg wait=%f\n",turnaround,wait);
}

//Function to start First Come First Serve scheduling
void FCFS(){
  line(line_length);
  printf("          Running FCFS\n");
  line(line_length);
  printf("\n\n");

  current_time=0;
  for(int i=0;i<process_count;i++){
    Process p=processtable[i];
    //Finding ideal time of cpu
    if(current_time<p.arrival){
      printf("[%d - %d]   Ideal\n",current_time,p.arrival);
      current_time=p.arrival;
    }

    //Updating process data regaring wait and turnaround time and outputting run duration
    p.wait=current_time-p.arrival;
    p.turnaround=p.wait+p.cpuburst;
    current_time+=p.cpuburst;
    processtable[i]=p;
    printf("[%d - %d] - %s running\n",current_time-p.cpuburst,current_time,p.name);

  }
  printf("\n\n");
  PrintStatistics();
}

//Function to start Round Robin scheduling
void RR(int timequantum){
  line(line_length);
  printf("          Running RR\n");
  line(line_length);
  printf("\n\n");

  current_time=0;
  //rem stores total remaining cpu burst of all processes
  int rem=0;
  int **exec=calloc(3,sizeof(int*));
  //exec stores remaining cpu burst in exec[0] and end time in exec[1]
  exec[0]=calloc(process_count,sizeof(int));
  exec[1]=calloc(process_count,sizeof(int));
  for(int i=0;i<process_count;i++){
    exec[0][i]=processtable[i].cpuburst;
    rem+=processtable[i].cpuburst;
  }

  Process p;
  bool modified=false;

  while(rem!=0){
    //executing process acc to RR using time quantum provided
    for(int i=0;i<process_count;i++){
      p=processtable[i];
      if(p.arrival>current_time)
        break;
      //checks if process need cpu time
      if(exec[0][i]>0){
        modified=true;
        if(exec[0][i]<=timequantum){
          printf("[%d - %d] - %s running\n",current_time,current_time+exec[0][i],p.name);
          current_time+=exec[0][i];
          rem-=exec[0][i];
          exec[0][i]=0;
          exec[1][i]=current_time;
        }else{
          printf("[%d - %d] - %s running\n",current_time,current_time+timequantum,p.name);
          current_time+=timequantum;
          rem-=timequantum;
          exec[0][i]-=timequantum;
        }
      }
    }

    //Finding ideal duration of cpu
    if(!modified && rem!=0){
      for(int i=0;i<process_count;i++){
        if(exec[0][i]>0){
          printf("[%d - %d] - ideal\n",current_time,processtable[i].arrival);
          current_time=processtable[i].arrival;
          break;
        }
      }
    }
    modified=false;
  }

  //Updating process data regaring turnaround and wait time
  for(int i=0;i<process_count;i++){
    Process p=processtable[i];
    p.turnaround=exec[1][i]-p.arrival;
    p.wait=p.turnaround-p.cpuburst;
    processtable[i]=p;
  }

  printf("\n\n");
  PrintStatistics();
}

//Function to start Shortest Job First scheduling
void SRBF(){
  line(line_length);
  printf("          Running SRBF\n");
  line(line_length);
  printf("\n\n");
  current_time=0;

  //rem stores cpu burst time remaining of all processes
  int rem=0;
  int **exec=calloc(3,sizeof(int*));
  //exec stores remaining cpu burst in exec[0] and end time in exec[1]
  exec[0]=calloc(process_count,sizeof(int));
  exec[1]=calloc(process_count,sizeof(int));
  for(int i=0;i<process_count;i++){
    exec[0][i]=processtable[i].cpuburst;
    rem+=processtable[i].cpuburst;
  }

  //used to keep track of wheter a process is still the shortes job even after a new process is scheduled
  int prev_index=-1,prev_start=0,prev_end=0;

  Process p;
  bool run;
  int running_index,rem_time;
  //runs while cpu time is required by some process
  while(rem>0){
    //resets checking parameters
    running_index=-1;
    run=false;
    rem_time=-1;
    for(int i=0;i<process_count;i++){
      p=processtable[i];
      //Finds time remaining before next process is scheduled
      if(p.arrival>current_time){
        rem_time=p.arrival-current_time;
        break;
      }
      //Finds Process with shortest remaing job at end of upper for loop
      if((running_index==-1 || exec[0][running_index]>exec[0][i])&&(exec[0][i]>0)){
        run=true;
        running_index=i;
      }
    }

    //Runs eligible process for time remaining before next process is scheduled
    if(run){
      if(rem_time<exec[0][running_index] && rem_time!=-1){
        if(prev_index==running_index){
          prev_end=current_time+rem_time;
        }
        else{
          //printf("[%d - %d] - %s\n",current_time,current_time+rem_time,processtable[running_index].name);
          if(prev_index!=-1)
          printf("[%d - %d] - %s\n",prev_start,prev_end,processtable[prev_index].name);
          prev_index=running_index;
          prev_start=current_time;
          prev_end=current_time+rem_time;
        }

        //updates
        current_time+=rem_time;
        exec[0][running_index]-=rem_time;
        rem-=rem_time;
      }else if(rem_time>=exec[0][running_index] || rem_time==-1){
        if(prev_index==running_index){
          prev_end=current_time+exec[0][running_index];
        }
        else{
          //printf("[%d - %d] - %s\n",current_time,current_time+exec[0][running_index],processtable[running_index].name);
          if(prev_index!=-1)
          printf("[%d - %d] - %s\n",prev_start,prev_end,processtable[prev_index].name);
          prev_index=running_index;
          prev_start=current_time;
          prev_end=current_time+exec[0][running_index];
        }

        //updates
        current_time+=exec[0][running_index];
        exec[1][running_index]=current_time;
        rem-=exec[0][running_index];
        exec[0][running_index]=0;
      }
    }

    //Finds ideal time of cpu
    if(!run && rem){
      if(prev_index!=-1)
        printf("[%d - %d] - %s\n",prev_start,prev_end,processtable[prev_index].name);
      prev_index=-1;//indicates cpu had been ideal
      for(int i=0;i<process_count;i++){
        if(exec[0][i]>0){
          printf("[%d - %d] - ideal\n",current_time,processtable[i].arrival);
          current_time=processtable[i].arrival;
          break;
        }
      }
    }
  }
  printf("[%d - %d] - %s\n",prev_start,prev_end,processtable[prev_index].name);
  //updates process parameters turnaround and wait time
  for(int i=0;i<process_count;i++){
    Process p=processtable[i];
    p.turnaround=exec[1][i]-p.arrival;
    p.wait=p.turnaround-p.cpuburst;
    processtable[i]=p;
  }

  printf("\n\n");
  PrintStatistics();
}

int main(int argc, char** argv){
  if(argc!=2)
    printf("ERR: Enter a single filename\n");
  else{

    int choice=-1;
    ReadProcessTable(argv[1]);
    line(line_length);
    printf("CPU simulator 2021\n");
    line(line_length);
    printf("\n\n\n\n");
    //starting scheduling choice and inputs
    while(choice!=0){

      line(line_length);
      printf("Enter your choice for scheduling algorithm:\n10 for help\n");
      scanf("%d",&choice);
      switch(choice){
        //help
        case 10:
          printf("1: First Come First Serve [FCFS]\n2: Round Robin [RR]\n");
          printf("3: Shortest Remaining Burst First [SRBF]\n11: Print Process Table\n");
          printf("0: Exit\n");
        break;
        //First come first serve
        case 1:
          FCFS();
        break;
        //Roud robin and input of time quantum
        case 2:
          printf("Enter the time time quantum:");
          int tq=1;
          scanf("%d",&tq);
          RR(tq);
        break;
        //Shortest Remaining Burst First
        case 3:
          SRBF();
        break;
        //Printing the process tabel taken input form file
        case 11:
          PrintProcessTable();
        break;
        //exit
        case 0:
          printf("Farewell\n");
        break;
        default:
          printf("It isnt that hard to enter a correct choice\n");
      }
      printf("Press enter\n");
      fflush(stdin);
      while(getchar()=="\n");
      char c=getchar();

    }
  }
  return 0;
}
