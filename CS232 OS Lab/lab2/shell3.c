#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h> 
#include <ctype.h>
#include <dirent.h> 

void executeCommand(char *command);

int MAX_ARGUMENT_LENGTH = 1000;

void handler(int signum)
{
	if(signum==SIGINT)
	{
		// take no actions
	}
}

char* trim(char input[])
{
	int n = strlen(input);
	int leftPointer=-1,rightPointer=-1;
	for(int x=0;x<n;x++)
	{
		if(!isspace(input[x]))
		{
			leftPointer = x;
			break;
		}
	}
	for(int x=n-1;x>=0;x--)
	{
		if(!isspace(input[x]))
		{			
			rightPointer = x;
			break;
		}
	}
	int new_n = rightPointer - leftPointer + 1;
	char *modifiedInput;
	modifiedInput = (char*)malloc(sizeof(char)*new_n);
	int index = 0;
	for(int x=leftPointer;x<=rightPointer;x++,index++)
	{
		modifiedInput[index] = input[x];
	}
	modifiedInput[index] = '\0';	
	return modifiedInput;
}

char* getCommandName(char *command)
{
	int pointer = -1;
	int n = strlen(command);
	for(int x = 0;x<n;x++)
	{
		if(isspace(command[x]))
		{
			pointer=x;
			break;
		}
	}
	if(pointer==-1)
	{
		return command;
	}
	char *commandName;
	commandName = (char*)malloc(sizeof(char)*(pointer));
	int index = 0;
	for(int x=0;x<pointer;x++,index++)
	{
		commandName[index] = command[x];
	}
	commandName[index] = '\0';
	return commandName;
}

int hasPipeCommand(char *command)
{
	int n = strlen(command);
	for(int x=0;x<n;x++)
	{
		if(command[x]=='|')
			return 1;
	}
	return 0;
}

int getTypePipeCommand(char *command)
{
	int count = 0;
	int n = strlen(command);
	for(int x=0;x<n;x++)
	{
		if(command[x]=='|')
		{
			count++;
		}
	}
	if(count==1 || count==2)
	{
		return count;
	}
	else
	{
		return -1;
	}
}

