#ifndef __MASTER_H
#define __MASTER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_SZ 40

void setup(pid_t pid, int pipes[], char* masterPass, int fp, int exitStatus){
    if(pid == 0){
        close(pipes[0]);
        close(fp);
        write(pipes[1], masterPass, strlen(masterPass));
        close(pipes[1]);
    }
    else{
        close(0);
        dup(pipes[0]);
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
void strVald(char* hashedInput, char* masterPass){
    if(strcmp(hashedInput, masterPass) == 0){
        //User is in
        printf("User is in\n");
    }
    else{
        printf("Master password is incorrect. Please try again");
    }
}


void validator(pid_t pid, int pipes[], char* masterPass, char* hashedInput, int exitStatus){
	if(pid == 0){
		//Write into pipe
		close(pipes[0]);
		write(pipes[1], masterPass, strlen(masterPass));
		close(pipes[1]);
	}else{
		//Read from pipes
		close(0);
		dup(pipes[0]);
		close(1);
		dup(pipes[1]);
		//use fdopen ----- finish later
		execl("/usr/bin/shasum", "/usr/bin/shasum", NULL);
		
		scanf("%s  -", hashedInput);
		close(pipes[0]);
		close(1);
		pid_t deadChild = wait(&exitStatus);
	}
}



#endif
