#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/types.h"
#include "../headers/nodes.h"

#define RED "\033[0;31m"
#define DEFAULT "\033[0m"

Node* create_node(char new_content[1024]){
    Node* p = (Node*) malloc(sizeof(Node));
    if(!p){
        printf("Error allocating\n");
        return NULL;;
    }
    strcpy(p->line,new_content);
    p->svt = NULL;
    p->prv = NULL;
    return p;
}

void display_nodes(Main_List HTC){
    Node* head = HTC.head;
    int i = 1;
    while(head != NULL){
        if(head == HTC.current) {
            printf(RED);
            printf("%d. %s\n",i++,head->line);
            head = head->svt;
            printf(DEFAULT);
            continue;
        }
        
        printf("%d. %s\n",i++,head->line);
        head = head->svt;
    }
}

Node* find_line(Node* head,int index){
    if (index < 1) return NULL;
    int i = 1;
    Node* p = head;
    while(p != NULL && i < index){
        p = p->svt;
        i++;
    }
    return p;
}

Main_List point_line(Main_List HTC, int index){
    Node* p = find_line(HTC.head,index);
    if(p == NULL) return HTC;

    HTC.current = p;
    return HTC;
}

Main_List modify_line(Main_List HTC, char new_content[1024]){
    strcpy(HTC.current->line,new_content);

    if(HTC.current->svt == NULL){ //we are at the tail
        Node* p = (Node*) malloc(sizeof(Node));
        if(!p){
            printf("ERROR allocating\n");
            exit(0);
        }
        p->prv = HTC.current;
        p->svt = NULL;
        HTC.current->svt = p;
        HTC.current = HTC.tail = p;
        strcpy(p->line,"");
        return HTC;
    }

    //case : just point to the next line
    HTC.current = HTC.current->svt;
    return HTC;
}

Main_List insert_line(Main_List HTC,int index, char new_content[1024]){
    Node* p = find_line(HTC.head,index);
    if(p == NULL) return HTC;

    Node* q = (Node*) malloc(sizeof(Node));
    strcpy(q->line,new_content);
    if(!q){
        printf("ERROR allocating\n");
        return HTC;
    }

    //case one : insert at head :
    if(index == 1){
        HTC.head->prv = q;
        q->prv = NULL;
        q->svt = HTC.head;
        HTC.head = q;
        return HTC;
    }
    //case two : insert at tail
    if(p->svt == NULL){
        q->prv = HTC.tail->prv;
        q->svt = HTC.tail;
        HTC.tail->prv->svt = q;
        HTC.tail->prv = q;
        return HTC;
    }

    //case three : random insert
    Node *prv_p = p->prv;
    //link q
    q->prv = prv_p;
    q->svt = p;
    //link p to q
    prv_p->svt = q;
    p->prv = q;

    return HTC;
}

Main_List delete_line(Main_List HTC,int index){
    Node* p = find_line(HTC.head,index);
    if(p == NULL) return HTC;  

    //case one : head delete
    if(index == 1){
        Node* q = HTC.head;
        q->svt->prv = NULL;
        HTC.head = HTC.head->svt;
        if(p == HTC.current) { 
            HTC.current = q->svt;
        }
        free(q);
        return HTC;
    }

    //case two : tail delete
    if(p->svt == NULL){
        Node* q = HTC.tail;
        q->prv->svt = NULL;
        HTC.tail = HTC.tail->prv;
        if(p == HTC.current) { 
            HTC.current = q->prv;
        }
        free(q);
        return HTC;
    }

    //case three : random delete
    Node* q = p->prv;
    q->svt = p->svt;
    p->svt->prv = q;
    if(p == HTC.current) { //if we are deleting the current pointer, make sure it points to a different element
        HTC.current = q;
    }
    free(p);
    return HTC;
}

Main_List swap(Main_List HTC, int n, int m) {
    if (n == m) return HTC;
    if (n > m) { int tmp = n; n = m; m = tmp; }

    Node *P = find_line(HTC.head, n);
    Node *Q = find_line(HTC.head, m);

    if (P == NULL || Q == NULL) {
        printf(P == NULL ? "Line n is non-existent!\n" : "Line m is non-existent!\n");
        return HTC;
    }

    char tmp_line[1024];
    strcpy(tmp_line, P->line);
    strcpy(P->line, Q->line);
    strcpy(Q->line, tmp_line);

    if (HTC.current == P) {
        HTC.current = Q;
    } else if (HTC.current == Q) {
        HTC.current = P;
    }

    return HTC;
}

Main_List move_up(Main_List HTC, int index){
    if(index == 1){ 
        printf("Can't move the first line up!\n"); 
        return HTC;
    }
    Node* p = find_line(HTC.head,index);
    if(p == NULL){
        printf("can't move a non-existing line!\n");
        return HTC;
    }

    return swap(HTC,index,index-1);
}


Main_List move_down(Main_List HTC, int index){
    Node* p = find_line(HTC.head,index);
    if(p == NULL){
        printf("can't move a non-existing line!\n");
        return HTC;
    }
    if(p->svt == NULL){
        printf("Can't move the last line down!\n");
        return HTC;
    }

    return swap(HTC,index,index+1);
}