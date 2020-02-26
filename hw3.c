
#include <stdio.h>

#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int execute(char* args) {
    printf("4\n");
        int i = 0;
    
        while(1) {
            if (i == 10) {
                
                break;
            }
    		if(args[i] == '\0'){
    			break;
    		}
    		if(strcmp(&args[0], "exit") == 0){
    			exit(0);
    			return 0;
    			break;
     		}
     		
     		if (strcmp(&args[i], ";") == 0) {
     		    
     		    
     		}
     		++i;
     		
     		printf("loop");
        }
        return 0;
}

void loop() {
        int i = 0;
        char line[500];
        char** argsList = malloc(1000 * sizeof(char*));
        char * word;
        int status = 0;
        int status2 = 0;
        int pid = 0;
        int pid2 = 0;
        
        while(1) {
                printf("CS361 >");
                fgets(line,500,stdin);
                line[strlen(line) - 1] = '\0';
                printf("1\n");

                i=0;
                word = strtok(line, " ");
                printf("2\n");
                while(word != NULL) {
                        argsList[i] = word;
                        i++;    //move to next space
                        word = strtok(NULL, " ");//iterate
                }
                argsList[i] = NULL; //make the last part null
                printf("3\n");

                status = execute(*argsList);
                
                
                pid = fork();
                //child
                if (pid == 0) {
                    
                    
                }
                //parent
                else {
                    
                    
  //                  printf("pid:%i status:%i\n", pid, status,  WEXITSTATUS(status));
//            		if(pid_2 != 0){
    //        			printf("pid:%i status:%i\n", pid2, status2,  WEXITSTATUS(status_2));
      //      		}
                }
        }
}
void sigintHandler(int sig) {
	char msg[] = "\ncaught sigint\n";
	write(1, msg, sizeof(msg));
}

void sigtstpHandler( int sig) {
	char msg[]= "\ncaught sigtstp\n";
	write(1,msg, sizeof(msg));
}

int main() {
    signal(SIGINT, sigintHandler);
	signal(SIGTSTP, sigtstpHandler);
    loop();
    return 0;
}

