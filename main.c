#include "master.h"
int main(void){
    int newUser;
    int exitStatus;
    int pipes[2];
    char* userName = (char*)calloc(MAX_SZ, sizeof(char));
    pipe(pipes);
    printf("Are you new?: ");
    scanf("%d", &newUser); 
    if(newUser){
        printf("Enter a password: ");
        scanf("%s", userName);
        int fp = open("./locker.txt", O_WRONLY | O_CREAT, 0777);
        pid_t pid = fork();
        firstTime(pid, pipes, userName, fp, exitStatus);
    }else{
        printf("Leave, implementation coming soon :)) \n");
    }
    return 0;
}
