#include "master.h"

int main(void)
{
    int newUser;
    int running = 1;
    int hasAccess = 0;
    int selection;
    int exit = 0;
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

        if(exit){
            printf("Terminating :)\n");
        }
    }
    
    return 0;
}

