#include <stdio.h>
#include <stdbool.h>

#include "headers/files.h"
#include "headers/listes.h"
#include "headers/input.h"
#include "headers/undo-redo.h"

#include <wchar.h>    
#include <locale.h>  

#ifdef _WIN32
#include <windows.h>
#endif

void print_rainbow_wide(const wchar_t *text) {
    const char *colors[] = {
        "\033[31m", // Red
        "\033[33m", // Yellow
        "\033[32m", // Green
        "\033[36m", // Cyan
        "\033[34m", // Blue
        "\033[35m", // Magenta
    };

    int num_colors = sizeof(colors) / sizeof(colors[0]);
    int color_index = 0;

    for (int i = 0; text[i] != L'\0'; i++) {
        wchar_t c = text[i];

        if (c != L' ' && c != L'\n' && c != L'\r') {
            printf("%s", colors[color_index]);
            color_index = (color_index + 1) % num_colors;
        }

        putwchar(c);
    }

    printf("\033[0m");
}

int main(){
    setlocale(LC_ALL, "");
    Status s = {0};
    char command_buffer[1024], c;
    int user_input;

    setlocale(LC_ALL, ".UTF-8");

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif

    const wchar_t *header =
        L"════════════════════════════\n"
        L"        MINI NOTEPAD        \n"
        L"════════════════════════════\n";

    print_rainbow_wide(header);

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
