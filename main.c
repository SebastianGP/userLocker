#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_SZ 40

int main(void){
    char* userName = (char*)calloc(MAX_SZ, sizeof(char));
    printf("Enter password: ");
    scanf("%s", userName);
    int exitStatus;
    int pipes[2];
    pipe(pipes);
    int fp = open("./locker.txt", O_WRONLY | O_CREAT, 0777);
    pid_t pid = fork();
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
    return 0;
}
