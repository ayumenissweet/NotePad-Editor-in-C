#ifndef TYPES_H
#define TYPES_H

typedef struct list{
    struct list *svt, *prv;
    char ln[1024];
} list;

typedef struct{
    list* head;
    list* tail;
    list* current;
} Main_L;

typedef struct {
    char action_data[6][255];
} Action;

typedef struct Status{
    Main_L HTC;
    char file_path[260];
    int print_mode;

    Action undo_stack[32];
    int undo_top;

    Action redo_stack[32];
    int redo_top;

    int skip;
} Status;

#endif
