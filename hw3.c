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
	execute();
}

void sigtstpHandler( int sig) {
	char msg[]= "\ncaught sigtstp\n";
	write(1,msg, sizeof(msg));
    execute();
}

execute(){
	char line[500];
	while(1){
 		printf("CS361 > ");
//--------------------------------------Line Parsing
		fgets(line, 500, stdin);
		line[strlen(line) - 1] = '\0';
		int i = 0;
		char** argsarray = malloc(1000 * sizeof(char*));
		char* word;

		word = strtok(line, " ");
		while(word) {
			argsarray[i] = word;
			i++;
			word = strtok(NULL, " ");
		}
		argsarray[i] = NULL;
//--------------------------------------Arg Check
	char *IO;
	char *IO_2[100];
	char *IO_Multi[100];
	int flag = 0;
	int temp = 0;
	int pid = 0;
	int pid_2 = 0;
	int status = 0;
	int status_2 = 0;
	char *fd = '\0';
	i = 0;
	
	while(1){
		if(argsarray[i] == '\0'){
			break;
		}
		if(!strcmp(argsarray[0], "exit")){
			exit(0);
			return 0;
 		}
		if(!strcmp(argsarray[i], ";")){
			flag = 1;
			IO_Multi[0] = argsarray[i + 1];
			if(argsarray[i+2] != '\0'){
				if((!strcmp(argsarray[i+2], ">")) || (!strcmp(argsarray[i+2], "<"))){
					IO_2[0] = argsarray[i+2];
					IO_2[1] = argsarray[i+3];
				}
				else{
					IO_Multi[0] = argsarray[i+1];
					IO_Multi[1] = argsarray[i+2];
				}
			}
			break;
		}
		if(!strcmp(argsarray[i], "<")){
			IO = argsarray[i];
			fd = argsarray[i + 1];
			if(argsarray[i + 2] != '\0'){
				if(!strcmp(argsarray[i + 2], ";")){
					flag = 1;
					IO_Multi[0] = argsarray[i + 3];
					if(argsarray[i+4] != '\0'){
						IO_2[0] = argsarray[i + 4];
						IO_2[1] = argsarray[i + 5];
					}
				}
			}
			break;
		}
		if(!strcmp(argsarray[i], ">")){
			IO = argsarray[i];
			fd = argsarray[i + 1];
			if(argsarray[i + 2] != '\0'){
				if(!strcmp(argsarray[i + 2], ";")){
					flag = 1;
					IO_Multi[0] = argsarray[i + 3];
					if(argsarray[i+4] != '\0'){
						IO_2[0] = argsarray[i + 4];
						IO_2[1] = argsarray[i + 5];
					}
				}
			}
			break;
		}
		i++;
	}
	pid = fork();
	if(pid == 0){
		if(IO != '\0'){
			if(!strcmp(IO, "<")){
				int fd1 = open(fd, O_RDONLY);
				dup2(fd1, 0);
				close(fd1);
			}
			if(!strcmp(IO, ">")){
				int fd1 = open(fd, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IXUSR|S_IROTH);
				dup2(fd1, 1);
				close(fd1);
			}
		}
		exit(execv(IO_Multi[0], IO_Multi));
	}
	else {
		wait(&status);
		if(flag = 1){
			pid_2 = fork();
			if(pid_2 == 0){
				if(IO_2[0] != '\0'){
					if(!strcmp(IO_2[0], "<")){
						int fd1 = open(fd, O_RDONLY);
						dup2(fd1,0);
						close(fd1);
					}
					if(!strcmp(IO_2[0], ">")){
						int fd1 = open(fd, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IXUSR|S_IROTH);
						dup2(fd1, 1);
						close(fd1);
					}
				}
				exit(execv(IO_Multi[0], IO_Multi));
			}
			else{
				wait(&status_2);
			}
		}
		printf("pid:%i status:%i\n", pid, status,  WEXITSTATUS(status));
		if(pid_2 != 0){
			printf("pid:%i status:%i\n", pid_2, status_2,  WEXITSTATUS(status_2));
		}
	}
	}
}

int main(int argc, char* argv[])
{
    signal(SIGINT, sigintHandler);
	signal(SIGTSTP, sigtstpHandler);
	execute();
// 	int pipefds[2];
// 	pid_t pid;
// 	char buf[BUFSIZE];

// 	//create pipe
// 	if(pipe(pipefds) == -1){
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	memset(buf,0,BUFSIZE);
// 	pid = fork();

// 	if (pid == 0) {
// 		//child close the write end
// 		close(pipefds[1]);
// 		//child read from the pipe read end until the pipe is empty
// 		while(read(pipefds[0], buf, 1)==1){
//       buf[1] = '\0';
// 			printf("CHILD read from pipe -- %s\n", buf);
// 		}
// 		//after finishing reading, child close the read end
// 		close(pipefds[0]);
// 		printf("CHILD: EXITING!\n");
// 		exit(EXIT_SUCCESS);
// 	}else {
// 		printf("PARENT write in pipe\n");
// 		//parent close the read end
// 		close(pipefds[0]);
// 		//parent write in the pipe write end
// 		write(pipefds[1], "UICCS361", 8);
// 		//after finishing writing, parent close the write end
// 		close(pipefds[1]);
// 		//parent wait for child
// 		wait(NULL);
// 	}
 	return 0;
}
