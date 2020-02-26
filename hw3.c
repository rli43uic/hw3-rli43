#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void sigintHandler(int sig) {
	char msg[] = "\ncaught sigint\n";
	write(1, msg, sizeof(msg));
}

void sigtstpHandler( int sig) {
	char msg[]= "\ncaught sigtstp\n";
	write(1,msg, sizeof(msg));

}

execute() {
	char line[500];
	while (TRUE) {
		printf("CS351 >"); 
		fgets(line, 500, stdin); //take in input from line
		
		char* word;
		//char ** argv = malloc(1000 * sizeof(char*)); 
		char* argsList[20];
		int i = 0;
   		for(i=0; i < 20; ++i)
			argsList[i] = (char*)malloc(100*sizeof(char));
		i = 0;
		word = strtok(line, " "); // parse line into word
		while (word) {
			argsList[i] = word;
			++i;
			word = strtok(NULL, " ");//iterate
		}
		argsList[i] = NULL;

		
	}
}

int main(int argc, char* argv[])
{
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
	return 0;
}

