#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/undo-redo.h"
#include "../headers/listes.h"

Action create_reverse(char* log[6]){
    Action new_action = {0};

    if(!strcmp(log[0], "i")){
        strcpy(new_action.action_data[0], "dl");
        strcpy(new_action.action_data[1], log[1]);
        if(log[2] != NULL) strcpy(new_action.action_data[2], log[2]);

    }else if(!strcmp(log[0], "dl")){
        strcpy(new_action.action_data[0], "i");
        strcpy(new_action.action_data[1], log[1]);
        if(log[2] != NULL) strcpy(new_action.action_data[2], log[2]);

    }else if(!strcmp(log[0], "swap")){
        strcpy(new_action.action_data[0], "swap");
        strcpy(new_action.action_data[1], log[1]);
        if(log[2] != NULL) strcpy(new_action.action_data[2], log[2]);

    }else if(!strcmp(log[0], "mu")){
        strcpy(new_action.action_data[0], "md");
        int pos = atoi(log[1]);
        snprintf(new_action.action_data[1], sizeof(new_action.action_data[1]), "%d", pos - 1);

    }else if(!strcmp(log[0], "md")){
        strcpy(new_action.action_data[0], "mu");
        int pos = atoi(log[1]);
        snprintf(new_action.action_data[1], sizeof(new_action.action_data[1]), "%d", pos + 1);
    }

    return new_action;
}

void push(Action new_action, Action stack[32], int* stack_top){
    (*stack_top)++;
    stack[*stack_top] = new_action;
}

Action pop(Action stack[32], int* stack_top){
    Action act = stack[*stack_top];
    (*stack_top)--;
    return act;
}

void undo_handler(Status *s, char* log[6], int action){
    if(s->undo_top >= 31){
        printf("Stack is Full!\n");
        return;
    }

    if(!action){
        Action new_action = create_reverse(log);
        push(new_action, s->undo_stack, &s->undo_top);
    }else{
        if(s->undo_top == 0){
            printf("Undo Stack Is Empty!\n");
            return;
        }
        Action act = pop(s->undo_stack, &s->undo_top);
        printf("Action Undone\n");

        if(!strcmp(act.action_data[0], "i")){
            s->HTC = insert_line(&s->HTC, atoi(act.action_data[1]), act.action_data[2]);
        }else if(!strcmp(act.action_data[0], "dl")){
            s->HTC = delete_line(&s->HTC, atoi(act.action_data[1]));
        }else if(!strcmp(act.action_data[0], "swap")){
            s->HTC = swap(s->HTC, atoi(act.action_data[1]), atoi(act.action_data[2]));
        }else if(!strcmp(act.action_data[0], "mu")){
            s->HTC = move_line_up(&s->HTC, atoi(act.action_data[1]));
        }else if(!strcmp(act.action_data[0], "md")){
            s->HTC = move_line_down(&s->HTC, atoi(act.action_data[1]));
        }

        char* temp_log[6] = {
            act.action_data[0],
            act.action_data[1],
            act.action_data[2],
        };
        Action new_action = create_reverse(temp_log);
        push(new_action, s->redo_stack, &s->redo_top);
    }
}

void redo_handler(Status *s, char* log[6]){
    if(s->redo_top == 0){
        printf("Redo Stack Is Empty!\n");
        return;
    }

    Action act = pop(s->redo_stack, &s->redo_top);
    printf("Action Redone\n");

    if(!strcmp(act.action_data[0], "i")){
        s->HTC = insert_line(&s->HTC, atoi(act.action_data[1]), act.action_data[2]);
    }else if(!strcmp(act.action_data[0], "dl")){
        s->HTC = delete_line(&s->HTC, atoi(act.action_data[1]));
    }else if(!strcmp(act.action_data[0], "swap")){
        s->HTC = swap(s->HTC, atoi(act.action_data[1]), atoi(act.action_data[2]));
    }else if(!strcmp(act.action_data[0], "mu")){
        s->HTC = move_line_up(&s->HTC, atoi(act.action_data[1]));
    }else if(!strcmp(act.action_data[0], "md")){
        s->HTC = move_line_down(&s->HTC, atoi(act.action_data[1]));
    }

    char* temp_log[6] = {
        act.action_data[0],
        act.action_data[1],
        act.action_data[2],
        act.action_data[3],
        act.action_data[4],
        act.action_data[5]
    };
    Action new_action = create_reverse(temp_log);
    push(new_action, s->undo_stack, &s->undo_top);
}
