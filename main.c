#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void){
   
    char userName;
    printf("Enter password:");
    scanf("%s", &userName);
    int exitStatus;
    pid_t pid = fork();
    int pipes[2];
    pipe(pipes);
    int fp = open("./locker.txt", O_WRONLY | O_CREAT, 0777);
    if(pid == 0){
        close(0);
        dup(pipes[0]);
        close(1);
        dup(fp);
        close(pipes[1]);
        execl("/sbin/md5", "/sbin/md5", NULL);
        close(pipes[0]);
        close(fp);
    }
    else{
        //close STD_OUT
        close(1);
        dup(pipes[1]);
        close(pipes[0]);
        execl("/bin/echo", "/bin/echo", userName, NULL);
        close(pipes[1]);
        pid_t deadChild = wait(&exitStatus);
    }
    return 0;
}
