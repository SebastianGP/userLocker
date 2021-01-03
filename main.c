#include "master.h"
int main(void){
    int newUser;
    int exitStatus;
    int regPipes[2];
    int vetPipes[2];
    int fp;
    int tempFP;
    char* masterPass = (char*)calloc(MAX_SZ, sizeof(char));
    char* tempBuffer = (char*)calloc(MAX_SZ, sizeof(char));
    printf("Are you new?: ");
    scanf("%d", &newUser); 
    if(newUser){
        printf("Enter a Master password (You can't reset this): ");
        scanf("%s", masterPass);
        fp = open("./locker.txt", O_WRONLY | O_CREAT, 0777);
        pipe(regPipes);
        pid_t pid = fork();
        setup(pid, regPipes, masterPass, fp, exitStatus);
        
        printf("Setup done\n");	
        //Portal entry is done
        /*TODO: Password entries open*/
    }else{
    	//char* tempBuffer = (char*)calloc(MAX_SZ, sizeof(char));
        printf("Enter Master password: ");
        scanf("%s", masterPass);
        pipe(vetPipes);
        //***************TEMP FILE***************************************
        tempFP = open("./tmp.txt", O_WRONLY | O_CREAT, 0777);
        //***************************************************************
        pid_t pid = fork();
        validator(pid, vetPipes, masterPass, tempFP, tempBuffer, exitStatus);
        //strVald(buffer, masterPass);
    }
    
    printf("String: %s\n", tempBuffer);
    
    
    return 0;
    
}
