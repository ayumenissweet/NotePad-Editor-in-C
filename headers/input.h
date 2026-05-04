#ifndef INPUT_H
#define INPUT_H

#include "types.h"

void read_input(char message[],char* text,int text_size,int newline);
int tokenize(char* command, char* command_flags[6]);
int analyse_input(Main_L HTC,char* command);

#endif