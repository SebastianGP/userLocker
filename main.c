#include "master.h"
int main(void){
    int newUser;
    int exitStatus;
    int regPipes[2];
    int vetPipes[2];
    char* masterPass = (char*)calloc(MAX_SZ, sizeof(char));
    printf("Are you new?: ");
    scanf("%d", &newUser); 
    if(newUser){
        printf("Enter a Master password (You can't reset this): ");
        scanf("%s", masterPass);
        int fp = open("./locker.txt", O_WRONLY | O_CREAT, 0777);
        pipe(regPipes);
        pid_t pid = fork();
        setup(pid, regPipes, masterPass, fp, exitStatus);
        printf("Setup done\n");
        //Portal entry is done
        /*TODO: Password entries open*/
    }else{
    	 char* buffer = (char*)calloc(MAX_SZ, sizeof(char));
        printf("Enter Master password: ");
        scanf("%s", masterPass);
        pipe(vetPipes);
        pid_t pid = fork();
        validator(pid, vetPipes, masterPass, buffer, exitStatus);
        strVald(buffer, masterPass);
    }
    return 0;
}