void pipeHandler(char *command)
{
	int typePipeCommand = getTypePipeCommand(command);
	int n = strlen(command);
	if(typePipeCommand==-1)
	{
		fprintf(stdout, "At max only 3 pipes supported\n");
		return;
	}
	if(typePipeCommand==1)
	{
		char *command1;
		char *command2;
		command1 = (char*)malloc(sizeof(char)*MAX_ARGUMENT_LENGTH);
		command2 = (char*)malloc(sizeof(char)*MAX_ARGUMENT_LENGTH);
		int index_pipe = -1;
		for(int x=0;x<n;x++)
		{
			if(command[x]=='|')
			{
				index_pipe = x;
				break;
			}
		}
		for(int x=0;x<index_pipe;x++)
		{
			command1[x] = command[x];
		}
		command1[index_pipe] = '\0';
		int index=0;
		for(int x=index_pipe+1;x<n;x++,index++)
		{
			command2[index] = command[x];
		}
		command2[index] = '\0';
		command1 = trim(command1);
		command2 = trim(command2);
		pid_t p;
		int stdin_copy = dup(STDIN_FILENO);
		int stderr_copy = dup(STDERR_FILENO);
		int fd[2];
			if(pipe(fd)<0)
			{
				fprintf(stdout, "Program execution failed\n");
				return;
			}
		if((p=fork())<0)
		{
			fprintf(stdout, "Program execution failed\n");
			return;
		}
		else if(p>0)
		{
			// parent continues here	
			pid_t p2;
			if((p2=fork())<0)
			{
				fprintf(stdout, "Program execution failed\n");
				return;
			}
			if(p2>0)
			{
				// parent continues here
				close(fd[0]);
				close(fd[1]);
				wait(NULL);
				wait(NULL);
				return;
			}
			else
			{
				// 2nd child
				close(2);
				dup(fd[1]);
				executeCommand(command1);
				exit(0);

			}
		}
		else
		{
			// child here

			close(fd[1]);
			close(0);
			dup(fd[0]);
		

			executeCommand(command2);
			
		
			exit(0);

		}

	}
	else if(typePipeCommand==2)
	{
		char *command1;
		char *command2;
		char *command3;
		command1 = (char*)malloc(sizeof(char)*MAX_ARGUMENT_LENGTH);
		command2 = (char*)malloc(sizeof(char)*MAX_ARGUMENT_LENGTH);
		command3 = (char*)malloc(sizeof(char)*MAX_ARGUMENT_LENGTH);
		int indexFirstOr=-1,indexSecondOr=-1;
		for(int x=0;x<n;x++)
		{
			if(command[x]=='|')
			{
				indexFirstOr = x;
				break;
			}
		}
		for(int x=n-1;x>=0;x--)
		{
			if(command[x]=='|')
			{
				indexSecondOr = x;
				break;
			}
		}
		for(int x=0;x<indexFirstOr;x++)
		{
			command1[x] = command[x];
		}
		int command2_index=0;
		for(int x=indexFirstOr+1;x<indexSecondOr;x++)
		{
			command2[command2_index] = command[x];
			command2_index++;
		}
		int command3_index = 0;
		for(int x=indexSecondOr+1;x<n;x++)
		{
			command3[command3_index] = command[x];
			command3_index++;
		}
		command1 = trim(command1);
		command2 = trim(command2);
		command3 = trim(command3);


		//  Create the two pipes
    	int pi[2];
    	pipe(pi);
    	int pi2[2];

    	//  First child
    	if ( fork() == 0 )
    	{
        	//  Set up the first pipe to be written to
        	//  and close the unneeded pipe endpoints
        	//fprintf(stdout, "Child 1 starts\n");
        	close(pi[0]);
        	dup2(pi[1], 2);
        	close(pi[1]);
        	//execlp( "ls", "ls", "-al", NULL );
        	executeCommand(command1);
        	//fprintf(stdout, "Child 1 finishes\n");
        	exit(0);
    	}

	    //  Don't open the second pipe until it's needed
	    //  so extra endpoints don't need to be closed
	    pipe(pi2);

    	//  Second child
    	if ( fork() == 0 )
    	{
        	//  Set up first pipe to be read from
        	//  and close the unneeded pipe endpoints
        //	fprintf(stdout, "Child 2 starts\n");
        	close(pi[1]);
        	dup2(pi[0], 0);
        	close(pi[0]);
        	//  Set up second pipe to be written to
        	//  and close the unneeded pipe endpoints
        	close(pi2[0]);
        	dup2(pi2[1], 2);
        	close(pi2[1]);
        	//execlp( "tr", "tr", "a-j", "A-J", NULL );
        	executeCommand(command2);
        //	fprintf(stdout, "Child 2 ends\n");
        	exit(0);
    	}

    	//  Close original pipe endpoints so they aren't
    	//  duplicated into the third child (where they would
    	//  need to be closed).
    	close(pi[1]);
    	close(pi[0]);

    	//  Third child
    	if ( fork() == 0 )
	    {
    	    //  Set up second pipe to be read from
	        //  and close the unneeded pipe endpoints
	      //  fprintf(stdout, "Child 3 starts\n");
    	    close(pi2[1]);
	        dup2(pi2[0], 0);
        	close(pi2[0]);
        	//execlp( "tr", "tr", "k-z", "K-Z", NULL );
        	executeCommand(command3);
        //	fprintf(stdout, "Child 3 ends\n");
        	exit(0);
    	}

    	//  Close parent's copy of second pipes
    	close(pi2[1]);
    	close(pi2[0]);

    	wait(NULL);
    	wait(NULL);
    	wait(NULL);
    	return;


	}
}


int isEqual(char *string1,char string2[])
{
	return !strcmp(string1,string2);	
}

int getCommandIndex(char *commandName)
{

	if(isEqual(commandName,"exit"))
	{
		return 1;
	}
	else if(isEqual(commandName,"cd"))
	{
		return 2;
	}
	else if(isEqual(commandName,"pwd"))
	{
		return 3;
	}
	else if(isEqual(commandName,"source"))
	{
		return 4;
	}
	else if(isEqual(commandName,"echo"))
	{
		return 5;
	}
	else if(isEqual(commandName,"cat"))
	{
		return 6;
	}
	else if(isEqual(commandName,"ls"))
	{
		return 7;
	}
	else if(strcmp(commandName,"mkdir")==0)
	{
		return 8;
	}
	else if(isEqual(commandName,"sed"))
	{
		return 10;
	}
	else if(isEqual(commandName,"tail"))
	{
		return 11;
	}
	else if(isEqual(commandName,"sleep"))
	{
		return 12;
	}
	else if(isEqual(commandName,"cp"))
	{
		return 13;
	}
	else if(strlen(commandName)==0)
	{
		return 14;
	}
	else if(isEqual(commandName,"chmod"))
	{
		return 15;
	}
	else if(isEqual(commandName,"^C"))
	{
		return 16;
	}
	else
	{
		return 9;
	}

}

