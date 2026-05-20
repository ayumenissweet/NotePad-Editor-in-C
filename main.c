#include <stdio.h>
#include <stdbool.h>

#include "headers/files.h"
#include "headers/listes.h"
#include "headers/input.h"
#include "headers/undo-redo.h"

int main(){
    char file_path[260] = "", buffer[1024];
    char command_buffer[1024], c;
    int user_input,print_mode = 0,undo_top,redo_top;
    bool skip = false;
    Main_L HTC;
    Action undo_stack[32],redo_stack[32];

    printf("============================\n");
    printf("---Welcome to our text editior---\n");
    printf("============================\n");
    while (true) {
    do{
        printf("\nChoose operation\n");
        printf("1.Create a new file\n");
        printf("2.Open an existing file\n");
        printf("3.Exit Program\n");
        printf("Select a choice: ");
        scanf("%d", &user_input);        
        while ((c = getchar()) != '\n' && c != EOF);
    }while(user_input<1 || user_input>3);
    if (user_input == 3) return 0;

    HTC = charge_file(file_path, user_input);
    display_list_n(HTC);
    if (HTC.head == NULL) skip = true; else skip = false;
    if (!skip) {
        while(1){
            read_input(">>",command_buffer,sizeof(command_buffer),1); 
            HTC = analyse_input(HTC,command_buffer,file_path,&print_mode,undo_stack,&undo_top,redo_stack,&redo_top);
        }
    }
    }
}
