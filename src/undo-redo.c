#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/undo-redo.h"
#include "../headers/nodes.h"

Action create_reverse(char* log[6]){
    Action new_action = {0};

    if(!log[0]) return new_action;

    if(!strcmp(log[0], "i")){
        strncpy(new_action.action_data[0], "dl", 1024);
        if(log[1]) strncpy(new_action.action_data[1], log[1], 1024);
        if(log[2]) strncpy(new_action.action_data[2], log[2], 1024);

    }else if(!strcmp(log[0], "dl")){
        strncpy(new_action.action_data[0], "i", 1024);
        if(log[1]) strncpy(new_action.action_data[1], log[1], 1024);
        if(log[2]) strncpy(new_action.action_data[2], log[2], 1024);

    }else if(!strcmp(log[0], "swap")){
        strncpy(new_action.action_data[0], "swap", 1024);
        if(log[1]) strncpy(new_action.action_data[1], log[1], 1024);
        if(log[2]) strncpy(new_action.action_data[2], log[2], 1024);

    }else if(!strcmp(log[0], "mu")){
        strncpy(new_action.action_data[0], "md", 1024);
        int pos = atoi(log[1]);
        snprintf(new_action.action_data[1], 1024, "%d", pos - 1);

    }else if(!strcmp(log[0], "md")){
        strncpy(new_action.action_data[0], "mu", 1024);
        int pos = atoi(log[1]);
        snprintf(new_action.action_data[1], 1024, "%d", pos + 1);
        
    }else if(!strcmp(log[0], "modify")){
        strncpy(new_action.action_data[0], "modify", 1024);
        if(log[1]) strncpy(new_action.action_data[1], log[1], 1024);
        if(log[2]) strncpy(new_action.action_data[2], log[2], 1024);
        if(log[3]) strncpy(new_action.action_data[3], log[3], 1024);
    }

    return new_action;
}

void push(Action new_action, Action stack[32], int* stack_top){
    if (*stack_top >= 31) return;
    (*stack_top)++;
    stack[*stack_top] = new_action;
}

Action pop(Action stack[32], int* stack_top){
    Action act = {0};
    if (*stack_top < 0) return act;
    act = stack[*stack_top];
    (*stack_top)--;
    return act;
}

void execute_action(Status *s, Action act) {
    if(!strcmp(act.action_data[0], "i")){
        s->HTC = insert_line(s->HTC, atoi(act.action_data[1]), act.action_data[2]);
    }else if(!strcmp(act.action_data[0], "dl")){
        s->HTC = delete_line(s->HTC, atoi(act.action_data[1]));
    }else if(!strcmp(act.action_data[0], "swap")){
        s->HTC = swap(s->HTC, atoi(act.action_data[1]), atoi(act.action_data[2]));
    }else if(!strcmp(act.action_data[0], "mu")){
        s->HTC = move_up(s->HTC, atoi(act.action_data[1]));
    }else if(!strcmp(act.action_data[0], "md")){
        s->HTC = move_down(s->HTC, atoi(act.action_data[1]));
    }else if(!strcmp(act.action_data[0], "modify")){
        s->HTC = point_line(s->HTC, atoi(act.action_data[1]));
        if (!strcmp(act.action_data[3], "1")) {
            strncpy(s->HTC.current->line, act.action_data[2], 1024);
            Node* extra_tail = s->HTC.current->svt;
            if (extra_tail != NULL) {
                s->HTC.current->svt = NULL;
                s->HTC.tail = s->HTC.current;
                free(extra_tail);
            }
        } else if (!strcmp(act.action_data[3], "2")) {
            s->HTC = modify_line(s->HTC, act.action_data[2]);
        } else {
            strncpy(s->HTC.current->line, act.action_data[2], 1024);
            if (s->HTC.current->svt != NULL)
                s->HTC.current = s->HTC.current->svt;
        }
    }
}

void undo_handler(Status *s, char* log[6], int action){
    if(!action){
        if(s->undo_top >= 31){
            for(int i = 0; i < 31; i++) {
                s->undo_stack[i] = s->undo_stack[i+1];
            }
            s->undo_top = 30;
        }
        Action new_action = create_reverse(log);
        push(new_action, s->undo_stack, &s->undo_top);
        
        s->redo_top = -1; 
    }
    else {
        if(s->undo_top < 0){
            printf("Undo Stack Is Empty!\n");
            return;
        }
        Action act = pop(s->undo_stack, &s->undo_top);
        
        char modify_backup[1024] = {0};
        char* temp_log[6] = {
            act.action_data[0],
            act.action_data[1],
            act.action_data[2],
            act.action_data[3],
            NULL, NULL
        };

        if (!strcmp(act.action_data[0], "modify")) {
            Node* target = find_line(s->HTC.head, atoi(act.action_data[1]));
            if (target) strncpy(modify_backup, target->line, 1024);
            temp_log[2] = modify_backup;
            temp_log[3] = !strcmp(act.action_data[3], "1") ? "2" : "0";
        }

        execute_action(s, act);
        printf("Action Undone\n");

        Action new_redo = create_reverse(temp_log);
        push(new_redo, s->redo_stack, &s->redo_top);
    }
}

void redo_handler(Status *s, char* log[6]){
    if(s->redo_top < 0){
        printf("Redo Stack Is Empty!\n");
        return;
    }

    Action act = pop(s->redo_stack, &s->redo_top);

    char modify_backup[1024] = {0};
    char* temp_log[6] = {
        act.action_data[0],
        act.action_data[1],
        act.action_data[2],
        act.action_data[3],
        NULL, NULL
    };

    if (!strcmp(act.action_data[0], "modify")) {
        Node* target = find_line(s->HTC.head, atoi(act.action_data[1]));
        if (target) strncpy(modify_backup, target->line, 1024);
        temp_log[2] = modify_backup;
        temp_log[3] = !strcmp(act.action_data[3], "1") ? "2" : "0";
    }

    execute_action(s, act);
    
    printf("Action Redone\n");

    Action new_undo = create_reverse(temp_log);
    push(new_undo, s->undo_stack, &s->undo_top);
}