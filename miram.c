#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

list* find_line(Main_L HTC,int index){
    int k = 1;
    list* p = NULL;

    if(index < 1) return NULL;
    
    if(HTC.head == HTC.tail && index > 1){
        return NULL;   
    }

    while(k < index && p->svt != NULL){

        p = p->svt;
        k++;
    }

    if(k < index){
        return NULL;
    }

    return p;
}

Main_L move_to_line(Main_L HTC, int index) {
    HTC.current = find_line(HTC, index);
    return HTC;
}

Main_L insert(Main_L *HTC, int position,char input[300] ) {
    list *q = (list*)malloc(sizeof(list));
    strcpy(q->ln, input);
    q->svt = NULL;
    q->prv =NULL;
    if (HTC->head == NULL) {
        HTC->head =HTC->tail = HTC->current = q;
        return *HTC;
    }

    if (position <= 0) { 
        return *HTC;
    }

    list *prev = find_line(*HTC, position-1);

    if (prev == NULL || prev->svt == NULL) {
        q->prv =HTC->tail;
        HTC->tail->svt = q;
        HTC->tail = q;
        return *HTC;
    }

    list *next =prev->svt;
    q->svt =next;
    q->prv =prev;
    prev->svt =q;
    next->prv =q;
    HTC->current = q;
}
   
void delete_line(Main_L *HTC, int position) {

    if (HTC->head == NULL) return;

    list *curr = HTC->head;
    int i = 0;
   while (curr != NULL && i < position) {
        curr = curr->svt;
        i++;
    }

    if (curr == NULL) return;if (curr == HTC->head) {
        HTC->head = curr->svt;

        if (HTC->head != NULL)
            HTC->head->prv = NULL;
        else
            HTC->tail = NULL;

        HTC->current = HTC->head;
        free(curr);
        return;
    }if (curr == HTC->tail) {
        HTC->tail = curr->prv;
        HTC->tail->svt = NULL;

        HTC->current = HTC->tail;
        free(curr);
        return;
    }

    curr->prv->svt = curr->svt;
    curr->svt->prv = curr->prv;

    HTC->current = curr->svt;

    free(curr);
}
  
void modify_line(Main_L *HTC, char new_text[1024]) {

    if (HTC == NULL || HTC->current == NULL) {
        return;
    }

    strcpy(HTC->current->ln, new_text);

    if(HTC->current->svt == NULL){
        list* p = (list*)malloc(sizeof(list));
        if(p == NULL){
            printf("ERROR allocating p");
            return NULL;
        }
        strcpy(p->ln,"");
        p->prv = HTC->current;
        p->svt = NULL;
        HTC->current = p;
    }else{
        HTC->current = HTC->current->svt;
    }
}