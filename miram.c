#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

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

Main_L move_to_line(Main_L HTC, int index){
    HTC.current = find_line(HTC, index);
    return HTC;
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