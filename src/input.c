#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../headers/types.h"
#include "../headers/input.h"
#include "../headers/nodes.h"
#include "../headers/files.h"
#include "../headers/undo-redo.h"

void read_input(char* message,char buffer[1024],int size){
        printf("%s",message);
        fgets(buffer,size,stdin);
        buffer[strcspn(buffer,"\n")] = '\0';
    }

void analyse_input(Status *s, char command[1024]){
    if(command[0] == ':'){
        int count;
        char *command_flags[6] = {NULL};
        
        count = tokenize(command, command_flags);
        if (count == 0) return;

        //just extra stuff to keep it clean
        char* clean_flags[6] = {NULL}; 
        for (int i = 0; i < count; i++) {
            clean_flags[i] = malloc(1024); 
            if (clean_flags[i] != NULL) {
                strcpy(clean_flags[i], command_flags[i]);
            }
        }

        if (is_number(clean_flags[0])) {
            s->HTC = point_line(s->HTC, atoi(clean_flags[0]));
            
        } else if (!strcmp(clean_flags[0], "undo")) {
            undo_handler(s, NULL, 1);
            
        } else if (!strcmp(clean_flags[0], "redo")) {
            redo_handler(s, NULL);
            
        } else if (!strcmp(clean_flags[0], "i") && count > 2 && is_number(clean_flags[1])) {
            undo_handler(s, clean_flags, 0);
            s->HTC = insert_line(s->HTC, atoi(clean_flags[1]), clean_flags[2]);
            
        } else if (!strcmp(clean_flags[0], "dl") && count > 1 && is_number(clean_flags[1])) {
            Node* target = find_line(s->HTC.head, atoi(clean_flags[1]));
            if (target != NULL) {
                clean_flags[2] = realloc(clean_flags[2], 1024);
                strcpy(clean_flags[2], target->line);
                undo_handler(s, clean_flags, 0);
                s->HTC = delete_line(s->HTC, atoi(clean_flags[1]));
            } else {
                printf("Line non-existent!\n");
            }
            
        } else if (!strcmp(clean_flags[0], "swap") && count > 2 && is_number(clean_flags[1]) && is_number(clean_flags[2])) {
            undo_handler(s, clean_flags, 0);
            s->HTC = swap(s->HTC, atoi(clean_flags[1]), atoi(clean_flags[2]));
            
        } else if (!strcmp(clean_flags[0], "mu") && count > 1 && is_number(clean_flags[1])) {
            undo_handler(s, clean_flags, 0);
            s->HTC = move_up(s->HTC, atoi(clean_flags[1]));
            
        } else if (!strcmp(clean_flags[0], "md") && count > 1 && is_number(clean_flags[1])) {
            undo_handler(s, clean_flags, 0);
            s->HTC = move_down(s->HTC, atoi(clean_flags[1]));
            
        } else if (!strcmp(clean_flags[0], "write")) {
            save_file(s->HTC, s->file_path);
            
        } else if (!strcmp(clean_flags[0], "print")) {
            s->print = (s->print + 1) % 2;
            printf(s->print == 1 ? "Automatic print mode set!\n" : "Automatic print mode reset\n");
        }

        for (int i = 0; i < 6; i++) {
            if (clean_flags[i] != NULL) free(clean_flags[i]);
        }
    } 
    else {
        char* clean_flags[6] = {NULL};
        for(int i = 0; i < 4; i++) clean_flags[i] = malloc(1024);
        
        int index = 1;
        Node* curr = s->HTC.head;
        while(curr != NULL && curr != s->HTC.current) {
            index++;
            curr = curr->svt;
        }

        strcpy(clean_flags[0], "modify");
        snprintf(clean_flags[1], 1024, "%d", index);
        strcpy(clean_flags[2], s->HTC.current->line); 
        
        if(s->HTC.current->svt == NULL) {
            strcpy(clean_flags[3], "1"); 
        } else {
            strcpy(clean_flags[3], "0");
        }

        undo_handler(s, clean_flags, 0);
        
        s->HTC = modify_line(s->HTC, command);

        for (int i = 0; i < 4; i++) free(clean_flags[i]);
    }

    if(s->print == 1){
        display_nodes(s->HTC);
    }
}

int tokenize(char* command, char* command_flags[6]){
    int count = 0;
    char* p = command;
    if(*p == ':') p++;
    while(*p != '\0' && count < 6){
        while(*p == ' ') p++;
        if(*p == '\0' || *p == '\n' || *p == '\r') break;
        if(*p == '"'){
            p++;
            command_flags[count++] = p;
            while(*p != '"' && *p != '\0') p++;
            if(*p == '"'){ *p = '\0'; p++; }
        }else{
            command_flags[count++] = p;
            while(*p != ' ' && *p != '\0' && *p != '\n' && *p != '\r') p++;
            if(*p != '\0'){ *p = '\0'; p++; }
        }
    }
        return count;
}

int is_number(char *text){
if(text == NULL || *text == '\0') return 0;
for(int i = 0; text[i] != '\0'; i++){
    if(!isdigit(text[i])) return 0;
}
return 1;
}