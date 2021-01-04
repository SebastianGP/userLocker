#include "master.h"

void hashedMasterPass(char *hashedMaster);

int main(void)
{
    int newUser;
    int exitStatus;

    int fp;

    /* PIPES */
    int regPipes[2];
    int vetPipes[2];
    int buffPipes[2];
    /*  ----   */

    /* BUFFERS */
    char* masterPass = (char*)calloc(MAX_SZ, sizeof(char));
    char* hashedMaster = (char*)calloc(MAX_SZ, sizeof(char));
    char* hashedInput = (char*)calloc(MAX_SZ, sizeof(char));
    /*  ----   */


    printf("Are you new?: ");
    scanf("%d", &newUser);
    if(newUser){
        printf("Enter a Master password (You can't reset this): ");
        scanf("%s", masterPass);
        fp = open("./locker.txt", O_WRONLY | O_CREAT, 0777);
        pipe(regPipes);
        setup(regPipes, masterPass, fp, exitStatus);        
        printf("Setup done\n");
        /*TODO: Password entries open*/
    }else{
        printf("Enter Master password: ");
        scanf("%s", masterPass);
        pipe(vetPipes);
        pipe(buffPipes);
        validator(vetPipes, buffPipes, masterPass, hashedInput, exitStatus);
        hashedMasterPass(hashedMaster);
        strVald(hashedInput, hashedMaster);
        /*TODO: Password entries open*/
    }
    freeBuffs(hashedInput, masterPass, hashedMaster);
    return 0;
}

void hashedMasterPass(char *hashedMaster)
{
    FILE *fd;
    fd = fopen("locker.txt", "r");
    int x = fread(hashedMaster, 1, 40, fd);
    fclose(fd);
}