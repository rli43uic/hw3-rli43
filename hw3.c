
#include <stdio.h>

#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>


void loop() {
        
        
        
//          int status = 0;
 //       int status2 = 0;
        
  //      int pid2 = 0;
    //    char* from;
    //    char* to;
        
        while(1) {
            //int pipefds[2];
            char line[500];
            
            //Allocate memory
            char *argsList[120];
            for (int j = 0; j < 21; j++){
                argsList[j] = (char*)malloc(120*sizeof(char));
            }
            printf("CS361 >");
            fgets(line,500,stdin);
            line[strlen(line) - 1] = '\0';
            
            pid_t pid;    
            char * word;
            
            int i=0;
            word = strtok(line, " ");
            while(word) {
                    //printf("word: %s\n", word);
                    strcpy(argsList[i], word);
                    i++;    //move to next space
                    word = strtok(NULL, " ");//iterate
            }
            //strcpy(argsList[i], "\0");
            argsList[i] = NULL; //make the last part null
            
    		if(strcmp(argsList[0], "exit") == 0){
    			exit(0);
     		}
     		
            pid = fork();
            //child
            if (pid == 0) {
                execvp(argsList[0], argsList);
            }
            //parent
            else {
                int stat;
                waitpid(pid, &stat, WUNTRACED);
                printf("pid:%d status:%d\n", pid,  WEXITSTATUS(stat));
            }
        }
        
}
void sigintHandler(int sig) {
// 	char msg[] = "\ncaught sigint\n";
// 	write(1, msg, sizeof(msg));
	fprintf(stdout, "\ncaught sigint\n");
}

void sigtstpHandler( int sig) {
// 	char msg[]= "\ncaught sigtstp\n";
// 	write(1,msg, sizeof(msg));
	fprintf(stdout, "\ncaught sigtstp\n");
}

int main() {
    signal(SIGINT, sigintHandler);
	signal(SIGTSTP, sigtstpHandler);
    loop();
    return 0;
}

