#include <stdio.h>
#include <stdlib.h>

#define DataType int

// 顺序队列
struct SeqQueue {
    int MAXNUM;
    int f, r;
    DataType* q;
};

typedef struct SeqQueue* PSeqQueue;

PSeqQueue createNullList_seq(int m) {
    PSeqQueue pastack = (PSeqQueue)malloc(sizeof(struct SeqQueue));
    if (pastack != NULL) {
        pastack->q = (DataType*)malloc(sizeof(DataType) * m);
        if (pastack->q) {
            pastack->MAXNUM = m;
            pastack->f = 0;
            pastack->r = 0;
            return pastack;
        } else
            free(pastack);
    }

    printf("Out of space!!\n");
    return NULL;
}

int isEmptyQueue_seq(PSeqQueue paqu) {
    return (paqu->f == paqu->r);
}

void enQueue_seq(PSeqQueue paqu, DataType x) {
    if ((paqu->r + 1) % paqu->MAXNUM == paqu->f)
        printf("Full queue.\n");
    else {
        paqu->q[paqu->r] = x;
        paqu->r = (paqu->r + 1) % paqu->MAXNUM;
    }
}

void deQueue_seq(PSeqQueue paqu) {
    if (paqu->f == paqu->r)
        printf("Empty queue.\n");
    else
        paqu->f = (paqu->f + 1) % paqu->MAXNUM;
}

DataType frontQueue_seq(PSeqQueue paqu) {
    if (paqu->f == paqu->r)
        printf("Empty queue.\n");
    else
        return (paqu->q[paqu->f]);
}