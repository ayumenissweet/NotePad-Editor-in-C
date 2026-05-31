#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "headers/types.h"
#include "headers/input.h"
#include "headers/files.h"
#include "headers/nodes.h"

Main_List initialize_program(Status* s);

int main(){
    Status status;
    status.HTC = (Main_List) {NULL,NULL,NULL};
    status.print = status.undo_top = status.redo_top = -1;
    strcpy(status.file_path,"");
    char buffer[1024];
    int skip = 0;
    status.HTC = initialize_program(&status);
    display_nodes(status.HTC);
    while(!skip){
        read_input(">>",buffer,sizeof(buffer));
        analyse_input(&status, buffer);
    }
}

Main_List initialize_program(Status *s){
    int choice;
    char c;
    printf("=====================\n");
    printf("NOTEPAD BUT BETTER\n");
    printf("=====================\n");
    printf("Select A choice :\n");
    printf("1.Create a new file\n");
    printf("2.Open an existing file\n");
    printf("3.Quit\n");
    do{
        scanf("%d",&choice);
        while((c = getchar()) != '\n' && c != EOF);
    }while(choice < 1 || choice > 3);

    if(choice == 1){
        Main_List HTC;
        Node* p = (Node*) malloc(sizeof(Node));
        if(!p){
            printf("ERROR allocating\n");
            exit(0);
        }
        strcpy(p->line,"");
        p->svt = p->prv = NULL;
        HTC = (Main_List) {p,p,p};
        return HTC;
    }else if(choice == 2){
        Main_List HTC = {NULL,NULL,NULL};
        do{
            printf("Enter file path: ");
            fgets(s->file_path,sizeof(s->file_path),stdin);
            s->file_path[strcspn(s->file_path,"\n")] = '\0';
            HTC = read_file(s->file_path);
        }while(HTC.head == NULL);
        return HTC;
    }else{
        exit(0);
    }
}