#include "master.h"

int main(void)
{
    int newUser;
    int running = 1;
    int hasAccess = 1;
    int selection;
    int terminate = 0;
    printf("1 for yes, 0 for no\n");
    printf("Are you new?: ");
    scanf("%d", &newUser);

    hasAccess = boot(newUser);

    while(running && hasAccess){
        printf("Add, remove, or edit?: ");
        scanf("%d", &selection);
        
        switch(selection){
            case ADD:
                printf("ADD\n");
                break;
            case EDIT:
                printf("EDIT \n");
                break;
            case REMOVE:
                printf("REMOVE\n");
                break;
        }

        if(terminate == 3){
            printf("Terminating :)\n");
            exit(0);
        }
        terminate += 1;
    }
    
    return 0;
}

