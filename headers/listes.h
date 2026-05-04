#ifndef LISTES_H
#define LISTES_H

#include "types.h"

list* find_at_line(Main_L* HTC,int index);
Main_L modify_line(Main_L *HTC, char new_text[1024]);
void display_list(list *L);
void display_list_n(list *L);
void display_odd(list *L);
Main_L remove_dup(Main_L HTC);
Main_L move_to_line(Main_L HTC,int index);
Main_L swap(Main_L HTC, int n, int m);
Main_L insert_line(Main_L *HTC, int index,char input[300]);
Main_L delete_line(Main_L *HTC, int index);

#endif