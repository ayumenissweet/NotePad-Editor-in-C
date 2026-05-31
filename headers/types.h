#ifndef TYPES_H
#define TYPES_H


typedef struct Node{
    char line[1024];
    struct Node* prv;
    struct Node* svt;
}Node;


typedef struct {
    Node *head,*tail,*current;
}Main_List;


typedef struct {
    char action_data[4][1024];
    // [0] = command ("i","dl","swap","mu","md","modify")
    // [1] = line number
    // [2] = content (for i, dl, modify)
    // [3] = second line number (swap only), or "1" if modify created a new node
}Action;

typedef struct{
    Main_List HTC;
    char file_path[255];
    int print;
    Action undo_stack[32];
    Action redo_stack[32];
    int undo_top;
    int redo_top;
}Status;

#endif