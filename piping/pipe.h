#ifndef PIPE_H
#define PIPE_H

void split_pipe_command(char *command[], char *args1[], char *args2[]);

void execute_pipe_command(char *command[]);

bool check_for_piping(char *command[]);

#endif
