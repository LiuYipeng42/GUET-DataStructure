#include <stdio.h>
#include <stdlib.h>

#define DataType int

struct Node;
typedef struct Node* PNode;
struct Node {
    DataType info;
    PNode link;
};

struct LinkQueue {
    PNode f;
    PNode r;
};

typedef struct LinkQueue* PLinkQueue;

PLinkQueue createEmptyQueue_link() {
    PLinkQueue plqu;
    plqu = (PLinkQueue)malloc(sizeof(struct LinkQueue));
    if (plqu != NULL) {
        plqu->f = NULL;
        plqu->r = NULL;
    } else
        printf("Out of space!!\n");
}

int isEmptyQueue_link(PLinkQueue plqu) {
    return (plqu->f == NULL);
}

void enQueue_link(PLinkQueue plqu, DataType x) {
    PNode p;
    p = (PNode)malloc(sizeof(struct Node));
    if (p == NULL)
        printf("Out of space!!\n");
    else {
        p->link = NULL;
        if (plqu->f == NULL)
            plqu->f = p;
        else
            plqu->r->link = p;
        plqu->r = p;
    }
}

void deQueue_link(PLinkQueue plqu) {
    PNode p;
    if (plqu->f == NULL)
        printf("Empty queue.\n");
    else {
        p = plqu->f;
        plqu->f = p->link;
        free(p);
    }
}

DataType frontQueue_link(PLinkQueue plqu) {
    if (plqu->f == NULL)
        printf("Empty queue.\n");
    else
        return (plqu->f->info);
}