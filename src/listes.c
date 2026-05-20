#include <stdio.h>
#include<stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include  "../headers/listes.h"

list* find_line(Main_L HTC, int index){
    if (index < 1 || HTC.head == NULL)
        return NULL;

    list* p = HTC.head;
    int k = 1;

    while (p != NULL && k < index)
    {
        p = p->svt;
        k++;
    }

    return p;
}
Main_L move_to_line(Main_L HTC,int index){
    list* p = find_line(HTC,index);
    if(!p){
        return HTC;
    }
    HTC.current = p;
    return HTC;
}
void display_list(Main_L HTC){
    while(HTC.head != NULL){
        if (HTC.head == HTC.current) {
            printf(ANSI_COLOR_RED);
        }

        printf("%s", HTC.head->ln);

        printf(ANSI_COLOR_RESET);
        
        if(HTC.head->svt == NULL && !strcmp(HTC.head->ln,"")){
            printf("\n");
        }

        HTC.head = HTC.head->svt;
    }
}
void display_list_n(Main_L HTC) {
    int i = 1;
    
    while (HTC.head != NULL) {
        if (HTC.head == HTC.current) {
            printf(ANSI_COLOR_RED);
        }
        
        printf("%d %s", i, HTC.head->ln);
        
        printf(ANSI_COLOR_RESET);

        if(HTC.head->svt == NULL && !strcmp(HTC.head->ln,"")){
            printf("\n");
        }
        
        HTC.head = HTC.head->svt; 
        i++;
    }
    printf("==============\n");
}
void display_odd(list *L){
    int i;
    if (L!= NULL && L->prv == NULL) i = 1; else i = 2;
    while(L!= NULL){
        L = L->svt;
        printf("%d %s", i, L->ln);
        L = L->svt; i += 2;
    }
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
Main_L swap(Main_L HTC, int n, int m){
        list *P = HTC.head, *Q = HTC.head, *prevP = NULL, *prevQ = NULL;
        int i = 1, tmp;
        if (n == m) return HTC;
        if(n > m) {tmp = n; n = m; m = tmp;}
        
        while(i < n && P != NULL)   {prevP = P; P = P->svt; i++;}
        if (P == NULL || P->svt == NULL)  {printf("Line %d inexistant !\n", n); return HTC;}
        i = 1;
        while(i < m && Q != NULL)   {prevQ = Q; Q = Q->svt; i++;}
        if (Q == NULL || Q->svt == NULL)  {printf("Line %d inexistant !\n", m); return HTC;}

        if (prevP != NULL) prevP->svt = Q; else HTC.head = Q;
        prevQ->svt = P;
        if (Q->svt != NULL){
            Q->svt->prv = P;
        } else HTC.tail = P;

        list *temp = P->svt;
        P->svt = Q->svt;    Q->svt = temp;
        P->prv = prevQ;     Q->prv = prevP;

        return HTC;
}
Main_L modify_line(Main_L *HTC, char new_text[1024])
{
    if (HTC == NULL || HTC->current == NULL)
    {
        printf("Error: Current line is NULL\n");
        return *HTC;
    }

    strcpy(HTC->current->ln, new_text);

    
    if (HTC->current->svt == NULL)
    {
        list *p = (list *)malloc(sizeof(list));

        if (p == NULL)
        {
            printf("ERROR allocating p\n");
            return *HTC;
        }

        strcpy(p->ln, "");

     p  ->prv = HTC->current;
        p->svt = NULL;

        HTC->current->svt = p;

      
        HTC->tail = p;

        HTC->current = p;
    }
    else
    {
        HTC->current = HTC->current->svt;
    }

    return *HTC;
}
Main_L insert_line(Main_L *HTC, int index, char input[255])
{
    list *q = (list *)malloc(sizeof(list));

    if (q == NULL)
        return *HTC;

    strcat(input, "\n");
    strcpy(q->ln, input);

    q->svt = NULL;
    q->prv = NULL;

  
    if (HTC->head == NULL)
    {
        HTC->head = q;
        HTC->tail = q;
        HTC->current = q;
        return *HTC;
    }

    
    if (index == 1)
    {
        q->svt = HTC->head;
        HTC->head->prv = q;
        HTC->head = q;
        HTC->current = q;
        return *HTC;
    }

    list *prev = find_line(*HTC, index - 1);

    
    if (prev == NULL || prev->svt == NULL)
    {
        q->prv = HTC->tail;
        HTC->tail->svt = q;
        HTC->tail = q;
        HTC->current = q;
        return *HTC;
    }

    
    list *next = prev->svt;

    q->svt = next;
    q->prv = prev;

    prev->svt = q;
    next->prv = q;

    HTC->current = q;

    return *HTC;
}
Main_L delete_line(Main_L *HTC, int index){

    if (HTC == NULL || HTC->head == NULL)
        return *HTC;

    list* p = find_line(*HTC, index);

    if (p == NULL)
    {
        printf("ERROR: invalid index\n");
        return *HTC;
    }

   
    if (HTC->head == HTC->tail)
    {
        free(HTC->head);
        HTC->head = HTC->tail = HTC->current = NULL;
        return *HTC;
    }

    
    if (p == HTC->head)
    {
        HTC->head = p->svt;

        if (HTC->head != NULL)
            HTC->head->prv = NULL;

        free(p);
        HTC->current = HTC->head;
        return *HTC;
    }

    
    if (p == HTC->tail)
    {
        HTC->tail = p->prv;

        if (HTC->tail != NULL)
            HTC->tail->svt = NULL;

        free(p);
        HTC->current = HTC->tail;
        return *HTC;
    }

    
    p->prv->svt = p->svt;
    p->svt->prv = p->prv;

    HTC->current = p->svt;
    free(p);

    return *HTC;
}
Main_L move_line_up(Main_L* HTC, int index)
{
    if(HTC == NULL || HTC->head == NULL)
        return *HTC;

    
    if(index == 1){
        printf("ERROR : First line can't move up\n");
        return *HTC;
    }

    
    list* p = find_line(*HTC, index);

    if(p == NULL){
        printf("ERROR : Invalid line\n");
        return *HTC;
    }

    
    return swap(*HTC, index - 1, index);
}
Main_L move_line_down(Main_L* HTC, int index)
{
    if(HTC == NULL || HTC->head == NULL)
        return *HTC;

    
    list* p = find_line(*HTC, index);

    if(p == NULL){
        printf("ERROR : Invalid line\n");
        return *HTC;
    }

    
    if(p->svt == NULL){
        printf("ERROR : Last line can't move down\n");
        return *HTC;
    }

    
    return swap(*HTC, index, index + 1);
}