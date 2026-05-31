#ifndef NODES_H
#define NODES_H

#include "types.h"

Node* create_node(char new_content[1024]);
void display_nodes(Main_List HTC);
Node* find_line(Node* head, int index);
Main_List point_line(Main_List HTC, int index);
Main_List modify_line(Main_List HTC, char new_content[1024]);
Main_List insert_line(Main_List HTC,int index, char new_content[1024]);
Main_List delete_line(Main_List HTC,int index);
Main_List swap(Main_List HTC, int n, int m);
Main_List move_up(Main_List HTC, int index);
Main_List move_down(Main_List HTC, int index);

#endif