void exitHandler(char *command)
{
	fprintf(stdout, "%s\n","\nShell terminated\n");
	exit(0);
}

char* getAllArguments(char *command)
{
	int pointerFirstSpace = -1;
	int n = strlen(command);
	for(int x=0;x<n;x++)
	{
		if(isspace(command[x]))
		{
			pointerFirstSpace = x;
			break;
		}
	}
	if(pointerFirstSpace==-1)
	{
		return "";
	}
	char *allArguments;
	allArguments = (char*)malloc(sizeof(char)*(n-pointerFirstSpace+1));
	int index = 0;
	for(int x=pointerFirstSpace;x<n;x++,index++)
	{
		allArguments[index] = command[x];
	}	
	allArguments[index] = '\0';
	char *allArguments_trimed = trim(allArguments);		
	free(allArguments);
	return allArguments_trimed;
}

int hasDoubleQuotes(char *s)
{
	s = trim(s);
	int n = strlen(s);
	if(n==0)
	{
		return 0; // empty string
	}
	for(int x=1;x<=n-2;x++)
	{				
		if(s[x]=='\"')
		{			
			return -1; // wrong number of double quotes or at wrong place
		}
	}
	if(s[0]=='\"' && s[n-1]=='\"')
	{
		return 1;
	}	
	return 0;
}

void cdHandler(char *command)
{
	char *allArguments = getAllArguments(command);	
	int n = strlen(allArguments);
	if(n==0 || isEqual(allArguments,"~"))
	{
		chdir(getenv("HOME"));
		return;
	}
	int temp = hasDoubleQuotes(allArguments);	
	if(temp==1)
	{
		char *directoryName;
		directoryName = (char*)malloc(sizeof(char)*(n-2));
		int index=0;
		for(int x=1;x<n-1;x++,index++)
		{
			directoryName[index] = allArguments[x];
		}
		
		directoryName[index] = '\0';
		int directoryChangeResult = chdir(directoryName);
		if(directoryChangeResult==-1)
		{
			fprintf(stdout,"Invalid cd command syntax\n");
			fprintf(stdout,"Failed to execute cd command\n");
		}
		free(directoryName);
		return;
	}	
	if(temp==-1)
	{
		fprintf(stdout,"Invalid cd command syntax\n");
		fprintf(stdout,"Failed to execute cd command\n");
		return;
	}
	if(temp==0)
	{			
		int directoryChangeResult = chdir(allArguments);
		if(directoryChangeResult==-1)
		{
			fprintf(stdout,"Invalid cd command syntax\n");
			fprintf(stdout,"Failed to execute cd command\n");
			return;
		}
	}

	free(allArguments);
}

void pwdHandler(char *command)
{
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) == NULL) 
   	{   		
     	fprintf(stdout, "%s\n","Error getting current working directory! :(" ); 
     	return;
   	}   	
   	int l =strlen(cwd);
   	cwd[l] = '\0';
   	fprintf(stderr,"%s\n",cwd);

}


void echoHandler(char *command)
{
	char *allArguments = getAllArguments(command);
	int n = strlen(allArguments);
	for(int x=0;x<n;x++)
	{
		if(allArguments[x]!='\"')
		{
			fprintf(stderr, "%c",allArguments[x]);	
		}		
	}
	free(allArguments);
	return;
}

void lsHandler()
{
	
	struct dirent *de;  // Pointer for directory entry 
  
    // opendir() returns a pointer of DIR type.  
    DIR *dr = opendir("."); 
  
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
        printf("Could not open current directory" ); 
        return; 
    } 
  
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html 
    // for readdir() 
    while ((de = readdir(dr)) != NULL) 
            fprintf(stderr,"%s\n", de->d_name); 
  
    closedir(dr);         
   // fprintf(stderr, "\\\n");
  	return;
}

