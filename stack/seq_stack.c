#include <stdio.h>
#include <stdlib.h>

#define DataType int

// 顺序栈
struct SeqStack {
    int MAXNUM;  // 元素的最大个数
    int t;       // 栈顶位置
    DataType* s;
};

typedef struct SeqStack* PSeqStack;

PSeqStack createNullList_seq(int m) {
    PSeqStack pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack != NULL) {
        pastack->s = (DataType*)malloc(sizeof(DataType) * m);
        if (pastack->s) {
            pastack->MAXNUM = m;
            pastack->t = -1;
            return pastack;
        } else
            free(pastack);
    }

    printf("Out of space!!\n");
    return NULL;
}

int isEmptyStack_seq(PSeqStack pastack) {
    return (pastack->t == -1);
}

void push_seq(PSeqStack pastack, DataType x) {
    if (pastack->t >= pastack->MAXNUM - 1)
        printf("Overflow!\n");
    else {
        pastack->t = pastack->t + 1;
        pastack->s[pastack->t] = x;
    }
}

void pop_seq(PSeqStack pastack) {
    if (pastack->t == -1)
        ptintf("Underflow!\n");
    else
        pastack->t = pastack->t - 1;
}

DataType top_seq(PSeqStack pastack) {
    if (pastack->t == -1)
        printf("It is empty!\n");
    else
        return (pastack->s[pastack->t]);
}