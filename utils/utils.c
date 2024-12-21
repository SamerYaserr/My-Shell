#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

void print_prompt(){
    char *username;
    char hostname[100];
    char cwd[100];

    username = getpwuid(getuid())->pw_name;
    gethostname(hostname, 100);
    getcwd(cwd, 100);

    printf("\033[1;34m%s@%s\033[0m:\033[1;32m%s\033[0m$ ", username, hostname, cwd);
}

char *input(){
    char *command = NULL;
    size_t size = 0;
    ssize_t len;

    len = getline(&command, &size, stdin);
    if (len == -1) {
        perror("getline");
        free(command);
        return NULL;
    }

    command[strlen(command) - 1] = 0;
    return command;
}

char *arr[3] = {"<", ">", "2>"};

void split_command(char *command, char *args[][1001], char *redirection[][3]){
    char *token = strtok(command, " \t\n");
    int i = 0, cmdId = 0;

    for(int id = 0; id < 1001; id++)
    	for(int j = 0; j < 3; j++)
	    redirection[id][j] = NULL;

    while (token != NULL) {
        if(strcmp(token, "&") == 0){
	    args[cmdId][i] = NULL;
            token = strtok(NULL, " \t\n");
	    i = 0;
	    cmdId++;
	    continue;
        }

	bool can = 0;
	for(int j = 0; j < 3; j++){
	    if(strcmp(token, arr[j]) == 0){
		token = strtok(NULL, " \t\n");
                redirection[cmdId][j] = (char *)malloc(100 * sizeof(char));
                redirection[cmdId][j] = token;
		can = 1;
            }
	}

        args[cmdId][i] = token;
        token = strtok(NULL, " \t\n");
	if(!can)
            i++;
    }

    args[cmdId][i] =  NULL;
    args[cmdId + 1][0] = NULL;
}
