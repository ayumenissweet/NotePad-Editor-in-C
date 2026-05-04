#include <stdio.h>
#include <stdbool.h>

#include "headers/files.h"
#include "headers/listes.h"
#include "headers/input.h"

int main(){
    char file_path[260], buffer[1024];
    char command_buffer[1024], c;
    int user_input;
    bool skip = false;
    Main_L HTC;

    printf("============================\n");
    printf("---Welcome to our text editior---\n");
    printf("============================\n");
    while (true) {
    do{
        printf("--\nChoose operation\n");
        printf("1.Create a new file\n");
        printf("2.Open an existing file\n");
        printf("3.Exit Program\n");
        printf("Select a choice: ");
        scanf("%d", &user_input);        
        while ((c = getchar()) != '\n' && c != EOF);
    }while(user_input<1 || user_input>3);
    if (user_input == 3) return 0;

    HTC = charge_file(file_path, user_input);
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
