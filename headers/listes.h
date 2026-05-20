#ifndef LISTES_H
#define LISTES_H

#include "types.h"

list*   find_line(Main_L HTC, int index);
void    display_list(Main_L HTC);
void    display_list_n(Main_L HTC);
void    display_odd(list *L);
Main_L  move_to_line(Main_L HTC, int index);
Main_L  remove_dup(Main_L HTC);
Main_L  swap(Main_L HTC, int n, int m);
Main_L  modify_line(Main_L *HTC, char new_text[1024]);
Main_L  insert_line(Main_L *HTC, int index, char input[255]);
Main_L  delete_line(Main_L *HTC, int index);
Main_L  move_line_up(Main_L *HTC, int index);
Main_L  move_line_down(Main_L *HTC, int index);

#endif
