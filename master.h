#ifndef __MASTER_H
#define __MASTER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_SZ 40

void setup(int pipes[], char* masterPass, int fp, int exitStatus){
    pid_t pid = fork();
    if(pid == 0){
        close(pipes[0]);
        close(fp);
        write(pipes[1], masterPass, strlen(masterPass));
        close(pipes[1]);
    }
    else{
        //STD_IN -> PIPE[0] -> execl(STD_IN)
        close(0);
        dup(pipes[0]);
        //execl(STD_IN) -> STD_OUT -> FP (OPEN FILE)
        close(1);
        dup(fp); 
        close(pipes[1]);
        execl("/usr/bin/shasum", "/usr/bin/shasum", NULL); 
        close(pipes[0]);
        close(fp);
        pid_t deadChild = wait(&exitStatus);
    }
}
//Finish this function below for a returning user
void strVald(char* hashedInput, char* hashedMaster){
    if(strcmp(hashedInput, hashedMaster) == 0){
        //User is in
        printf("Access granted.\n");
    }else{
        printf("Wrong\n");
    }
}

void validator(int pipes[], int buffPipes[], char* masterPass, char* hashedInput, int exitStatus){
    pid_t pid = fork();
	if(pid == 0){
		close(pipes[0]);
        close(buffPipes[0]);
        close(buffPipes[1]);
		write(pipes[1], masterPass, strlen(masterPass));
		close(pipes[1]);
        //child 2 process done
        exit(0);
	}
	else{
        pid_t pid2 = fork();
        if(pid2 == 0){
            //STD_IN -> PIPE[0] -> execl(STD_IN)
            close(0);
            dup(pipes[0]);
            //execl(STD_IN) -> STD_OUT -> buffPipes[1]
            close(1);
            dup(buffPipes[1]);
            close(pipes[1]);
            close(buffPipes[0]);
            execl("/usr/bin/shasum", "/usr/bin/shasum", NULL);
            close(buffPipes[1]);
            close(pipes[0]);
            //Child 1 process done
            exit(0);
        }
        else{
            close(pipes[0]);
            close(pipes[1]);
            close(buffPipes[1]);
            read(buffPipes[0], hashedInput, 40);
            close(buffPipes[0]);
            pid_t deadChild = wait(&exitStatus);
            //Parent waits for children processes to finish
        }
    }
}


void freeBuffs(char* hashedInput, char* masterPass, char* hashedMaster){
    free(hashedInput);
    free(masterPass);
    free(hashedMaster);
}

#endif
