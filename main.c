#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#include "headers/files.h"
#include "headers/listes.h"
#include "headers/input.h"
#include "headers/undo-redo.h"

void print_rainbow(const char *text) {

    const char *colors[] = {
        "\033[31m",
        "\033[33m",
        "\033[32m",
        "\033[36m",
        "\033[34m",
        "\033[35m",
    };

    int num_colors = sizeof(colors) / sizeof(colors[0]);
    int color_index = 0;

    for (int i = 0; text[i] != '\0'; ) {

        unsigned char c = text[i];

        if (c < 128) {

            if (c != ' ' && c != '\n') {
                printf("%s", colors[color_index]);
                color_index = (color_index + 1) % num_colors;
            }

            putchar(c);
            i++;
        }

        /* UTF-8 multibyte character */
        else {

            printf("%s", colors[color_index]);
            color_index = (color_index + 1) % num_colors;

            int bytes = 0;

            if ((c & 0xE0) == 0xC0)
                bytes = 2;
            else if ((c & 0xF0) == 0xE0)
                bytes = 3;
            else if ((c & 0xF8) == 0xF0)
                bytes = 4;

            for (int j = 0; j < bytes; j++) {
                putchar(text[i + j]);
            }

            i += bytes;
        }
    }

    printf("\033[0m");
}

int main(){
    setlocale(LC_ALL, "");
    Status s = {0};
    char command_buffer[1024], c;
    int user_input;

    const char *header =
    "════════════════════════════\n"
    "        MINI NOTEPAD        \n"
    "════════════════════════════\n";

print_rainbow(header);
    

    while (true) {
        do {
            printf("1. Create a new file\n");
            printf("2. Open an existing file\n");
            printf("3. Exit program\n");
            printf("────────────────────────────\n");
            printf("Select a choice: ");
            scanf("%d", &user_input);
            while ((c = getchar()) != '\n' && c != EOF);
        } while (user_input < 1 || user_input > 3);

        if (user_input == 3) return 0;

        s.HTC = charge_file(s.file_path, user_input);
        display_list_n(s.HTC);
        s.skip = (s.HTC.head == NULL) ? 1 : 0;

        while (!s.skip) {
            read_input(">>", command_buffer, sizeof(command_buffer), 1);
            analyse_input(&s, command_buffer);
        }
    }
}
