#include <stdio.h>
#include <stdlib.h>

#define DataType int

struct Node;
typedef struct Node* PNode;

struct Node {
    DataType info;
    PNode link;
};

struct LinkStack {
    PNode top;
};

typedef struct LinkStack* PlinkStack;

PlinkStack createEmptyStack_link() {
    PlinkStack plstack;
    plstack = (PlinkStack)malloc(sizeof(struct LinkStack));

    if (plstack != NULL)
        plstack->top = NULL;
    else
        printf("Out of space!\n");

    return plstack;
}

int isEmptyStack_link(PlinkStack plastack) {
    return (plastack->top = NULL);
}

void push_link(PlinkStack plstack, DataType x) {
    PNode p;
    p = (PNode)malloc(sizeof(struct Node));
    if (p == NULL)
        printf("Out of space!\n");
    else {
        p->info = x;
        p->link = plstack->top;
        plstack->top = p;
    }
}

void pop_link(PlinkStack plstack) {
    PNode p;
    if (isEmptyStack_link(plstack))
        printf("Empty stack pop.\n");
    else {
        p = plstack->top;
        plstack->top = plstack->top->link;
        free(p);
    }
}

DataType top_link(PlinkStack plstack) {
    if (plstack->top == NULL)
        printf("Empty stack pop.\n");
    else
        return (plstack->top->info); 
}