void sourceHandler(char *command)
{
	char *fileName = getAllArguments(command);
	FILE* file = fopen(fileName, "r"); 
	if(!file)
	{
		printf("Unable to open : %s \n", fileName);
		return;
	}

	char *lines[5000];
	int lines_index = 0;
	char line[500];

	while (fgets(line, sizeof(line), file)) 
	{
		char *token;
		char *rest;
		rest = line;
		while((token=strtok_r(rest,";",&rest)))
		{
			if(strlen(trim(token))!=0)
			{
				lines[lines_index] = trim(token);
				lines_index++;
			}
		}
	}
	fclose(file);
	lines[lines_index] = NULL;
	pid_t t;
	for(int x=0;x<lines_index;x++)
	{
		//fprintf(stdout, "%s\n",lines[x]);
		executeCommand(lines[x]);
	}			
	

	
	return;
}


void mkdirHandler(char *command)
{
	// Creating a directory 
    if (mkdir(getAllArguments(command), 0777) == -1) 
    {
    	fprintf(stdout,"Error creating directory\n");
    	return;
    }
  	return;
}

int getTypeOfCatCommand(char *arguments)
{
	int leftArrowIndex=-1;
	int rightArrowIndex=-1;
	int counterLeftArrow=0;
	int counterRightArrow=0;
	int n = strlen(arguments);
	for(int x=0;x<n;x++)
	{
		if(arguments[x]=='>')
		{
			rightArrowIndex=x;
			counterRightArrow++;
		}
		if(arguments[x]=='<')
		{
			leftArrowIndex=x;
			counterLeftArrow++;
		}
	}
	if(counterLeftArrow==0 && counterRightArrow==0)
	{
		return 1; // only output file content to screen
	}
	if(counterRightArrow>1 || counterLeftArrow>1)
	{
		return -1; // invalid syntax
	}

	if(counterRightArrow==0 && counterLeftArrow==1)
	{
		if(leftArrowIndex==0)
		{
			return 4; // only ouptut file content to screen, contains one left arrow 
		}
	}
	if(counterLeftArrow==0 && counterRightArrow==1)
	{
		if(rightArrowIndex!=0)
		{
			return 2; // output to output.txt file, contains only right arrow	
		}
		else
		{
			return 5;
		}
		
	}
	if(counterRightArrow==1 && counterLeftArrow==1)
	{
		if(leftArrowIndex==0)
		{
			return 3; // output to output.txt, contains one left and one right arrow
		}
	}


	return -1;
}

