#ifndef INPUT_H
#define INPUT_H

#include "types.h"

void read_input(char* message,char buffer[1024],int size);
void analyse_input(Status *s, char command[1024]);
int tokenize(char* command, char* command_flags[6]);
int is_number(char *text);

#endif