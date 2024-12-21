#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "external_commands.h"
#include "../redirection/redirection.h"

void execute_external(char *args[], char *redirection[]){
    int id =  fork();
    if(id == 0){
        check_for_redirection(redirection);
        execvp(args[0], args);
        printf("\n");
    }else if(id > 0){
        waitpid(id, NULL, 0);
    }else{
        printf("Fork Failed\n");
    }
}
