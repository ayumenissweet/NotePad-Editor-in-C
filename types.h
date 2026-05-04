#ifndef TYPES_H
#define TYPES_H

typedef struct list{
    struct list *svt, *prv;
    char ln[1024];
}list;

typedef struct{
    list* head;
    list* tail;
    list* current;
}Main_L;

#endif