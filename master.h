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

void firstTime(pid_t pid, int pipes[], char* userName, int fp, int exitStatus){
    if(pid == 0){
        close(pipes[0]);
        close(fp);
        write(pipes[1], userName, strlen(userName));
        close(pipes[1]);
    }
    else{
        close(pipes[1]);
        close(0);
        dup(pipes[0]);
        close(1);
        dup(fp);
        execl("/usr/bin/shasum", "/usr/bin/shasum", NULL); 
        close(pipes[0]);
        close(fp);
        pid_t deadChild = wait(&exitStatus);
    }
}

//Finish this function below for a returning user
int strVal(char* password, char* masterPass){
    if(strcmp(password, masterPass) == 0){
        //User is in
    }
    else{
        printf("Master password is incorrect. Please try again");
    }
}

#endif
