#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../headers/input.h"
#include "../headers/files.h"
#include "../headers/listes.h"

void read_input(char message[],char* text,int text_size,int newline){
    printf("%s",message);
    fgets(text,text_size,stdin);
    if(newline == 0){
        text[strcspn(text,"\n")] = '\0';
    }
}

Main_L analyse_input(Main_L HTC,char* command,char file_path[260]){
    if(command[0] == ':'){
        char* command_flags[6];
        int count = tokenize(command, command_flags);

        if(strcmp(command_flags[0],"i") == 0){
            if(is_number(command_flags[1]) && count > 2){
                printf("%d\n",atoi(command_flags[1]));
                printf("%s\n",command_flags[2]);
                HTC = insert_line(&HTC,atoi(command_flags[1]),command_flags[2]);
            }
        }else if(strcmp(command_flags[0],"dl") == 0){
            if(is_number(command_flags[1])){
                HTC=delete_line(&HTC,atoi(command_flags[1]));
            }
        }else if(strcmp(command_flags[0],"view") == 0){
            display_list(HTC.head);
        }else if(strcmp(command_flags[0],"view_n") == 0){
            display_list_n(HTC.head);
        }else if(strcmp(command_flags[0],"write") == 0) {
            file_path[strcspn(file_path,".")] = '\0'; //remove the ".txt" if the user includes it
            save_file(&HTC, file_path);
            printf("File Saved in %s",file_path);
        }else if(is_number(command_flags[0])){
            printf("SUCCESS!");
            HTC = move_to_line(HTC,atoi(command_flags[0]));
        }
    }
    else{
        HTC = modify_line(&HTC,command);
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
