#include <stdio.h>
#include<stdlib.h>
#include <string.h>

#include  "../headers/listes.h"

list* find_line(Main_L HTC,int index){
    int k = 1;
    list* p = NULL;
    
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

void display_list(list *L){
    while(L != NULL){
        printf("%s", L->ln);
        L = L->svt;
    }
    printf("\n");
}
void display_list_n(list *L){
    int i = 1;
    while(L != NULL){
        printf("%d %s", i, L->ln);
        L = L->svt; i++;
    }
    printf("\n");
}

Main_L modify_line(Main_L *HTC, char new_text[1024]) {
    if (HTC == NULL || HTC->current == NULL) {
        printf("Error: Current line is NULL\n");
        return *HTC;
    }

    strcpy(HTC->current->ln, new_text);

    if (HTC->current->svt == NULL) {
        list* p = (list*)malloc(sizeof(list));
        if (p == NULL) {
            printf("ERROR allocating p\n");
            return *HTC;
        }
        
        strcpy(p->ln, "");
        p->prv = HTC->current;
        p->svt = NULL;
        
        HTC->current->svt = p; 
        
        HTC->current = p;
    } else {
        HTC->current = HTC->current->svt;
    }

    return *HTC; 
}

Main_L remove_dup(Main_L HTC){
    list *L = HTC.head, *P, *Q;
    while(L != NULL){
        P = L->svt;
        while (P != NULL){
            if (strcmp(P->ln, L->ln) == 0){
                Q = P;  P = P->svt;
                Q->prv->svt = Q->svt;
                if (Q->svt != NULL)  Q->svt->prv = Q->prv;
                free(Q);
            } else P = P->svt;
        }
        Q = L; L = L->svt;
    }
    HTC.current = Q;    HTC.tail = Q;
    return HTC;
}