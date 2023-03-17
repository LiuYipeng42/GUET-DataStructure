#include <stdio.h>
#include <stdlib.h>

#define DataType int

struct SeqList {
    int MAXNUM;  // 元素的的最大个数
    int n;       // 当前元素的个数
    DataType* element;
};

typedef struct SeqList* PSeqList;

PSeqList createNullList_seq(int m) {
    PSeqList palist = (PSeqList)malloc(sizeof(struct SeqList));
    if (palist != NULL) {
        palist->element = (DataType*)malloc(sizeof(DataType) * m);
        if (palist->element) {
            palist->MAXNUM = m;
            palist->n = 0;
            return palist;
        } else
            free(palist);
    }

    printf("Out of space!!\n");
    return NULL;
}

int isNullList_seq(PSeqList palist) {
    return (palist->n == 0);
}

int locate_seq(PSeqList palist, DataType x) {
    // 求 x 在 palist 所指顺序表中的下标

    int q;
    for (q = 0; q < palist->n; q++) {
        if (palist->element[q] == x)
            return q;
    }
    return -1;
}

int insertPre_seq(PSeqList palist, int p, DataType x) {
    // 在 palist 所指顺序表中下标为 p 的元素之前插入元素 x
    int q;
    if (palist->n >= palist->MAXNUM) {
        // 若顺序表已满，则将顺序表的大小变为原来的 2 倍
        DataType* pos1 =
            (DataType*)malloc(sizeof(DataType) * palist->MAXNUM * 2);
        if (pos1 == NULL) {
            printf("Overflow!\n");
            return 0;
        }
        for (q = 0; q < palist->MAXNUM; q++)
            pos1[q] = palist->element[q];

        free(palist->element);
        palist->element = pos1;
        palist->MAXNUM *= 2;

        return 0;
    }
    if (p < 0 || p > palist->n) {
        printf("Not exist!\n");
        return 0;
    }

    for (q = palist->n - 1; q >= p; q--)
        palist->element[q + 1] = palist->element[q];

    palist->element[p] = x;
    palist->n = palist->n + 1;

    return 1;
}

int delete_seq(PSeqList palist, int p) {
    // 在 palist 所指顺序表中删除下标为 p 的元素
    int q;
    if (p < 0 || p > palist->n - 1) {
        printf("Not Exist!\n");
        return 0;
    }

    for (q = p; q < palist->n - 1; q++)
        palist->element[q] = palist->element[q + 1];

    palist->n = palist->n - 1;

    return 1;
}

int main() {
    return 0;
}
