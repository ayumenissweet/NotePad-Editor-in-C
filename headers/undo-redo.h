#ifndef UNDO_REDO_H
#define UNDO_REDO_H

#include "types.h"

Action  create_reverse(char* log[6]);
void    push(Action new_action, Action stack[32], int* stack_top);
Action  pop(Action stack[32], int* stack_top);
void    undo_handler(Status *s, char* log[6], int action);
void    redo_handler(Status *s, char* log[6]);

#endif
