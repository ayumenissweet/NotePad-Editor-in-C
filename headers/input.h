#ifndef INPUT_H
#define INPUT_H

#include "types.h"

void read_input(char message[],char* text,int text_size,int newline);
int tokenize(char* command, char* command_flags[6]);
Main_L analyse_input(Main_L HTC,char* command,char file_path[260],int *print,Action undo_stack[32],int* undo_top,Action redo_stack[32],int* redo_top);
int save_log(char* command_flags[6]);
int is_number(char *text);

#endif