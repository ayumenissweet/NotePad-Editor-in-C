#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../headers/input.h"
#include "../headers/files.h"
#include "../headers/listes.h"
#include "../headers/undo-redo.h"

void read_input(char message[],char* text,int text_size,int newline){
    printf("%s",message);
    fgets(text,text_size,stdin);
    if(newline == 0){
        text[strcspn(text,"\n")] = '\0';
    }
}

Main_L analyse_input(Main_L HTC,char* command,char file_path[260],int *print,Action undo_stack[32],int* undo_top,Action redo_stack[32],int* redo_top){
    if(command[0] == ':'){
        char* command_flags[6];
        int count = tokenize(command, command_flags);

        if(strcmp(command_flags[0],"undo") != 0 && strcmp(command_flags[0],"redo") != 0){ //any action other than undo resets the redo stack
            *redo_top= 0;
        }

        if(strcmp(command_flags[0],"i") == 0){
            if(is_number(command_flags[1]) && count > 2){
                HTC = insert_line(&HTC,atoi(command_flags[1]),command_flags[2]);
                undo_handler(&HTC,command_flags,0,undo_stack,undo_top,redo_stack,redo_top);
        }}else if(strcmp(command_flags[0],"swap") == 0){
            if(is_number(command_flags[1]) && is_number(command_flags[2])){
                HTC = swap(HTC,atoi(command_flags[1]),atoi(command_flags[2]));
                undo_handler(&HTC,command_flags,0,undo_stack,undo_top,redo_stack,redo_top);
        }}else if(strcmp(command_flags[0],"dl") == 0){
            if(is_number(command_flags[1])){
                list* p = find_line(HTC,atoi(command_flags[1]));
                if(p){
                    command_flags[2] = strdup(p->ln);
                }
                command_flags[2][strcspn(command_flags[2],"\n")] = '\0';
                undo_handler(&HTC,command_flags,0,undo_stack,undo_top,redo_stack,redo_top);

                HTC = delete_line(&HTC,atoi(command_flags[1]));
            }
        }else if(strcmp(command_flags[0],"mu") == 0){
            if(is_number(command_flags[1])){
                HTC = move_line_up(&HTC,atoi(command_flags[1])); 
                undo_handler(&HTC,command_flags,0,undo_stack,undo_top,redo_stack,redo_top);                
            }
        }else if(strcmp(command_flags[0],"md") == 0){
            if(is_number(command_flags[1])){
                HTC = move_line_down(&HTC,atoi(command_flags[1])); 
                undo_handler(&HTC,command_flags,0,undo_stack,undo_top,redo_stack,redo_top);                
            }
        }else if(strcmp(command_flags[0],"uniq") == 0){
            HTC = remove_dup(HTC);
        }else if(strcmp(command_flags[0],"view") == 0){
            display_list(HTC);
        }else if(strcmp(command_flags[0],"view_n") == 0){
            display_list_n(HTC);
        }else if(strcmp(command_flags[0],"write") == 0) {
            save_file(&HTC, file_path);
        }else if(is_number(command_flags[0])){
            HTC = move_to_line(HTC,atoi(command_flags[0]));
        }else if (strcmp(command_flags[0],"print") == 0){
            *print = ((*print) + 1) % 2;
            printf(*print == 1 ? "automatic print mode set!\n" : "automatic print mode reset!\n");
        }else if (strcmp(command_flags[0],"undo") == 0){
            HTC = undo_handler(&HTC,command_flags,1,undo_stack,undo_top,redo_stack,redo_top);
        }else if(strcmp(command_flags[0],"redo") == 0){
            HTC = redo_handler(&HTC,command_flags,undo_stack,undo_top,redo_stack,redo_top);
        }else if(strcmp(command_flags[0],"quit") == 0){
            exit(1);
        }

        if(*print == 1 && strcmp(command_flags[0],"view_n") != 0 && strcmp(command_flags[0],"view") != 0){
            display_list_n(HTC);
        }
    }else{
        HTC = modify_line(&HTC,command);
        if (*print == 1){
            display_list_n(HTC);
        }
        *redo_top = 0;
    }

    return HTC;
}

int tokenize(char* command, char* command_flags[6]) {
    int count = 0;
    char* p = command;
    if (*p == ':') p++;
    while (*p != '\0' && count < 6) {
        while (*p == ' ') p++;                        
        if (*p == '\0' || *p == '\n' || *p == '\r') break;  
        if (*p == '"') {
            p++;
            command_flags[count++] = p;
            while (*p != '"' && *p != '\0') p++;
            if (*p == '"') { *p = '\0'; p++; }
        } else {
            command_flags[count++] = p;
            while (*p != ' ' && *p != '\0' && *p != '\n' && *p != '\r') p++; 
            if (*p != '\0') { *p = '\0'; p++; }
        }
    }
    return count;
}

int is_number(char *text) {
    if (text == NULL || *text == '\0') return 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (!isdigit(text[i])) return 0;
    }
    return 1;
}