#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/undo-redo.h"
#include "../headers/listes.h"

Action create_reverse(char* log[6]){
    Action new_action;
    
    if(!strcmp(log[0],"i")){
        strcpy(new_action.action_data[0],"dl"); 
    }else if(!strcmp(log[0],"dl")){
        strcpy(new_action.action_data[0],"i"); 
    }else{
        strcpy(new_action.action_data[0],"swap"); 
    }
    //this works for insert,delete,redo
    strcpy(new_action.action_data[1],log[1]); 
    strcpy(new_action.action_data[2],log[2]); 
    
    return new_action;
}

Main_L undo_handler(Main_L* HTC, char* log[6],int action, Action undo_stack[32],int* undo_top, Action redo_stack[32],int* redo_top){
    if(*undo_top >= 31){
        printf("Stack is Full!\n");
        return *HTC;
    }

    if(!action){
        Action new_action = create_reverse(log);

        push(new_action,undo_stack,undo_top);

        printf("Action Pushed!\n");
    }else{
        if(*undo_top == 0){
            printf("Undo Stack Is Empty!\n");
            return *HTC;
        }
        Action act= pop(undo_stack,undo_top);
        printf("Action Undone\n");
        if(!strcmp(act.action_data[0],"i")){
            *HTC =  insert_line(HTC,atoi(act.action_data[1]),act.action_data[2]);
        }else if (!strcmp(act.action_data[0],"dl")){
            *HTC = delete_line(HTC,atoi(act.action_data[1]));
        }else if (!strcmp(act.action_data[0],"swap")){
            *HTC = swap(*HTC,atoi(act.action_data[1]),atoi(act.action_data[2]));
        }

        char* temp_log[6] = {
        act.action_data[0],
        act.action_data[1],
        act.action_data[2],
        };  
        Action new_action = create_reverse(temp_log);
        push(new_action,redo_stack,redo_top);
        printf("Pushed successly : %d\n",*redo_top);
    }
    return *HTC;
}

Main_L redo_handler(Main_L* HTC, char* log[6], Action undo_stack[32],int* undo_top, Action redo_stack[32],int* redo_top){
        if((*redo_top) == 0){
            printf("Redo Stack Is Empty!");
            return *HTC;
        }

        Action act= pop(redo_stack,redo_top); 
        
        printf("Action Redone\n");
        if(!strcmp(act.action_data[0],"i")){
            *HTC = insert_line(HTC,atoi(act.action_data[1]),act.action_data[2]);
        }else if (!strcmp(act.action_data[0],"dl")){
            *HTC = delete_line(HTC,atoi(act.action_data[1]));
        }else if (!strcmp(act.action_data[0],"swap")){
            *HTC = swap(*HTC,atoi(act.action_data[1]),atoi(act.action_data[2]));
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

        push(new_action,undo_stack,undo_top);
    return *HTC;
}

void push(Action new_action, Action stack[32],int* stack_top){
    (*stack_top)++;
    stack[*stack_top] = new_action;
}

Action pop(Action stack[32],int* stack_top){
    Action act = stack[*stack_top];
    (*stack_top)--;
    return act;
}