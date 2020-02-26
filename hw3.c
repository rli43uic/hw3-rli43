#include <stdio.h>

#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#define BUFSIZE (10)
int execute_Shell() {
	char line[500];
	while (1) {
		printf("CS361 >"); 
		fgets(line, 500, stdin); //take in input from line
		line[strlen(line) - 1] = '\0'; // string termination character
		char* word;
		char** argsList = malloc(1000 * sizeof(char*));

		int i = 0;
		word = strtok(line, " "); // parse line into word
		while (word) {
			argsList[i] = word;
			++i;
			word = strtok(NULL, " ");//iterate
		}
		argsList[i] = NULL;
		
		int pid;
		int pid2;
		
		while(1){
    			if(argsList[i] == '\0'){
    				break;
    			}
    			if(!strcmp(line, "exit")){
    				exit(0);
    				return 0;
     			}
				int pipefds[2];
	pid_t pid;
	char buf[BUFSIZE];

	//create pipe
	if(pipe(pipefds) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	memset(buf,0,BUFSIZE);
	pid = fork();

	if (pid == 0) {
		//child close the write end
		close(pipefds[1]);
		//child read from the pipe read end until the pipe is empty
		while(read(pipefds[0], buf, 1)==1){
      buf[1] = '\0';
			printf("CHILD read from pipe -- %s\n", buf);
		}
		//after finishing reading, child close the read end
		close(pipefds[0]);
		printf("CHILD: EXITING!\n");
		exit(EXIT_SUCCESS);
	}else {
		printf("PARENT write in pipe\n");
		//parent close the read end
		close(pipefds[0]);
		//parent write in the pipe write end
		write(pipefds[1], "UICCS361", 8);
		//after finishing writing, parent close the write end
		close(pipefds[1]);
		//parent wait for child
		wait(NULL);
	}
		}
        return 0;
    }
}

void sigintHandler(int sig) {
	char msg[] = "\ncaught sigint\n";
	write(1, msg, sizeof(msg));
	execute_Shell();
}

void sigtstpHandler( int sig) {
	char msg[]= "\ncaught sigtstp\n";
	write(1,msg, sizeof(msg));
    execute_Shell();
}


int main()
{
    signal(SIGINT, sigintHandler);
	signal(SIGTSTP, sigtstpHandler);
	execute_Shell();
 	return 0;
}
