#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "../headers/input.h"
#include "../headers/files.h"
#include "../headers/listes.h"
#include "../headers/undo-redo.h"

void read_input(char message[], char* text, int text_size, int newline){
    printf("%s", message);
    fgets(text, text_size, stdin);
    if(newline == 0){
        text[strcspn(text, "\n")] = '\0';
    }
}

void analyse_input(Status *s, char* command){
    if(command[0] == ':'){
        char* command_flags[6];
        int count = tokenize(command, command_flags);

        if(strcmp(command_flags[0], "undo") != 0 && strcmp(command_flags[0], "redo") != 0){
            s->redo_top = 0;
        }
        if(strcmp(command_flags[0], "i") == 0){
            if(is_number(command_flags[1]) && count > 2){
                s->HTC = insert_line(&s->HTC, atoi(command_flags[1]), command_flags[2]);
                undo_handler(s, command_flags, 0);
            }
        }else if(strcmp(command_flags[0], "swap") == 0){
            if(is_number(command_flags[1]) && is_number(command_flags[2])){
                s->HTC = swap(s->HTC, atoi(command_flags[1]), atoi(command_flags[2]));
                undo_handler(s, command_flags, 0);
            }
        }else if(strcmp(command_flags[0], "dl") == 0){
            if(is_number(command_flags[1])){
                list* p = find_line(s->HTC, atoi(command_flags[1]));
                if(p){
                    command_flags[2] = strdup(p->ln);
                }
                command_flags[2][strcspn(command_flags[2], "\n")] = '\0';
                undo_handler(s, command_flags, 0);
                s->HTC = delete_line(&s->HTC, atoi(command_flags[1]));
            }
        }else if(strcmp(command_flags[0], "mu") == 0){
            if(is_number(command_flags[1])){
                s->HTC = move_line_up(&s->HTC, atoi(command_flags[1]));
                undo_handler(s, command_flags, 0);
            }
        }else if(strcmp(command_flags[0], "md") == 0){
            if(is_number(command_flags[1])){
                s->HTC = move_line_down(&s->HTC, atoi(command_flags[1]));
                undo_handler(s, command_flags, 0);
            }
        }else if(strcmp(command_flags[0], "uniq") == 0){
            s->HTC = remove_dup(s->HTC);
        }else if(strcmp(command_flags[0], "view") == 0){
            display_list(s->HTC);
        }else if(strcmp(command_flags[0], "view_n") == 0){
            display_list_n(s->HTC); // with numbered lines
        }else if(strcmp(command_flags[0], "view_even") == 0){
            display_odd(s->HTC.head);   //with a simple argument change display_odd can display even lines too
        }else if(strcmp(command_flags[0], "view_odd") == 0){
            display_odd(s->HTC.head->svt); 
        }else if(strcmp(command_flags[0], "write") == 0){
            save_file(&s->HTC, s->file_path);
        }else if(is_number(command_flags[0])){
            s->HTC = move_to_line(s->HTC, atoi(command_flags[0]));
        }else if(strcmp(command_flags[0], "print") == 0){
            s->print_mode = (s->print_mode + 1) % 2;
            printf(s->print_mode == 1 ? "automatic print mode set!\n" : "automatic print mode reset!\n");
        }else if(strcmp(command_flags[0], "undo") == 0){
            undo_handler(s, command_flags, 1);
        }else if(strcmp(command_flags[0], "redo") == 0){
            redo_handler(s, command_flags);
        }else if(strcmp(command_flags[0], "menu") == 0){
            s->skip = 1; //allows exiting the loop in the main function, thus resetting the programme
        }else if(strcmp(command_flags[0], "quit") == 0){
            exit(1); //direct programme exit
        }

        if(s->print_mode == 1 && strcmp(command_flags[0], "view_n") != 0 && strcmp(command_flags[0], "view") != 0){
            display_list_n(s->HTC);
        }
    }else{
        s->HTC = modify_line(&s->HTC, command);
        if(s->print_mode == 1){
            display_list_n(s->HTC);
        }
        s->redo_top = 0;
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