void catHandler(char *command)
{
	char *arguments = getAllArguments(command);
	int typeCatCommand = getTypeOfCatCommand(arguments);
	
	if(typeCatCommand==1)
	{
		char *fileName = getAllArguments(command);
		FILE* file = fopen(fileName, "r"); 
		if(!file)
		{
			printf("Unable to open : %s \n", fileName);
			return;
		}

		char line[500];
		char buffer[MAX_ARGUMENT_LENGTH*10];
		int index = 0;

		while (fgets(line, sizeof(line), file)) 
		{
			//fprintf(stderr, "%s",line );
			for(int x=0;x<strlen(line);x++)
			{
				buffer[index] = line[x];
				index++;
			}
		}
	
		buffer[index] = '\0';
		write(2,buffer,index);
		free(fileName);
		free(arguments);
	}
	else if(typeCatCommand==4)
	{
		int n = strlen(arguments);
		char *fileName;
		fileName = (char*)malloc(sizeof(char)*(n-1));
		for(int x=1;x<n;x++)
		{
			fileName[x-1] = arguments[x];
		}
		fileName[n-1] = '\0';
		fileName = trim(fileName);
		FILE* file = fopen(fileName, "r"); 
		if(!file)
		{
			printf("Unable to open : %s \n", fileName);
			return;
		}

		char line[500];

		while (fgets(line, sizeof(line), file)) 
		{
			fprintf(stderr, "%s",line );
		}
	
		free(fileName);
	}
	else if(typeCatCommand==2)
	{
		int rightArrowIndex=-1;
		int n = strlen(arguments);
		for(int x=0;x<n;x++)
		{
			if(arguments[x]=='>')
			{
				rightArrowIndex=x;
				break;
			}
		}
		int inputFileName_length = rightArrowIndex;
		char *inputFileName;
		inputFileName = (char*)malloc(sizeof(char)*inputFileName_length);
		int outputFileName_length = n-rightArrowIndex;
		char *outputFileName;
		outputFileName = (char*)malloc(sizeof(char)*outputFileName_length);
		for(int x=0;x<rightArrowIndex;x++)
		{
			inputFileName[x] = arguments[x];
		}
		inputFileName[inputFileName_length] = '\0';
		int index=0;
		for(int x=rightArrowIndex+1;x<n;x++,index++)
		{
			outputFileName[index] = arguments[x];
		}
		outputFileName[index] = '\0';
		inputFileName = trim(inputFileName);
		outputFileName = trim(outputFileName);
	
		FILE *output=fopen(outputFileName,"w");
		if((output)==NULL)
		{
			fprintf(stdout, "Error opening %s file\n",outputFileName);
			return;
		}
		FILE* file = fopen(inputFileName, "r"); 
		if(!file)
		{
			printf("Unable to open : %s \n", inputFileName);
			return;
		}

		char line[500];

		while (fgets(line, sizeof(line), file)) 
		{			
			fprintf(output, "%s\n",line );
		}
		fclose(file);
		fclose(output);
		free(inputFileName);
		free(outputFileName);
	}
	else if(typeCatCommand==3)
	{
		int rightArrowIndex=-1;
		int n = strlen(arguments);
		for(int x=0;x<n;x++)
		{
			if(arguments[x]=='>')
			{
				rightArrowIndex=x;
				break;
			}
		}
		int inputFileName_length = rightArrowIndex-1;
		char *inputFileName;
		inputFileName = (char*)malloc(sizeof(char)*inputFileName_length);
		int outputFileName_length = n-rightArrowIndex;
		char *outputFileName;
		outputFileName = (char*)malloc(sizeof(char)*outputFileName_length);
		for(int x=1;x<rightArrowIndex;x++)
		{
			inputFileName[x-1] = arguments[x];
		}
		inputFileName[inputFileName_length] = '\0';
		int index=0;
		for(int x=rightArrowIndex+1;x<n;x++,index++)
		{
			outputFileName[index] = arguments[x];
		}
		outputFileName[index] = '\0';
		inputFileName = trim(inputFileName);
		outputFileName = trim(outputFileName);

		FILE *output=fopen(outputFileName,"w");
		if((output)==NULL)
		{
			fprintf(stdout, "Error opening %s file\n",outputFileName);
			return;
		}
		FILE* file = fopen(inputFileName, "r"); 
		if(!file)
		{
			printf("Unable to open : %s \n", inputFileName);
			return;
		}

		char line[500];

		while (fgets(line, sizeof(line), file)) 
		{			
			fprintf(output, "%s",line );
		}
		fclose(file);
		fclose(output);

		free(inputFileName);
		free(outputFileName);
	}
	else if(typeCatCommand==5)
	{

		char *outputFileName;
		outputFileName = (char*)malloc(sizeof(char*)*MAX_ARGUMENT_LENGTH);
		int index=0;
		int n = strlen(command);
		for(int x=1;x<strlen(arguments);x++)
		{
			outputFileName[index] = arguments[x];
			index++;
		}
		outputFileName[index] = '\0';
		outputFileName = trim(outputFileName);

		FILE *output=fopen(outputFileName,"w");
		if((output)==NULL)
		{
			fprintf(stdout, "Error opening %s file\n",outputFileName);
			return;
		}
		char input[MAX_ARGUMENT_LENGTH]	;	
		int i;
		index=0;
		while((i=getchar())!=EOF)
		{
			input[index] = i;

			index++;
		}
		input[index] = '\0';			
		if(write(fileno(output),input,strlen(input))==-1)
		{
			fprintf(stdout, "Erorr writting output\n");
			return;
		}
		close(fileno(output));
		fflush(stdin);
		free(outputFileName);
	}
	return;
}


void programHandler(char *command)
{
	char *arguments = getAllArguments(command);
	char *programName = getCommandName(command);
	int runInBackground = 0;
	int n = strlen(arguments);	
	if(arguments[n-1]=='&')
	{
		runInBackground=1;		
	}
	char *args[1000];
	int index=0;
	if(runInBackground)
	{
		arguments[n-1] = '\0';
		arguments = trim(arguments);
	}
	char *rest = arguments;
	char *token;
	args[index] = programName;
	index++;
	while((token=strtok_r(rest," ",&rest)))
	{
		if(strlen(trim(token))!=0)
		{
			args[index] = trim(token);
			index++;	
		}
	}
	args[index] = NULL;		
	int status;
	pid_t p;
	if((p=fork())<0)
	{
		fprintf(stdout,"Cannot run the program\n");
		return;
	}
	else if(p>0)
	{
		// parent here		
		if(!runInBackground)
		{
			waitpid(p,&status,0);

		}
		else
		{
			return;
		}

	}
	else
	{
		// child
		if(execvp(args[0],args)==-1)
		{
			fprintf(stdout, "%s\n","Failed to run the program");
		}

	}
}

