#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<errno.h>
#include "types.h"

int save_file(Main_L* HTC, char file_path[20]);
Main_L charge_file(char file_path[], int path_size, int user_input);
list* find_at_line(Main_L* HTC,int index);
int file_select;
void read_input(char message[],char* text,int text_size,int newline);
Main_L modify_line(Main_L *HTC, char new_text[1024]);
int analyse_input(Main_L HTC,char* command);
void display_list(list *L);

int main(){
    char file_path[256], buffer[1024];
    char command_buffer[1024], c;
    int user_input;
    bool skip = false;
    Main_L HTC;

    printf("============================\n");
    printf("---Welcome to our text editior---\n");
    printf("============================\n");
    while (true) 
    {
    do{
        printf("Choose operation\n");
        printf("1.Create a new file\n");
        printf("2.Open an existing file\n");
        printf("3.Exit Program\n");
        printf("Select a choice: ");
        scanf("%d", &user_input);        
        while ((c = getchar()) != '\n' && c != EOF);
    }while(user_input<1 || user_input>3);
    if (user_input == 3) return 0;

    HTC = charge_file(file_path, sizeof(file_path), user_input);
    display_list(HTC.head);

    if (!skip) {
        while(1){
            read_input(">>",command_buffer,sizeof(command_buffer),1); 
            if(analyse_input(HTC,command_buffer) != 0){
                printf("ERROR : Invalid Command\n");
            }else{
                printf("VALID Command\n");
            }
        }
    }
    }
}

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
            char* token;
            int count = 0;
    
            token = strtok(command, " :");
            if(token == NULL){
                return -1; //si il n'ya rien apres ":"
            }
            
        while (token != NULL && count < 6) {
            if(token[0] == '"') { 
                char* start = strchr(command + (token - command), '"');
                if (start) {
                    char* end = strrchr(start + 1, '"');
                    if (end) {
                        *end = '\0'; 
                        command_flags[count++] = start + 1;
                        break; 
                        }
                    }
                }
            command_flags[count++] = token;
            token = strtok(NULL, " ");

        char* command_identifier[6];
        if(strcmp(*command_identifier,"i") == 0){
            //insertion
        }else if(strcmp(*command_identifier,"dl") == 0){
            //deletion
        }else if(atoi(*command_identifier) != 0){
            //deplacment at la ligne n   
        }else if(strcmp(*command_identifier,"view")){
            printf("HERE\n");
            display_list(HTC.head);
        }

        return 0;
        }
    }
    else{
        modify_line(&HTC,command);
     }

}

Main_L error(){
    Main_L HTC;
    HTC.current = NULL; HTC.head = NULL; HTC.tail = NULL;
    return HTC;
}

Main_L charge_file(char file_path[], int path_size, int user_input){
    FILE *F = NULL;
    char buffer[1024];
    int f_exist;
    list *L = NULL, *P = NULL, *Q = NULL;
    bool invalid;
    Main_L HTC;

    HTC.current = NULL;
    if (user_input != 2 && user_input != 1) return error();
    
    read_input("Enter File Path (Relative || Absolute): ",file_path,path_size,0);

    if(user_input == 1){
        F = fopen(file_path, "wx");
        if(!F){
            if (errno == EEXIST) {
                printf("File at %s already exists !\n", file_path);
                do{
                    printf("Would you like to:\n");
                    printf(" 1-charge the file\n");
                    printf(" 2-overwrite the file\n");
                    printf(" 3-select another file\n");
                    scanf("%d\n", &f_exist);
                }while(f_exist < 1 || f_exist > 3);

                if( f_exist == 2 ){
                    F = fopen(file_path, "w");
                    printf("File created at %s", file_path);
                    fclose(F);
                    return error();
                } else if (f_exist == 3) return charge_file(file_path, path_size, user_input);
                else user_input = 2;
            } else {perror("Failed to open file"); return error() ;}
        } else {
                printf("File created at %s\n", file_path);
                fclose(F);
                return error();
        }
    }
    if (user_input == 2){

        F = fopen(file_path, "r");
        if(!F){perror("Failed to open file"); return error();}

        P = (list*)malloc(sizeof(list));
        if (P == NULL) return error();
        if( fgets(P->ln, sizeof(P->ln), F) == NULL ) return error();
        P->prv = NULL;
        P->svt = L;
        L = P;

        while(fgets(buffer, sizeof(buffer), F) != NULL ){
            P->svt = (list*)malloc(sizeof(list));
            if (P->svt == NULL) break;
            Q = P;
            P = P->svt;
            P->prv = Q;
            strcpy(P->ln, buffer);
            P->svt = NULL;
        }
     HTC.head = L;  HTC.current = HTC.tail = P; return HTC;
    }
}

int save_file(Main_L* HTC, char file_path[20]){
    FILE* F;
    char formatted_file_name[25];

    snprintf(formatted_file_name,sizeof(formatted_file_name),"%s.txt",file_path);

    F = fopen(formatted_file_name,"w");

    if(F == NULL){
        return -1;
    }

    list* p = HTC->head; 

    while(p != NULL){
        fprintf(F,"%s",p->ln);
        p = p->svt;
    }

    fclose(F);

    return 0;
}

list* find_line(Main_L HTC,int index){
    int k = 1;
    list* p = NULL;
    
    if(HTC.head == HTC.tail && index > 1){
        return NULL;   
    }

    while(k < index && p->svt != NULL){

        p = p->svt;
        k++;
    }

    if(k < index){
        return NULL;
    }

    return p;
}

void display_list(list *L){
    while(L != NULL){
        printf("%s", L->ln);
        L = L->svt;
    }
}

Main_L modify_line(Main_L *HTC, char new_text[1024]) {
    if (HTC == NULL || HTC->current == NULL) {
        printf("Error: Current line is NULL\n");
        return *HTC;
    }

    strcpy(HTC->current->ln, new_text);

    if (HTC->current->svt == NULL) {
        list* p = (list*)malloc(sizeof(list));
        if (p == NULL) {
            printf("ERROR allocating p\n");
            return *HTC;
        }
        
        strcpy(p->ln, "");
        p->prv = HTC->current;
        p->svt = NULL;
        
        HTC->current->svt = p; 
        
        HTC->current = p;
    } else {
        HTC->current = HTC->current->svt;
    }

    return *HTC; 
}