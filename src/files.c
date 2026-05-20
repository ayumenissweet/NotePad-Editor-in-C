#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#include "../headers/files.h"
#include "../headers/input.h"

Main_L charge_file(char file_path[260], int user_input){

    FILE *F = NULL;
    char buffer[1024], c;
    bool file_created = false;
    int f_exist;
    list *L = NULL, *P = NULL, *Q = NULL;
    Main_L HTC;
//initialisations

    HTC.current = NULL;
    if(user_input != 2 && user_input != 1) return all_null();  
//emergency exist if abnormal user input

    if(user_input == 1){
        P = (list*)malloc(sizeof(list));
        strcpy(P->ln, "");
        P->prv = NULL;
        P->svt = NULL;
        HTC = (Main_L){P, P, P};
        return HTC;
    }
//if we create a new file then we don't choose it's name until we decide save it

    read_input("Enter File Path (Relative || Absolute): ", file_path, 260, 0);
//the file path can be either relative or absolute so a simple file name is enough for files in the same folder

    if(user_input == 2){
        F = fopen(file_path, "r");
        if(!F){ perror("Failed to open file"); return all_null(); }
//this handles logical file creation failure

//preparing FIFO
        P = (list*)malloc(sizeof(list));
        if(P == NULL) return all_null();
        if(fgets(P->ln, sizeof(P->ln), F) == NULL) return all_null();
        P->prv = NULL;
        P->svt = L;
        L = P;
//FIFO Linked list creation
        while(fgets(buffer, sizeof(buffer), F) != NULL){
            P->svt = (list*)malloc(sizeof(list));
            if(P->svt == NULL) break;
            Q = P;
            P = P->svt;
            P->prv = Q;
            strcpy(P->ln, buffer);
            P->svt = NULL;
        }
//we want the last line to be an empty new line to allow quicker user insertion after re-opening
//for this we need this check
        if(strcmp(P->ln, "") != 0){
            if(P->ln[strlen(P->ln) - 1] != '\n') strcat(P->ln, "\n");//add the new line caracter if it doesn't exist
            P->svt = (list*)malloc(sizeof(list));//add a new empty line at the last
            if(P->svt == NULL) return all_null();
            Q = P;
            P = P->svt;
            P->prv = Q;
            strcpy(P->ln, "");
            P->svt = NULL;
        }else{
            strcat(P->ln, "");
        }
        fclose(F);
        HTC.head = L;
        HTC.current = HTC.tail = P; //P points actulally to the tail, andthe user is intended to insert at the end
        return HTC;
    }

    return all_null();// just an emergency exit
}

int save_file(Main_L *HTC, char file_path[260]){
    FILE *F;
    int choice, f_exist;
    char c;

    if(strcmp(file_path, "") == 0){
        read_input("Enter File Path (Relative || Absolute): ", file_path, 260, 0);

        F = fopen(file_path, "wx");
        if(!F){
            if(errno == EEXIST){
                printf("File at %s already exists !\n", file_path);
                do{
                    printf("Would you like to:\n");
                    printf(" 1-overwrite the file\n");
                    printf(" 2-Enter another file path\n");
                    scanf("%d", &f_exist);
                    while((c = getchar()) != '\n' && c != EOF);
                }while(f_exist < 1 || f_exist > 2);

                if(f_exist == 2){
                    strcpy(file_path, "");
                    return save_file(HTC, file_path);
                }
            }else{ perror("Failed to open file"); return -1; }
        }
    }

    F = fopen(file_path, "w");
    if(!F) return -1;

    list *p = HTC->head;
    while(p->svt != NULL){
        fprintf(F, "%s", p->ln);
        p = p->svt;
    }

    fclose(F);
    printf("Save Done!\n");
    return 0;
}

// a function that quicly returns an all NULL HTC variable
Main_L all_null(){
    Main_L HTC;
    HTC.current = NULL;
    HTC.head = NULL;
    HTC.tail = NULL;
    return HTC;
}
