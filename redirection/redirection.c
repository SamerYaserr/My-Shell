#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "redirection.h"

void check_for_redirection(char *redirection[]){
    for(int i = 0; i < 3; i++){
        if(redirection[i] == NULL)
            continue;
        int fd = open(redirection[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        dup2(fd, i);
    }
}
