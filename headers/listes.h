#ifndef LISTES_H
#define LISTES_H

#include "types.h"

list* find_at_line(Main_L* HTC,int index);
Main_L modify_line(Main_L *HTC, char new_text[1024]);
void display_list(list *L);
void display_list_n(list *L);
Main_L remove_dup(Main_L HTC);

#endif