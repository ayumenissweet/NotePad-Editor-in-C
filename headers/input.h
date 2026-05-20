#ifndef INPUT_H
#define INPUT_H

#include "types.h"

void read_input(char message[], char* text, int text_size, int newline);
int tokenize(char* command, char* command_flags[6]);
void analyse_input(Status *s, char* command);
int is_number(char *text);

#endif
