
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
        
        //int pipefds[2];
        char line[500];
        
        //Allocate memory
        char *argsList[100];
        for (int j = 0; j < 20; j++){
            argsList[j] = (char*)malloc(100*sizeof(char));
        }
        
//          int status = 0;
 //       int status2 = 0;
        
  //      int pid2 = 0;
    //    char* from;
    //    char* to;
        
        while(1) {
                printf("CS361 >");
                // x++;
                // if (x == 2) {
                //     break;
                // }
                fgets(line,500,stdin);
                line[strlen(line) - 1] = '\0';
                int pid;    
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
         		
        //  		if (strcmp(argsList[i], "|") == 0) {
         		    
         		    
        //  		}
         		
            
                //}
                //create pipe
                
                pid = fork();
                //child
                if (pid == 0) {
                    // if (strcmp(argsList[1], "|") == 0) {
                        
                    // }
                    execvp(argsList[0], argsList);
                }
                //parent
                else {
                    int stat;
                    waitpid(pid, &stat, WUNTRACED);
                    
                    printf("pid:%d status:%d\n", pid,  WEXITSTATUS(stat));
            // 		if(pid_2 != 0){
            // 			printf("pid:%i status:%i\n", pid2, status2,  WEXITSTATUS(status_2));
            // 		}
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

