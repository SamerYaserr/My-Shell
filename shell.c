#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdbool.h>
#include "utils/utils.h"
#include "piping/pipe.h"
#include "external_commands/external_commands.h"

int main(int argc, char *argv[]) {
    char *command = NULL;
    char *args[1001][1001];
    char *redirection[1001][3];

    while(1){
        print_prompt();
        command = input();
        if(strcmp(command, "exit") == 0){
            break;
        }

        split_command(command, args, redirection);
        for(int i = 0; args[i][0] != NULL; i++){
            if(check_for_piping(args[i]))
                continue;
            execute_external(args[i], redirection[i]);
        }
    }
    return 0;
}
