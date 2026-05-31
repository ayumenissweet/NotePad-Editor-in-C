#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/types.h"
#include "../headers/files.h"
#include "../headers/input.h"
#include "../headers/nodes.h"

void save_file(Main_List HTC, char file_path[255]){
    if(strcmp(file_path, "") == 0) {
        while(1) {
            read_input("Input a file name : ", file_path, 255);

            FILE* F = fopen(file_path, "wx");
            if (F != NULL) {
                //file does not exist
                fclose(F);
                break; 
            }

            //file does exist
            char c; 
            int choice = 0;
            printf("File already exists!\n");
            printf("Would you like to :\n");
            printf("1. Try creating a different file\n");
            printf("2. Overwrite the file\n");
            
            do {
                if (scanf("%d", &choice) != 1) {
                    choice = 0; 
                }
                while((c = getchar()) != '\n' && c != EOF);
            } while(choice < 1 || choice > 2);

            if (choice == 2) {
                break; 
            }
        }
    }

    FILE* F = fopen(file_path, "w");
    if(!F){
        printf("Error opening file\n");
        return;
    }

    Node* p = HTC.head;
    while(p != NULL){
        fprintf(F, "%s", p->line); 
        if(p->svt == NULL && !strcmp(p->line,"")){
            break;
        }
        fprintf(F,"\n");
        p = p->svt;
    }
    
    fclose(F);
}

Main_List read_file(char file_path[255]) {
    char buffer[1024];
    Main_List HTC = {NULL,NULL,NULL};
    Node *p = NULL, *prv_p = NULL;

    FILE *F = fopen(file_path, "r");
    if (!F) {
        printf("File not found!\n");
        return (Main_List){NULL, NULL, NULL};
    }

    while (fgets(buffer, sizeof(buffer), F) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        p = create_node(buffer);

        if (HTC.head == NULL) {
            HTC.head = p;
            p->prv = NULL;
        } else {
            p->prv = prv_p;
            prv_p->svt = p;   
        }
        prv_p = p;          
    }
    HTC.tail = HTC.current = prv_p;

    if(p == NULL){ //file exists but just... empty
        strcpy(buffer,"");
        Node *p = create_node(buffer);
        HTC = (Main_List) {p,p,p}; //create a single empty node
    }

    fclose(F);
    return HTC;
}