#ifndef UNDO_REDO_H
#define UNDO_REDO_H

#include "types.h"

void push(Action new_action, Action stack[32],int* stack_top);
Action pop(Action stack[32],int* stack_top);
Main_L redo_handler(Main_L* HTC, char* log[6],int action, Action undo_stack[32],int* undo_top, Action redo_stack[32],int* redo_top);
Main_L undo_handler(Main_L* HTC, char* log[6],int action, Action undo_stack[32],int* undo_top, Action redo_stack[32],int* redo_top);
Action create_reverse(char* log[6]);

#endif