int getSedCommandType(char *arguments)
{
	if(isEqual(trim(arguments),"p"))
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

void sedHandler(char *command)
{
	char *arguments = getAllArguments(command);
	int sedCommandType = getSedCommandType(arguments);
	if(sedCommandType==0)
	{
		char fileContent[MAX_ARGUMENT_LENGTH];
		int index=0;
		int c;
		while((c=getchar())!=EOF )
		{
			fileContent[index] = c;
			index++;
		}
		fileContent[index] = '\0';
		char line[MAX_ARGUMENT_LENGTH];

		int new_index=0;


		char *rest = fileContent;
		char *token;
		char *lines[MAX_ARGUMENT_LENGTH];
		int lines_index=0;
		while((token=strtok_r(rest,"\n",&rest)))
		{
			if(strlen(trim(token))!=0)
			{
				lines[lines_index] = trim(token);
				lines_index++;
			}
		}
		lines[lines_index] = NULL;

		for(int x=0;x<lines_index;x++)
		{
			fprintf(stderr, "%s\n",lines[x]);
			fprintf(stderr, "%s\n",lines[x]);
		}

		free(arguments);

	}
	else
	{
		fprintf(stdout, "Given command not supported\n");
		return;
	}

}


int getTailCommandType(char *arguments)
{
	int flag=0;
	int n = strlen(arguments);
	int takeInputFromKeyboard = 0;
	for(int x=0;x<n;x++)
	{
		if(arguments[x]=='-')
		{
			flag=1;
		}
		if(arguments[x]=='n')
		{
			if(flag==1)
			{
				takeInputFromKeyboard=1;
				break;
			}
		}
		if(arguments[x]!='-')
		{
			flag=0;
		}
	}
	if(takeInputFromKeyboard==1)
	{
		return 0;
	}
	return -1;
}

void tailHandler(char *command)
{
	char *arguments = getAllArguments(command);
	int tailCommandType = getTailCommandType(arguments);
	if(tailCommandType==-1)
	{
		fprintf(stdout, "Invalid Command\n");
		return;
	}
	if(tailCommandType==0)
	{
		int index=0;
		for(int x=0;x<strlen(arguments);x++)
		{
			if(arguments[x]==' ')
			{
				index=x;
				break;
			}
		}
		char *number;
		number = (char*)malloc(sizeof(char)*MAX_ARGUMENT_LENGTH);
		int new_index=0;
		for(int x=index;x<strlen(arguments);x++)
		{
			number[new_index] = arguments[x];
			new_index++;
		}
		number[new_index] = '\0';
		number = trim(number);
		int n = atoi(number);
		if(n==0)
		{
			fprintf(stdout, "Invalid command\n");
			return;
		}
		char inputContent[MAX_ARGUMENT_LENGTH];
		int i=0;
		int c;
		while((c=getchar())!=EOF)
		{
			inputContent[i] = c;
			i++;
			if(c!='\n')
			{
		
			}
			else
			{
		
			}
			
		}
		inputContent[i] = '\0';

		char *lines[MAX_ARGUMENT_LENGTH];
		int lines_index=0;
		char *rest = inputContent;
		char *token;
		while((token=strtok_r(rest,"\n",&rest)))
		{
			if(strlen(trim(token))!=0)
			{
				lines[lines_index] = trim(token);
				lines_index++;
			}
		}
		lines[lines_index] = NULL;

		for(int x=lines_index-n;x<lines_index;x++)
		{			
			fprintf(stderr, "%s\n",lines[x]);		
		}

	}
}

void sleepHandler(char *command)
{
	char *argument = getAllArguments(command);
	int sleepDuration = atoi(argument);
	if(sleepDuration==0)
	{
		fprintf(stdout, "Invalid sleep duration given\n");
	}
	pid_t p;
	p = fork();
	if(p>0)
	{
		wait(NULL);
	}
	else
	{
		sleep(sleepDuration);
	}
	
}


void cpHandler(char *command)
{
	printf("cpHandler\n");
	char *arguments = getAllArguments(command);
	int indexFirstSpace = -1;
	int n = strlen(arguments);
	for(int x=0;x<n;x++)
	{
		if(isspace(arguments[x]))
		{
			indexFirstSpace = x;
			break;
		}
	}
	if(indexFirstSpace==-1)
	{
		fprintf(stdout, "Wrong syntax\n");
		return;
	}	
	char *filename1;
	char *filename2;	
	filename1 = (char*)calloc(50,sizeof(char));	
	filename2 = (char*)malloc(sizeof(char)*50);	
	int filename1_index=0;
	for(int x=0;x<indexFirstSpace;x++,filename1_index++)
	{
		filename1[x] = arguments[x];
	}
	filename1[filename1_index] = '\0';
	int filename2_index=0;
	for(int x=indexFirstSpace+1;x<n;x++)
	{
		filename2[filename2_index] = arguments[x];
		filename2_index++;
	}
	filename2[filename2_index] = '\0';
	filename1 = trim(filename1);
	filename2 = trim(filename2);	

	printf("%s %ld %s %ld\n",filename1,strlen(filename1),filename2,strlen(filename2));

	char *cdCommand;
	cdCommand = (char*)malloc(sizeof(char)*MAX_ARGUMENT_LENGTH);
	int indexSlash = -1;
	for(int x=0;x<strlen(filename1);x++)
	{
		if(filename1[x]=='/')
		{
			indexSlash = x;
			break;			
		}
	}

	char *fileContent;


	if(indexSlash!=-1)
	{
		int index_cdCommand = 0;
		for(int x=0;x<indexSlash;x++)
		{
			cdCommand[index_cdCommand] = filename1[x];
			index_cdCommand++;
		}
		cdCommand[index_cdCommand] = '\0';		
		char *passCdCommand;
		passCdCommand = (char*)malloc(sizeof(char)*MAX_ARGUMENT_LENGTH);
		passCdCommand[0] = 'c';
		passCdCommand[1] = 'd';
		passCdCommand[2] = ' ';
		passCdCommand[3] = '\0';
		strcat(passCdCommand,cdCommand);		
		char cwd[MAX_ARGUMENT_LENGTH];
		getcwd(cwd, sizeof(cwd));	
		cdHandler(passCdCommand);		
		filename1_index = 0;
		char *newFilename1;
		newFilename1 = (char*)malloc(sizeof(char)*MAX_ARGUMENT_LENGTH);
		for(int x=indexSlash+1;x<strlen(filename1);x++)
		{
			newFilename1[filename1_index] = filename1[x];
			filename1_index++;
		}
		newFilename1[filename1_index] = '\0';

		newFilename1 = trim(newFilename1);		

		filename1 = newFilename1;

		fprintf(stderr, "%s %ld\n",filename1,strlen(filename1));

		int file1 = open(filename1, O_RDONLY);
		if(file1<0)
		{
			fprintf(stdout, "Error opening file %s\n",filename1);
			return;
		}
		
		fileContent = (char*)malloc(sizeof(char)*MAX_ARGUMENT_LENGTH*100);

		int sz = read(file1,fileContent,MAX_ARGUMENT_LENGTH*100);
		if(sz<0)
		{
			fprintf(stdout, "Error reading the file\n");
			return;
		}
		fileContent[sz] = '\0';
		close(file1);			
		passCdCommand[0] = 'c';
		passCdCommand[1] = 'd';
		passCdCommand[2] = ' ';
		passCdCommand[3] = '\0';
		strcat(passCdCommand,cwd);

		cdHandler(passCdCommand);


	}
	else
	{
		int file1 = open(filename1, O_RDONLY);
		if(file1<0)
		{
			fprintf(stdout, "Error opening file %s\n",filename1);
			return;
		}
		
		fileContent = (char*)malloc(sizeof(char)*MAX_ARGUMENT_LENGTH*100);
		int sz = read(file1,fileContent,MAX_ARGUMENT_LENGTH*100);
		if(sz<0)
		{
			fprintf(stdout, "Error reading the file\n");
			return;
		}
		fileContent[sz] = '\0';
		close(file1);	
	}
	
	FILE *file2 = fopen(filename2,"w");
	if(file2==NULL)
	{
		fprintf(stdout, "Error with 2nd file %s\n",filename2);
		return;
	}	
	fprintf(file2, "%s",fileContent);	
	fclose(file2);
	
}

void chmodHandler(char *command)
{
	char *arguments = getAllArguments(command);
	char *filename;
	char *permissionType;
	filename = (char*)malloc(sizeof(char)*MAX_ARGUMENT_LENGTH);
	permissionType = (char*)malloc(sizeof(char)*MAX_ARGUMENT_LENGTH);
	int index_filename = 0;
	int index_permissionType = 0;
	int indexFirstSpace = -1;
	int n = strlen(arguments);
	for(int x=0;x<n;x++)
	{
		if(isspace(arguments[x]))
		{
			indexFirstSpace = x;
			break;			
		}
	}
	if(indexFirstSpace==-1)
	{
		fprintf(stdout, "Wrong syntax\n");
		return;
	}
	for(int x=0;x<indexFirstSpace;x++)
	{
		permissionType[index_permissionType] = arguments[x];
		index_permissionType++;
	}
	for(int x=indexFirstSpace+1;x<n;x++)
	{
		filename[index_filename] = arguments[x];
		index_filename++;
	}
	permissionType[index_permissionType] = '\0';
	filename[index_filename] = '\0';
	permissionType = trim(permissionType);
	filename = trim(filename);
	int pT = strtol(permissionType, 0, 8);
	if(pT<0)
	{
		fprintf(stdout, "Command failed\n");
		return;
	}
	if(chmod(filename,pT)<0)
	{
		fprintf(stdout, "Command failed\n");
		return;
	}
}


void executeCommand(char *command)
{
	if(hasPipeCommand(command))
	{
		pipeHandler(command);
		return;
	}
	char *commandName = getCommandName(command);
	int commandIndex = getCommandIndex(commandName);
	if(commandIndex==1)
	{
		exitHandler(command);
		return;
	}
	else if(commandIndex==2)
	{
		cdHandler(command);
		return;
	}
	else if(commandIndex==3)
	{
		pwdHandler(command);
		return;
	}
	else if(commandIndex==4)
	{		
		sourceHandler(command);
		return;
	}
	else if(commandIndex==5)
	{
		echoHandler(command);
		return;
	}
	else if(commandIndex==6)
	{
		catHandler(command);
		return;
	}
	else if(commandIndex==7)
	{
		lsHandler();
		return;
	}
	else if(commandIndex==8)
	{
		mkdirHandler(command);
		return;
	}
	else if(commandIndex==9)
	{
		programHandler(command);
		return;
	}
	else if(commandIndex==10)
	{
		sedHandler(command);
		return;
	}	
	else if(commandIndex==11)
	{
		tailHandler(command);
		return;
	}	
	else if(commandIndex==12)
	{
		sleepHandler(command);
		return;
	}
	else if(commandIndex==13)
	{
		cpHandler(command);
		return;
	}
	else if(commandIndex==14)
	{
		return;
	}
	else if(commandIndex==15)
	{
		chmodHandler(command);
		return;
	}
	else if(commandIndex==16)
	{
		return;
	}

	return;


	
}

int main()
{
	char *input;
	input = (char*)malloc(sizeof(char)*MAX_ARGUMENT_LENGTH);
	char cwd[PATH_MAX];
	signal(SIGINT, handler);
   	if (getcwd(cwd, sizeof(cwd)) == NULL) 
   	{   		
     	fprintf(stderr, "%s\n","Error getting current directory! :(" ); 
     	exit(1);
   	}
   	while(1)
   	{
   		fprintf(stderr, "aditya@adi:~%s$ ",cwd );
   		fgets(input,MAX_ARGUMENT_LENGTH,stdin);   		
   		char *trimmed_input = trim(input);   		   		
   		char *command;
   		command = (char*)malloc(sizeof(char)*MAX_ARGUMENT_LENGTH);
   		int index=0;
   		for(int x=0;x<strlen(trimmed_input);x++)
   		{
   			if(trimmed_input[x]==';')
   			{
   				command[index]='\0';
   				executeCommand(trim(command));
   				index=0;
   			}
   			else
   			{
   				command[index] = trimmed_input[x];
   				index++;
   			}
   		}
   		command[index] = '\0';
   		executeCommand(trim(command));
   		getcwd(cwd, sizeof(cwd));

		/*
			Aditya Arun Sharma

		*/

	
   	}
}