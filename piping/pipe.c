#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "../utils/utils.h"
#include "pipe.h"

void split_pipe_command(char *command[], char *args1[], char *args2[]){
    int i = 0;
    for(;strcmp(command[i], "|") != 0; i++)
        args1[i] = command[i];

    i++;
    for(int j = 0; command[i] != NULL; i++, j++)
        args2[j] = command[i];
}

void execute_pipe_command(char *command[]){
    char *args1[1001], *args2[1001];
    split_pipe_command(command, args1, args2);

    int pipeFd[2];
    pid_t pid1, pid2;

    if(pipe(pipeFd) == -1){
        printf("error: cannot create a pipe\n");
        return;
    }

    if((pid1 = fork()) == -1){
        printf("error: cannot fork the process\n");
        return;
    }

    if(pid1 == 0){
        dup2(pipeFd[1], STDOUT_FILENO);

        close(pipeFd[0]);
        close(pipeFd[1]);

        execvp(args1[0], args1);
        printf("error: cannot execute the process\n");
    }

    if((pid2 = fork()) == -1){
        printf("error: cannot fork the process\n");
        return;
    }

    if(pid2 == 0){
        dup2(pipeFd[0], STDIN_FILENO);

        close(pipeFd[0]);
        close(pipeFd[1]);

        execvp(args2[0], args2);
        printf("error: cannot execute the process\n");
    }

    close(pipeFd[0]);
    close(pipeFd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

bool check_for_piping(char *command[]){
    for(int i = 0; command[i] != NULL; i++){
        if(strcmp(command[i], "|") == 0){
            execute_pipe_command(command);
            return 1;
        }
    }
    return 0;
}
