#ifndef UTILS_H
#define UTILS_H

void print_prompt();

char *input();

void split_command(char *command, char *args[][1001], char *redirection[][3]);

#endif

