#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int analyse_input(Main_L HTC,char* command){
    if(command[0] == ':'){
        char* command_flags[6];
        int count = tokenize(command,command_flags);

        if(strcmp(command_flags[0],"i") == 0){
        }else if(strcmp(command_flags[0],"dl") == 0){
            //deletion
        }else if(atoi(command_flags[0]) != 0){
            //deplacment at la ligne n   
        }else if(strcmp(command_flags[0],"view")){
            display_list(HTC.head);
        }else{
            return -1;
        }
    }
    else{
        modify_line(&HTC,command);
     }

}

int tokenize(char* command, char* command_flags[6]) {
    int count = 0;
    char* p = command;

    if (*p == ':') p++;

    while (*p != '\0' && count < 6) {
        while (*p == ' ') p++;
        if (*p == '\0') break;

        if (*p == '"') {
            p++; 
            command_flags[count++] = p; 
            
            while (*p != '"' && *p != '\0') p++;
            
            if (*p == '"') {
                *p = '\0'; 
                p++;       
            }
        } else {
            command_flags[count++] = p; 
            
            while (*p != ' ' && *p != '\0') p++;
            
            if (*p != '\0') {
                *p = '\0'; 
                p++;       
            }
        }
    }
    return count;
}
