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

    HTC.current = NULL;
    if (user_input != 2 && user_input != 1) return all_null();
    
    read_input("Enter File Path (Relative || Absolute): ",file_path, 260, 0);

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
                    scanf("%d", &f_exist);
                    while ((c = getchar()) != '\n' && c != EOF);
                }while(f_exist < 1 || f_exist > 3);

                if( f_exist == 2 ){
                    F = fopen(file_path, "w");
                    file_created = true;
                } else if (f_exist == 3) return charge_file(file_path, user_input);
                else user_input = 2;
            } else {perror("Failed to open file"); return all_null() ;}
        } else file_created = true;
        if (file_created) {
                printf("File created at %s\n", file_path);
                fclose(F);

                P = (list*)malloc(sizeof(list));
                strcpy(P->ln,"");
                P->prv = NULL;
                P->svt = NULL;
                HTC = (Main_L) {P,P,P};
                return HTC;
        }
    }
    if (user_input == 2){

        F = fopen(file_path, "r");
        if(!F){perror("Failed to open file"); return all_null();}

        P = (list*)malloc(sizeof(list));
        if (P == NULL) return all_null();
        if( fgets(P->ln, sizeof(P->ln), F) == NULL ) return all_null();
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
        strcat(P->ln, "\n");
        fclose(F);
        HTC.head = L;  HTC.current = HTC.tail = P; return HTC;
    }
}

int save_file(Main_L* HTC, char file_path[260]){
    FILE* F;
    int choice;
    char formatted_file_name[265]; //pour ajouter ".txt"
    
    snprintf(formatted_file_name,sizeof(formatted_file_name),"%s.txt",file_path);
    printf("%s\n",formatted_file_name);
    
    F = fopen(formatted_file_name,"r");
    if(F){
        while(true){
            printf("Overwrite File [1/0] : %s ?",formatted_file_name);  
            scanf("%d",&choice);
            if(choice == 1 || choice == 0) 
                break;
        }   
        if(choice == 1){
            fclose(F);
            F = fopen(formatted_file_name,"w");
        }else if(choice == 0){
            fclose(F);
            char new_file_path[260];
            read_input("Select new file name: ", new_file_path,260, 0);
            return save_file(HTC,new_file_path);
        }
    }else{
        return -1;
    }

    if(!F){
        return -1;
    }

    list* p = HTC->head; 

    while(p != NULL){
        fprintf(F,"%s",p->ln);
        p = p->svt;
    }

    fclose(F);

    printf("Save Done!");

    return 0;
}

Main_L all_null(){
    Main_L HTC;
    HTC.current = NULL; HTC.head = NULL; HTC.tail = NULL;
    return HTC;
}
